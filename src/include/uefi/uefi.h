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

#pragma once

#include <uefi/systab.h>
#include <uefi/status_codes.h>
#include <uefi/protocols/console/console.h>

namespace UEFI {

inline EFI_STATUS print(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *out, const CHAR16 *s)
{
    return out->OutputString(out, (CHAR16 *)s);
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
void get_memory_map(const EFI_SYSTEM_TABLE *systab, MemoryMap *map);

/*
 * Returns a pointer to an EFI_GRAPHICS_OUTPUT_PROTOCOL instance that supports
 * direct framebuffer access and either RGB or BGR colors, nullptr otherwise.
 */
EFI_GRAPHICS_OUTPUT_PROTOCOL *get_gop(EFI_HANDLE handle,
                                      const EFI_SYSTEM_TABLE *systab);

/*
 * Prints '@msg: [@status translated to string]' and halts the CPU.
 */
void die(const EFI_SYSTEM_TABLE *systab, EFI_STATUS status, const CHAR16 *msg);

}
