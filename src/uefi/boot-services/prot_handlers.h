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

enum EFI_INTERFACE_TYPE {
    EFI_NATIVE_INTERFACE
};

enum EFI_LOCATE_SEARCH_TYPE {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
};

struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY {
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    UINT32 Attribute;
    UINT32 OpenCount;
};

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
