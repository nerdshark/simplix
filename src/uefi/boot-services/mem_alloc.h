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

#include <uefi/types.h>

enum EFI_ALLOCATE_TYPE {
    AllocateAnyPages,
    AllocateMaxAddress,
    MaxAllocateType
};

enum EFI_MEMORY_TYPE {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType
};

struct EFI_MEMORY_DESCRIPTOR {
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
};

#define EFI_MEMORY_UC 0x0000000000000001
#define EFI_MEMORY_WC 0x0000000000000002
#define EFI_MEMORY_WT 0x0000000000000004
#define EFI_MEMORY_WB 0x0000000000000008
#define EFI_MEMORY_UCE 0x0000000000000010
#define EFI_MEMORY_WP 0x0000000000001000
#define EFI_MEMORY_RP 0x0000000000002000
#define EFI_MEMORY_XP 0x0000000000004000
#define EFI_MEMORY_RUNTIME 0x8000000000000000

#define EFI_MEMORY_DESCRIPTOR_VERSION 1

typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_PAGES)
(EFI_ALLOCATE_TYPE Type, EFI_MEMORY_TYPE MemoryType, UINTN Pages,
 EFI_PHYSICAL_ADDRESS *Memory);

typedef EFI_STATUS (EFIAPI *EFI_FREE_PAGES)
(EFI_PHYSICAL_ADDRESS Memory, UINTN Pages);

typedef EFI_STATUS (EFIAPI *EFI_GET_MEMORY_MAP)
(UINTN *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap, UINTN *MapKey,
 UINTN *DescriptorSize, UINT32 *DescriptorVersion);

typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_POOL)
(EFI_MEMORY_TYPE PoolType, UINTN Size, VOID **Buffer);

typedef EFI_STATUS (EFIAPI *EFI_FREE_POOL)
(VOID *Buffer);
