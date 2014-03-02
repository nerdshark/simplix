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

#include <uefi/uefi.h>

static const CHAR16 *status_array[] = {
    [EFI_SUCCESS] = L"Success",
    [EFI_ERROR_TO_NORM(EFI_LOAD_ERROR)] = L"Load error",
    [EFI_ERROR_TO_NORM(EFI_INVALID_PARAMETER)] = L"Invalid parameter",
    [EFI_ERROR_TO_NORM(EFI_UNSUPPORTED)] = L"Unsupported",
    [EFI_ERROR_TO_NORM(EFI_BAD_BUFFER_SIZE)] = L"Bad buffer size",
    [EFI_ERROR_TO_NORM(EFI_BUFFER_TOO_SMALL)] = L"Buffer too small",
    [EFI_ERROR_TO_NORM(EFI_NOT_READY)] = L"Not ready",
    [EFI_ERROR_TO_NORM(EFI_DEVICE_ERROR)] = L"Device error",
    [EFI_ERROR_TO_NORM(EFI_WRITE_PROTECTED)] = L"Write protected",
    [EFI_ERROR_TO_NORM(EFI_OUT_OF_RESOURCES)] = L"Out of resources",
    [EFI_ERROR_TO_NORM(EFI_VOLUME_CORRUPTED)] = L"Volume corrupted",
    [EFI_ERROR_TO_NORM(EFI_VOLUME_FULL)] = L"Volume full",
    [EFI_ERROR_TO_NORM(EFI_NO_MEDIA)] = L"No media",
    [EFI_ERROR_TO_NORM(EFI_MEDIA_CHANGED)] = L"Media changed",
    [EFI_ERROR_TO_NORM(EFI_NOT_FOUND)] = L"Not found",
    [EFI_ERROR_TO_NORM(EFI_ACCESS_DENIED)] = L"Access denied",
    [EFI_ERROR_TO_NORM(EFI_NO_RESPONSE)] = L"No response",
    [EFI_ERROR_TO_NORM(EFI_NO_MAPPING)] = L"No mapping",
    [EFI_ERROR_TO_NORM(EFI_TIMEOUT)] = L"Timeout",
    [EFI_ERROR_TO_NORM(EFI_NOT_STARTED)] = L"Not started",
    [EFI_ERROR_TO_NORM(EFI_ALREADY_STARTED)] = L"Already started",
    [EFI_ERROR_TO_NORM(EFI_ABORTED)] = L"Aborted",
    [EFI_ERROR_TO_NORM(EFI_ICMP_ERROR)] = L"ICMP error",
    [EFI_ERROR_TO_NORM(EFI_TFTP_ERROR)] = L"TFTP error",
    [EFI_ERROR_TO_NORM(EFI_PROTOCOL_ERROR)] = L"Protocol error",
    [EFI_ERROR_TO_NORM(EFI_INCOMPATIBLE_VERSION)] = L"Incompatible version",
    [EFI_ERROR_TO_NORM(EFI_SECURITY_VIOLATION)] = L"Security violation",
    [EFI_ERROR_TO_NORM(EFI_CRC_ERROR)] = L"CRC error",
    [EFI_ERROR_TO_NORM(EFI_END_OF_MEDIA)] = L"End of media",
    [29] = L"",
    [30] = L"",
    [EFI_ERROR_TO_NORM(EFI_END_OF_FILE)] = L"End of file",
    [EFI_ERROR_TO_NORM(EFI_INVALID_LANGUAGE)] = L"Invalid language",
    [EFI_ERROR_TO_NORM(EFI_COMPROMISED_DATA)] = L"Compromised data",
    [EFI_ERROR_TO_NORM(EFI_IP_ADDRESS_CONFLICT)] = L"IP address conflict"
};

const CHAR16 *uefi_error_to_string(EFI_STATUS status)
{
    return status_array[EFI_ERROR_TO_NORM(status)];
}

void uefi_die(const EFI_SYSTEM_TABLE *systab, EFI_STATUS status, const CHAR16 *msg)
{
    uefi_print(systab->ConOut, msg);
    uefi_print(systab->ConOut, L": ");
    uefi_print(systab->ConOut, uefi_error_to_string(status));
    uefi_print(systab->ConOut, L"\r\n");
    __asm__ volatile ("cli \n\t hlt");
}

EFI_GRAPHICS_OUTPUT_PROTOCOL *uefi_get_gop(EFI_HANDLE handle,
                                           const EFI_SYSTEM_TABLE *systab)
{
    EFI_BOOT_SERVICES *bs = systab->BootServices;

    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    UINTN num;
    EFI_HANDLE *handles;

    EFI_STATUS status = bs->LocateHandleBuffer(ByProtocol, &gop_guid, NULL,
                                               &num, &handles);
    if (EFI_STATUS_IS_ERROR(status))
        uefi_die(systab, status, L"LocateHandleBuffer");

    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;

    for (UINTN i = 0; i < num; ++i) {
        status = bs->OpenProtocol(handles[i], &gop_guid, (VOID **)&gop, handle,
                                  NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
        if (EFI_STATUS_IS_ERROR(status))
            uefi_die(systab, status, L"OpenProtocol");

        if (gop->Mode->Info->PixelFormat != PixelBltOnly &&
            gop->Mode->Info->PixelFormat != PixelBitMask)
            return gop;
    }

    return NULL;
}

void uefi_get_memory_map(const EFI_SYSTEM_TABLE *systab, struct uefi_memory_map *map)
{
    EFI_BOOT_SERVICES *bs = systab->BootServices;

    map->memory_map_size = 0;
    EFI_STATUS status = bs->GetMemoryMap(&map->memory_map_size, map->memory_map,
                                         &map->map_key, &map->descriptor_size,
                                         &map->descriptor_version);
    if (EFI_STATUS_IS_ERROR(status) && status != EFI_BUFFER_TOO_SMALL)
        uefi_die(systab, status, L"GetMemoryMap");

    do {
        map->memory_map_size *= 2;
        status = bs->AllocatePool(EfiLoaderData, map->memory_map_size,
                                  (VOID **)&map->memory_map);
        if (EFI_STATUS_IS_ERROR(status))
            uefi_die(systab, status, L"AllocatePool");

        status = bs->GetMemoryMap(&map->memory_map_size, map->memory_map,
                                  &map->map_key, &map->descriptor_size,
                                  &map->descriptor_version);
        if (EFI_STATUS_IS_ERROR(status) && status != EFI_BUFFER_TOO_SMALL)
            uefi_die(systab, status, L"GetMemoryMap");
    } while (status == EFI_BUFFER_TOO_SMALL);
}
