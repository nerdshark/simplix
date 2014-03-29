/*
 * Copyright (c) 2014 Thorben Hasenpusch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <uefi/uefi.h>
#include <framebuffer/framebuffer.h>
#include <lib/stdio.h>
#include <cpuid/cpuid.h>

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

    char buf[CPUID::VENDOR_STR_BUF_SIZE];
    printf("Welcome to Simplix! [CPU: %s]\n", CPUID::get_vendor_string(buf));

    // Just halt for now
    __asm volatile ("cli \n\t hlt");
    return EFI_SUCCESS;
}
