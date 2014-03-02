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

EFI_STATUS EFIAPI kmain(EFI_HANDLE handle, EFI_SYSTEM_TABLE *systab)
{
    EFI_STATUS status;
    EFI_BOOT_SERVICES *bs = systab->BootServices;

    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = uefi_get_gop(handle, systab);
    if (gop == NULL) {
        uefi_print(systab->ConOut, L"No GOP framebuffer support!\r\n");
        __asm volatile ("cli \n\t hlt");
    }

    framebuffer_init(gop);

    struct uefi_memory_map memory_map;
    uefi_get_memory_map(systab, &memory_map);

    status = bs->ExitBootServices(handle, memory_map.map_key);
    if (EFI_STATUS_IS_ERROR(status))
        uefi_die(systab, status, L"ExitBootServices");

    char buf[13];
    printf("Welcome to Simplix! [CPU: %s]\n", cpuid_get_vendor_string(buf));

    // Just halt for now
    __asm volatile ("cli \n\t hlt");
    return EFI_SUCCESS;
}
