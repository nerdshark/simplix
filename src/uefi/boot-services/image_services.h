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
(EFI_HANDLE ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable);

typedef EFI_STATUS (EFIAPI *EFI_EXIT)
(EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus, UINTN ExitDataSize,
 CHAR16 *ExitData);

typedef EFI_STATUS (EFIAPI *EFI_EXIT_BOOT_SERVICES)
(EFI_HANDLE ImageHandle, UINTN MapKey);
