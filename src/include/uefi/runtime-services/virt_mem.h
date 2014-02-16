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

#ifndef UEFI_RUN_VIRT_MEM_H
#define UEFI_RUN_VIRT_MEM_H

#include <uefi/types.h>

#define EFI_OPTIONAL_PTR 0x00000001

typedef EFI_STATUS (EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP)
(UINTN MemoryMapSize, UINTN DescriptorSize, UINT32 DescriptorVersion,
 EFI_MEMORY_DESCRIPTOR *VirtualMap);

typedef EFI_STATUS (EFIAPI *EFI_CONVERT_POINTER)
(UINTN DebugDisposition, VOID **Address);

#endif // UEFI_RUN_VIRT_MEM_H
