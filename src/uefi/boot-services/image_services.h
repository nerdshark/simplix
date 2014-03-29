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

#define EFI_HII_PACKAGE_LIST_PROTOCOL_GUID \
{ 0x6a1ee763, 0xd47a, 0x43b4, 0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc }

//typedef EFI_HII_PACKAGE_LIST_HEADER *EFI_HII_PACKAGE_LIST_PROTOCOL;

struct EFI_SYSTEM_TABLE;

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_LOAD)
(BOOLEAN BootPolicy, EFI_HANDLE ParentImageHandle,
 EFI_DEVICE_PATH_PROTOCOL *DevicePath, VOID *SourceBuffer, UINTN SourceSize,
 EFI_HANDLE *ImageHandle);

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_START)
(EFI_HANDLE ImageHandle, UINTN *ExitDataSize, CHAR16 **ExitData);

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_UNLOAD)
(EFI_HANDLE ImageHandle);

typedef EFI_STATUS (EFIAPI *EFI_IMAGE_ENTRY_POINT)
(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);

typedef EFI_STATUS (EFIAPI *EFI_EXIT)
(EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus, UINTN ExitDataSize,
 CHAR16 *ExitData);

typedef EFI_STATUS (EFIAPI *EFI_EXIT_BOOT_SERVICES)
(EFI_HANDLE ImageHandle, UINTN MapKey);
