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

#ifndef UEFI_STATUS_CODES_H
#define UEFI_STATUS_CODES_H

enum {
    EFI_SUCCESS = 0
};

enum {
    EFI_LOAD_ERROR = 1,
    EFI_INVALID_PARAMETER = 2,
    EFI_UNSUPPORTED = 3,
    EFI_BAD_BUFFER_SIZE = 4,
    EFI_BUFFER_TOO_SMALL = 5,
    EFI_NOT_READY = 6,
    EFI_DEVICE_ERROR = 7,
    EFI_WRITE_PROTECTED = 8,
    EFI_OUT_OF_RESOURCES = 9,
    EFI_VOLUME_CORRUPTED = 10,
    EFI_VOLUME_FULL = 11,
    EFI_NO_MEDIA = 12,
    EFI_MEDIA_CHANGED = 13,
    EFI_NOT_FOUND = 14,
    EFI_ACCESS_DENIED = 15,
    EFI_NO_RESPONSE = 16,
    EFI_NO_MAPPING = 17,
    EFI_TIMEOUT = 18,
    EFI_NOT_STARTED = 19,
    EFI_ALREADY_STARTED = 20,
    EFI_ABORTED = 21,
    EFI_ICMP_ERROR = 22,
    EFI_TFTP_ERROR = 23,
    EFI_PROTOCOL_ERROR = 24,
    EFI_INCOMPATIBLE_VERSION = 25,
    EFI_SECURITY_VIOLATION = 26,
    EFI_CRC_ERROR = 27,
    EFI_END_OF_MEDIA = 28,
    EFI_END_OF_FILE = 31,
    EFI_INVALID_LANGUAGE = 32,
    EFI_COMPROMISED_DATA = 33,
    EFI_IP_ADDRESS_CONFLICT = 34
};

enum {
    EFI_WARN_UNKNOWN_GLYPH = 1,
    EFI_WARN_DELETE_FAILURE = 2,
    EFI_WARN_WRITE_FAILURE = 3,
    EFI_WARN_BUFFER_TOO_SMALL = 4,
    EFI_WARN_STALE_DATA = 5
};

#endif // UEFI_STATUS_CODES_H
