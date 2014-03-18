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
