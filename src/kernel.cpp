/*
 * Copyright © 2014 Thorben Hasenpusch <thorben.hasenpusch@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <uefi/uefi.h>
#include <framebuffer/framebuffer.h>
#include <lib/stdio.h>
#include <cpuid/cpuid.h>

static void print_memory_descriptor_attribute(UINT64 attribute);
static void print_memory_map(const UEFI::MemoryMap& map);

extern "C"
EFI_STATUS EFIAPI kmain(EFI_HANDLE handle, EFI_SYSTEM_TABLE *systab)
{
    EFI_STATUS status;
    EFI_BOOT_SERVICES *bs = systab->BootServices;

    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = UEFI::get_gop(handle, *systab);
    if (gop == nullptr) {
        UEFI::print(*systab, L"No GOP framebuffer support!\r\n");
        __asm volatile ("cli \n\t hlt");
    }

    Framebuffer::init(*gop);

    UEFI::MemoryMap memory_map;
    UEFI::get_memory_map(*systab, memory_map);

    status = bs->ExitBootServices(handle, memory_map.map_key);
    if (EFI_STATUS_IS_ERROR(status))
        UEFI::die(*systab, status, L"ExitBootServices");

    Framebuffer::clear_screen();

    char buf[CPUID::VENDOR_STR_BUF_SIZE];
    printf("Welcome to Simplix! [CPU: %s]\n\n", CPUID::get_vendor_string(buf));

    printf("Memory map:\n");
    print_memory_map(memory_map);

    printf("Halting...");

    // Just halt for now
    __asm volatile ("cli \n\t hlt");
    return EFI_SUCCESS;
}

void print_memory_descriptor_attribute(UINT64 attribute)
{
    if (attribute & EFI_MEMORY_UC)
        printf("UC ");
    if (attribute & EFI_MEMORY_WC)
        printf("WC ");
    if (attribute & EFI_MEMORY_WT)
        printf("WT ");
    if (attribute & EFI_MEMORY_WB)
        printf("WB ");
    if (attribute & EFI_MEMORY_UCE)
        printf("UCE ");
    if (attribute & EFI_MEMORY_WP)
        printf("WP ");
    if (attribute & EFI_MEMORY_RP)
        printf("RP ");
    if (attribute & EFI_MEMORY_XP)
        printf("XP ");
    if (attribute & EFI_MEMORY_RUNTIME)
        printf("RUNTIME ");
    printf("\n");
}

void print_memory_map(const UEFI::MemoryMap &map)
{
    for (size_t i = 0; i < map.memory_map_size / map.descriptor_size; ++i) {
        const void *ptr = (uint8_t *)map.memory_map + map.descriptor_size * i;
        const EFI_MEMORY_DESCRIPTOR &desc = *(EFI_MEMORY_DESCRIPTOR *)ptr;

        printf("Type: %s\n", UEFI::memory_type_to_string((EFI_MEMORY_TYPE)desc.Type));
        size_t size = desc.NumberOfPages * 4096;
        printf("Physical range: 0x%p -> 0x%p | %zu bytes\n", (void *)desc.PhysicalStart,
               (uint8_t *)desc.PhysicalStart + size, size);
        printf("Attributes: ");
        print_memory_descriptor_attribute(desc.Attribute);
        printf("\n");
    }
}
