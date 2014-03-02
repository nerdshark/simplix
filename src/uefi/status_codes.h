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

#define EFI_HIGH_BIT 0x8000000000000000

#define EFI_ERROR(x) ((x) | EFI_HIGH_BIT)

#define EFI_ERROR_TO_NORM(x) ((x) & ~EFI_HIGH_BIT)

#define EFI_STATUS_IS_ERROR(x) ((x) & EFI_HIGH_BIT)

enum {
    EFI_SUCCESS = 0,
    EFI_LOAD_ERROR = EFI_ERROR(1),
    EFI_INVALID_PARAMETER = EFI_ERROR(2),
    EFI_UNSUPPORTED = EFI_ERROR(3),
    EFI_BAD_BUFFER_SIZE = EFI_ERROR(4),
    EFI_BUFFER_TOO_SMALL = EFI_ERROR(5),
    EFI_NOT_READY = EFI_ERROR(6),
    EFI_DEVICE_ERROR = EFI_ERROR(7),
    EFI_WRITE_PROTECTED = EFI_ERROR(8),
    EFI_OUT_OF_RESOURCES = EFI_ERROR(9),
    EFI_VOLUME_CORRUPTED = EFI_ERROR(10),
    EFI_VOLUME_FULL = EFI_ERROR(11),
    EFI_NO_MEDIA = EFI_ERROR(12),
    EFI_MEDIA_CHANGED = EFI_ERROR(13),
    EFI_NOT_FOUND = EFI_ERROR(14),
    EFI_ACCESS_DENIED = EFI_ERROR(15),
    EFI_NO_RESPONSE = EFI_ERROR(16),
    EFI_NO_MAPPING = EFI_ERROR(17),
    EFI_TIMEOUT = EFI_ERROR(18),
    EFI_NOT_STARTED = EFI_ERROR(19),
    EFI_ALREADY_STARTED = EFI_ERROR(20),
    EFI_ABORTED = EFI_ERROR(21),
    EFI_ICMP_ERROR = EFI_ERROR(22),
    EFI_TFTP_ERROR = EFI_ERROR(23),
    EFI_PROTOCOL_ERROR = EFI_ERROR(24),
    EFI_INCOMPATIBLE_VERSION = EFI_ERROR(25),
    EFI_SECURITY_VIOLATION = EFI_ERROR(26),
    EFI_CRC_ERROR = EFI_ERROR(27),
    EFI_END_OF_MEDIA = EFI_ERROR(28),
    EFI_END_OF_FILE = EFI_ERROR(31),
    EFI_INVALID_LANGUAGE = EFI_ERROR(32),
    EFI_COMPROMISED_DATA = EFI_ERROR(33),
    EFI_IP_ADDRESS_CONFLICT = EFI_ERROR(34),
    EFI_WARN_UNKNOWN_GLYPH = 1,
    EFI_WARN_DELETE_FAILURE = 2,
    EFI_WARN_WRITE_FAILURE = 3,
    EFI_WARN_BUFFER_TOO_SMALL = 4,
    EFI_WARN_STALE_DATA = 5
};
