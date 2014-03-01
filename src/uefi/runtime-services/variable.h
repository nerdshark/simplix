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

#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD 0x00000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS 0x00000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE 0x00000040

struct EFI_VARIABLE_AUTHENTICATION {
    UINT64 MonotonicCount;
    WIN_CERTIFICATE_UEFI_GUID AuthInfo;
};

struct EFI_VARIABLE_AUTHENTICATION_2 {
    EFI_TIME TimeStamp;
    WIN_CERTIFICATE_UEFI_GUID AuthInfo;
};

typedef EFI_STATUS (EFIAPI *EFI_GET_VARIABLE)
(CHAR16 *VariableName, EFI_GUID *VendorGuid, UINT32 *Attributes,
 UINTN DataSize, VOID *Data);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_VARIABLE_NAME)
(UINTN *VariableNameSize, CHAR16 *VariableName, EFI_GUID VendorGuid);

typedef EFI_STATUS (EFIAPI *EFI_SET_VARIABLE)
(CHAR16 *VariableName, EFI_GUID *VendorGuid, UINT32 Attributes,
 UINTN DataSize, VOID *Data);

typedef EFI_STATUS (EFIAPI *EFI_QUERY_VARIABLE_INFO)
(UINT32 Attributes, UINT64 *MaximumVariableStorageSize,
 UINT64 *RemainingVariableStorageSize, UINT64 *MaximumVariableSize);
