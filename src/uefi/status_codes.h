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

constexpr EFI_STATUS EFI_HIGH_BIT = 0x8000000000000000;

constexpr inline EFI_STATUS EFI_ERROR(EFI_STATUS x)
{
    return x | EFI_HIGH_BIT;
}

constexpr inline EFI_STATUS EFI_ERROR_TO_NORM(EFI_STATUS x)
{
    return x & ~EFI_HIGH_BIT;
}

constexpr inline bool EFI_STATUS_IS_ERROR(EFI_STATUS x)
{
    return x & EFI_HIGH_BIT;
}

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
