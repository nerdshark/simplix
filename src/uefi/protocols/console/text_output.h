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

#ifndef UEFI_PROT_CONSOLE_TEXT_OUTPUT_H
#define UEFI_PROT_CONSOLE_TEXT_OUTPUT_H

#include "../../types.h"

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
{ 0x387477c2, 0x69c7, 0x11d2, 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

struct SIMPLE_TEXT_OUTPUT_MODE {
    INT32 MaxMode;
    // current settings
    INT32 Mode;
    INT32 Attribute;
    INT32 CursorColumn;
    INT32 CursorRow;
    BOOLEAN CursorVisible;
};

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_TEXT_RESET)
(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING)
(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

// XXX: boxdraw constants UEFI spec page 453/4

typedef EFI_STATUS (EFIAPI *EFI_TEXT_TEST_STRING)
(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_QUERY_MODE)
(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber, UINTN *Columns,
 UINTN *Rows);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_MODE)
(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_ATTRIBUTE)
(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Attribute);

// XXX: Atribute constants

typedef EFI_STATUS (EFIAPI *EFI_TEXT_CLEAR_SCREEN)
(SIMPLE_TEXT_OUTPUT_MODE *This);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_CURSOR_POSITION)
(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Column, UINTN Row);

typedef EFI_STATUS (EFIAPI *EFI_TEXT_ENABLE_CURSOR)
(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN Visible);

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET Reset;
    EFI_TEXT_STRING OutputString;
    EFI_TEXT_TEST_STRING TestString;
    EFI_TEXT_QUERY_MODE QueryMode;
    EFI_TEXT_SET_MODE SetMode;
    EFI_TEXT_SET_ATTRIBUTE SetAttribute;
    EFI_TEXT_CLEAR_SCREEN ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR EnableCursor;
    SIMPLE_TEXT_OUTPUT_MODE *Mode;
};

#endif // UEFI_PROT_CONSOLE_TEXT_OUTPUT_H
