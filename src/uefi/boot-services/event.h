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

#ifndef UEFI_BOOT_EVENT_H
#define UEFI_BOOT_EVENT_H

#include "../types.h"

enum EFI_TIMER_DELAY {
    TimerCancel,
    TimerPeriodic,
    TimerRelative
};

typedef VOID (EFIAPI *EFI_EVENT_NOTIFY)
(EFI_EVENT Event, VOID *Context);

typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT)
(UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction,
 VOID *NotifyContext, EFI_EVENT *Event);

#define EVT_TIMER 0x80000000
#define EVT_RUNTIME 0x40000000
#define EVT_NOTIFY_WAIT 0x00000100
#define EVT_NOTIFY_SIGNAL 0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES 0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

typedef EFI_STATUS (EFIAPI *EFI_CREATE_EVENT_EX)
(UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction,
 CONST VOID *NotifyContext, CONST EFI_GUID *EventGuid, EFI_EVENT *Event);

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
{ 0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf }

#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
{ 0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96 }

#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
{ 0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, 0xf0, 0xd7, 0xab }

#define EFI_EVENT_GROUP_READY_TO_BOOT \
{ 0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5,0xd, 0x2b }

typedef EFI_STATUS (EFIAPI *EFI_CLOSE_EVENT)
(EFI_EVENT Event);

typedef EFI_STATUS (EFIAPI *EFI_SIGNAL_EVENT)
(EFI_EVENT Event);

typedef EFI_STATUS (EFIAPI *EFI_WAIT_FOR_EVENT)
(UINTN NumberOfEvents, EFI_EVENT *Event, UINTN *Index);

typedef EFI_STATUS (EFIAPI *EFI_CHECK_EVENT)
(EFI_EVENT Event);

typedef EFI_STATUS (EFIAPI *EFI_SET_TIMER)
(EFI_EVENT Event, EFI_TIMER_DELAY Type, UINT64 TriggerTime);

typedef EFI_TPL (EFIAPI *EFI_RAISE_TPL)
(EFI_TPL NewTpl);

#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31

typedef VOID (EFIAPI *EFI_RESTORE_TPL)
(EFI_TPL OldTpl);

#endif // UEFI_BOOT_EVENT_H
