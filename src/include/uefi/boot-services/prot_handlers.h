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

typedef enum {
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef struct {
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    UINT32 Attribute;
    UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE)
(EFI_HANDLE *Handle, EFI_GUID *Protocol, EFI_INTERFACE_TYPE InterfaceType,
 VOID *Interface);

typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE)
(EFI_HANDLE Handle, EFI_GUID *Protocol, VOID *Interface);

typedef EFI_STATUS (EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE)
(EFI_HANDLE Handle, EFI_GUID *Protocol, VOID *OldInterface, VOID *NewInterface);

typedef EFI_STATUS (EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY)
(EFI_GUID *Protocol, EFI_EVENT Event, VOID **Registration);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE)
(EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol, VOID *SearchKey,
 UINTN *BufferSize, EFI_HANDLE *Buffer);

typedef EFI_STATUS (EFIAPI *EFI_HANDLE_PROTOCOL)
(EFI_HANDLE Handle, EFI_GUID *Protocol, VOID **Interface);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_DEVICE_PATH)
(EFI_GUID *Protocol, EFI_DEVICE_PATH_PROTOCOL **DevicePath, EFI_HANDLE *Device);

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL)
(EFI_HANDLE Handle, EFI_GUID *Protocol, VOID **Interface,
 EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle, UINT32 Attributes);

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020

typedef EFI_STATUS (EFIAPI *EFI_CLOSE_PROTOCOL)
(EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_HANDLE AgentHandle,
 EFI_HANDLE ControllerHandle);

typedef EFI_STATUS (EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION)
(EFI_HANDLE Handle, EFI_GUID *Protocol,
 EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer, UINTN *EntryCount);

typedef EFI_STATUS (EFIAPI *EFI_CONNECT_CONTROLLER)
(EFI_HANDLE ControllerHandle, EFI_HANDLE *DriverImageHandle,
 EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, BOOLEAN Recursive);

typedef EFI_STATUS (EFIAPI *EFI_DISCONNECT_CONTROLLER)
(EFI_HANDLE ControllerHandle, EFI_HANDLE DriverImageHandle,
 EFI_HANDLE ChildHandle);

typedef EFI_STATUS (EFIAPI *EFI_PROTOCOLS_PER_HANDLE)
(EFI_HANDLE Handle, EFI_GUID ***ProtocolBuffer, UINTN *ProtocolBufferCount);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_HANDLE_BUFFER)
(EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol, VOID *SearchKey,
 UINTN *NoHandles, EFI_HANDLE **Buffer);

typedef EFI_STATUS (EFIAPI *EFI_LOCATE_PROTOCOL)
(EFI_GUID *Protocol, VOID *Registration, VOID **Interface);

typedef EFI_STATUS (EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)
(EFI_HANDLE *Handle, ...);

typedef EFI_STATUS (EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)
(EFI_HANDLE Handle, ...);
