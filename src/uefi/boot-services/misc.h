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
