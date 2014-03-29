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
