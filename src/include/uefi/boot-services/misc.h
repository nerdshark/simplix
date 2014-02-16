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

#ifndef UEFI_BOOT_MISC_H
#define UEFI_BOOT_MISC_H

#include <uefi/types.h>

typedef EFI_STATUS (EFIAPI *EFI_SET_WATCHDOG_TIMER)
(UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize, CHAR16 *WatchdogData);

typedef EFI_STATUS (EFIAPI *EFI_STALL)
(UINTN Microseconds);

typedef VOID (EFIAPI *EFI_COPY_MEM)
(VOID *Destination, VOID *Source, UINTN Length);

typedef VOID (EFIAPI *EFI_SET_MEM)
(VOID *Buffer, UINTN Size, UINT8 Value);

typedef EFI_STATUS (EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT)
(UINT64 *Count);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE)
(EFI_GUID *Guid, VOID *Table);

typedef EFI_STATUS (EFIAPI *EFI_CALCULATE_CRC32)
(VOID *Data, UINTN DataSize, UINT32 *Crc32);

#endif // UEFI_BOOT_MISC_H
