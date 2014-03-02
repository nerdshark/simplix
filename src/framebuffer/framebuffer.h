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

#include <stdint.h>
#include <stddef.h>
#include <uefi/protocols/console/gop.h>

// We support only the basic colors for now
typedef enum {
    FRAMEBUFFER_BLACK,
    FRAMEBUFFER_WHITE,
    FRAMEBUFFER_RED,
    FRAMEBUFFER_LIME,
    FRAMEBUFFER_BLUE,
    FRAMEBUFFER_YELLOW,
    FRAMEBUFFER_CYAN,
    FRAMEBUFFER_MAGENTA,
    FRAMEBUFFER_SILVER,
    FRAMEBUFFER_GRAY,
    FRAMEBUFFER_MAROON,
    FRAMEBUFFER_OLIVE,
    FRAMEBUFFER_GREEN,
    FRAMEBUFFER_PURPLE,
    FRAMEBUFFER_TEAL,
    FRAMEBUFFER_NAVY
} framebuffer_color_t;

// Call that the first time before doing anything with the framebuffer!
void framebuffer_init(const EFI_GRAPHICS_OUTPUT_PROTOCOL *gop);

int framebuffer_put_string(const char *s, framebuffer_color_t fg,
                           framebuffer_color_t bg);
