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

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02

#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

struct EFI_TIME_CAPABILITIES {
    UINT32 Resolution;
    UINT32 Accuracy;
    BOOLEAN SetsToZero;
};

typedef EFI_STATUS (EFIAPI *EFI_GET_TIME)
(EFI_TIME *Time, EFI_TIME_CAPABILITIES *Capabilities);

typedef EFI_STATUS (EFIAPI *EFI_SET_TIME)
(EFI_TIME *Time);

typedef EFI_STATUS (EFIAPI *EFI_GET_WAKEUP_TIME)
(BOOLEAN *Enabled, BOOLEAN *Pending, EFI_TIME *Time);

typedef EFI_STATUS (EFIAPI *EFI_SET_WAKEUP_TIME)
(BOOLEAN Enable, EFI_TIME *Time);
