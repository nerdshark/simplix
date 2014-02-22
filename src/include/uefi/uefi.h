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

#include <uefi/systab.h>
#include <uefi/status_codes.h>
#include <uefi/protocols/console/console.h>

namespace UEFI {

inline EFI_STATUS print(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *out, CONST CHAR16 *s)
{
    return out->OutputString(out, (CHAR16 *)s);
}

CONST CHAR16 *uefi_status_to_string[] = {
    [EFI_SUCCESS] = L"Success",
    [EFI_LOAD_ERROR] = L"Load error",
    [EFI_INVALID_PARAMETER] = L"Invalid parameter",
    [EFI_UNSUPPORTED] = L"Unsupported",
    [EFI_BAD_BUFFER_SIZE] = L"Bad buffer size",
    [EFI_BUFFER_TOO_SMALL] = L"Buffer too small",
    [EFI_NOT_READY] = L"Not ready",
    [EFI_DEVICE_ERROR] = L"Device error",
    [EFI_WRITE_PROTECTED] = L"Write protected",
    [EFI_OUT_OF_RESOURCES] = L"Out of resources",
    [EFI_VOLUME_CORRUPTED] = L"Volume corrupted",
    [EFI_VOLUME_FULL] = L"Volume full",
    [EFI_NO_MEDIA] = L"No media",
    [EFI_MEDIA_CHANGED] = L"Media changed",
    [EFI_NOT_FOUND] = L"Not found",
    [EFI_ACCESS_DENIED] = L"Access denied",
    [EFI_NO_RESPONSE] = L"No response",
    [EFI_NO_MAPPING] = L"No mapping",
    [EFI_TIMEOUT] = L"Timeout",
    [EFI_NOT_STARTED] = L"Not started",
    [EFI_ALREADY_STARTED] = L"Already started",
    [EFI_ABORTED] = L"Aborted",
    [EFI_ICMP_ERROR] = L"ICMP error",
    [EFI_TFTP_ERROR] = L"TFTP error",
    [EFI_PROTOCOL_ERROR] = L"Protocol error",
    [EFI_INCOMPATIBLE_VERSION] = L"Incompatible version",
    [EFI_SECURITY_VIOLATION] = L"Security violation",
    [EFI_CRC_ERROR] = L"CRC error",
    [EFI_END_OF_MEDIA] = L"End of media",
    [29] = L"",
    [30] = L"",
    [EFI_END_OF_FILE] = L"End of file",
    [EFI_INVALID_LANGUAGE] = L"Invalid language",
    [EFI_COMPROMISED_DATA] = L"Compromised data",
    [EFI_IP_ADDRESS_CONFLICT] = L"IP address conflict"
};

}
