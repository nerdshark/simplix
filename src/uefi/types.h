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

/*
 * UEFI data types. See UEFI spec. 2.3.1.
 */

#include <cstdint>

#define EFIAPI __attribute__((ms_abi))
#define CONST const

typedef uint8_t BOOLEAN;
constexpr BOOLEAN FALSE = 0;
constexpr BOOLEAN TRUE = 1;
typedef int64_t INTN;
typedef uint64_t UINTN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef char CHAR8;
static_assert(sizeof(wchar_t) == 2, "wchar_t is not 16-bit!");
typedef wchar_t CHAR16;
typedef void VOID;
typedef UINTN EFI_STATUS;
typedef VOID *EFI_EVENT;
typedef UINTN EFI_TPL;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;
typedef VOID *EFI_HANDLE;

struct EFI_GUID {
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4;
    UINT8 Data5;
    UINT8 Data6;
    UINT8 Data7;
    UINT8 Data8;
    UINT8 Data9;
    UINT8 Data11;
    UINT8 Data12;
};

struct EFI_DEVICE_PATH_PROTOCOL {
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
};

struct EFI_TIME {
    UINT16 Year;
    UINT8 Month;
    UINT8 Day;
    UINT8 Hour;
    UINT8 Minute;
    UINT8 Second;
    UINT8 Pad1;
    UINT32 Nanosecond;
    INT16 TimeZone;
    UINT8 DayLight;
    UINT8 Pad2;
};

struct WIN_CERTIFICATE {
    UINT32 dwLength;
    UINT16 wRevision;
    UINT16 wCertificateType;
    // UINT8 bCertificate[ANYSIZE_ARRAY]
};

struct WIN_CERTIFICATE_UEFI_GUID {
    WIN_CERTIFICATE Hdr;
    EFI_GUID CertType;
    UINT8 CertData[1];
};
