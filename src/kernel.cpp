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
#include <lib/string.h>

extern "C"
EFI_STATUS EFIAPI kmain(EFI_HANDLE handle, EFI_SYSTEM_TABLE *systab)
{
    EFI_STATUS status;

    UEFI::print(systab->ConOut, L"Welcome to Simplix!\r\n");

    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = UEFI::get_gop(handle, systab);
    void *framebuffer_base = (void *)gop->Mode->FrameBufferBase;
    size_t framebuffer_size = gop->Mode->FrameBufferSize;

    UEFI::MemoryMap memory_map;
    UEFI::get_memory_map(systab, &memory_map);

    status = systab->BootServices->ExitBootServices(handle, memory_map.map_key);
    if (EFI_STATUS_IS_ERROR(status))
        UEFI::die(systab, status, L"ExitBootServices");

    // Test framebuffer; should set screen to all-white
    memset(framebuffer_base, 0xff, framebuffer_size);

    __asm__ volatile ("cli \n\t hlt");
    return EFI_SUCCESS;
}
