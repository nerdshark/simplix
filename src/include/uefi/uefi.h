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

#ifndef UEFI_H
#define UEFI_H

#include <uefi/systab.h>
#include <uefi/status_codes.h>

namespace UEFI {

inline EFI_STATUS print(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *out, CONST CHAR16 *s)
{
    return out->OutputString(out, (CHAR16 *)s);
}

const CHAR16 *status_to_string[] = {
    [EFI_SUCCESS] = u"Success",
    [EFI_LOAD_ERROR] = u"Load error",
    [EFI_INVALID_PARAMETER] = u"Invalid parameter",
    [EFI_UNSUPPORTED] = u"Unsupported",
    [EFI_BAD_BUFFER_SIZE] = u"Bad buffer size",
    [EFI_BUFFER_TOO_SMALL] = u"Buffer too small",
    [EFI_NOT_READY] = u"Not ready",
    [EFI_DEVICE_ERROR] = u"Device error",
    [EFI_WRITE_PROTECTED] = u"Write protected",
    [EFI_OUT_OF_RESOURCES] = u"Out of resources",
    [EFI_VOLUME_CORRUPTED] = u"Volume corrupted",
    [EFI_VOLUME_FULL] = u"Volume full",
    [EFI_NO_MEDIA] = u"No media",
    [EFI_MEDIA_CHANGED] = u"Media changed",
    [EFI_NOT_FOUND] = u"Not found",
    [EFI_ACCESS_DENIED] = u"Access denied",
    [EFI_NO_RESPONSE] = u"No response",
    [EFI_NO_MAPPING] = u"No mapping",
    [EFI_TIMEOUT] = u"Timeout",
    [EFI_NOT_STARTED] = u"Not started",
    [EFI_ALREADY_STARTED] = u"Already started",
    [EFI_ABORTED] = u"Aborted",
    [EFI_ICMP_ERROR] = u"ICMP error",
    [EFI_TFTP_ERROR] = u"TFTP error",
    [EFI_PROTOCOL_ERROR] = u"Protocol error",
    [EFI_INCOMPATIBLE_VERSION] = u"Incompatible version",
    [EFI_SECURITY_VIOLATION] = u"Security violation",
    [EFI_CRC_ERROR] = u"CRC error",
    [EFI_END_OF_MEDIA] = u"End of media",
    [29] = u"",
    [30] = u"",
    [EFI_END_OF_FILE] = u"End of file",
    [EFI_INVALID_LANGUAGE] = u"Invalid language",
    [EFI_COMPROMISED_DATA] = u"Compromised data",
    [EFI_IP_ADDRESS_CONFLICT] = u"IP address conflict"
};

} // namespace UEFI end

#endif // UEFI_H
