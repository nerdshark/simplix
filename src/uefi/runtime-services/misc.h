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

#define EFI_CAPSULE_REPORT_GUID \
{ 0x39b68c46, 0xf7fb, 0x441b, 0xb6, 0xec, 0x16, 0xb0, 0xf6, 0x98, 0x21, 0xf3 }

enum EFI_RESET_TYPE {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
};

struct EFI_CAPSULE_BLOCK_DESCRIPTOR {
    UINT64 Length;
    union {
        EFI_PHYSICAL_ADDRESS DataBlock;
        EFI_PHYSICAL_ADDRESS ContinuationPointer;
    } Union;
};

struct EFI_CAPSULE_HEADER {
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
};

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET 0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET 0x00040000

#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI 0x0000000000000001
#define EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION 0x0000000000000002
#define EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED 0x0000000000000004
#define EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED 0x0000000000000008
#define EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED 0x0000000000000010

struct EFI_CAPSULE_RESULT_VARIABLE_HEADER {
    UINT32 VariableTotalSize;
    UINT32 Reserved;
    EFI_GUID CapsuleGuid;
    EFI_TIME CapsuleProcessed;
    EFI_STATUS CaspuleStatus;
};

struct EFI_CAPSULE_RESULT_VARIABLE_FMP {
    UINT16 Version;
    UINT8 PayloadIndex;
    UINT8 UpdateImageIndex;

    EFI_GUID UpdateImageTypeId;
};

typedef VOID (EFIAPI *EFI_RESET_SYSTEM)
(EFI_RESET_TYPE ResetType, EFI_STATUS ResetStatus, UINTN DataSize,
 VOID *ResetData);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT)
(UINT32 *HighCount);

typedef EFI_STATUS (EFIAPI *EFI_UPDATE_CAPSULE)
(EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount,
 EFI_PHYSICAL_ADDRESS ScatterGatherList);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES)
(EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount,
 UINT64 *MaximumCapsuleSize, EFI_RESET_TYPE *ResetType);
