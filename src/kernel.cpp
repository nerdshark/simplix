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

extern "C" {

// gnu-efi doesn't declare its functions as 'extern '"C"' if compiled
// with a C++-compiler. But we need C-linkage of these.
#include <efi.h>
#include <efilib.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE handle, EFI_SYSTEM_TABLE *systab)
{
    InitializeLib(handle, systab);

    // Print() takes non-const CHAR16 *, but a literal is const...
    Print((CHAR16 *)L"Welcome to Simplix!\n");

    asm volatile ("cli \n\t hlt");
    return EFI_SUCCESS;
}

} // extern C
