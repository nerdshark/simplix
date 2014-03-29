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

#pragma once

#include <uefi/systab.h>
#include <uefi/status_codes.h>
#include <uefi/protocols/console/console.h>

namespace UEFI {

inline EFI_STATUS print(const EFI_SYSTEM_TABLE &systab, const CHAR16 *s)
{
    return systab.ConOut->OutputString(systab.ConOut, (CHAR16 *)s);
}

const CHAR16 *error_to_string(EFI_STATUS status);

struct MemoryMap {
    UINTN memory_map_size;
    EFI_MEMORY_DESCRIPTOR *memory_map;
    UINTN map_key;
    UINTN descriptor_size;
    UINT32 descriptor_version;
};

/*
 * Fills @map with the current UEFI-provided memory map.
 */
void get_memory_map(const EFI_SYSTEM_TABLE &systab, MemoryMap &map);

/*
 * Returns a pointer to an EFI_GRAPHICS_OUTPUT_PROTOCOL instance that supports
 * direct framebuffer access and either RGB or BGR colors, nullptr otherwise.
 */
EFI_GRAPHICS_OUTPUT_PROTOCOL *get_gop(EFI_HANDLE handle, const EFI_SYSTEM_TABLE &systab);

/*
 * Prints '@msg: [@status translated to string]' and halts the CPU.
 */
void die(const EFI_SYSTEM_TABLE &systab, EFI_STATUS status, const CHAR16 *msg);

} // namespace UEFI end
