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
