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

#include <cstdint>

namespace Descriptor {

enum PrivilegeLevel {
    KERNEL = 0,
    USER = 3
};

enum Conformity{
    NON_CONFORMING = 0,
    CONFORMING = 1
};

enum Presence {
    NOT_PRESENT = 0,
    PRESENT = 1
};

enum SystemType {
    LDT = 0b0010,
    TSS_AVAIL = 0b1001,
    TSS_BUSY = 0b1011,
    CALL_GATE = 0b1100,
    INT_GATE = 0b1110,
    TRAP_GATE = 0b1111
};

enum TableIndicator{
    TI_GDT = 0,
    TI_LDT = 1
};

/*
 * Structure of a Segment Selector.
 */
struct SegmentSelector {
    uint16_t rpl:2; // Requestor Privilege Level
    uint16_t ti:1; // Table Indicator
    uint16_t si:13; // Selector Index
};

/*
 * Structure of a Descriptor Table Register (GDTR and IDTR).
 */
struct Dtr {
    uint16_t limit;
    uint64_t address;
} __attribute((packed));

/*
 * Structure of a Code Segment Descriptor in Long Mode.
 */
struct CSDescriptor {
    uint32_t res;
    uint8_t res2;
    uint8_t res3:2;
    uint8_t c:1;
    uint8_t one1:1;
    uint8_t one2:1;
    uint8_t dpl:2;
    uint8_t p:1;
    uint8_t res5:5;
    uint8_t l:1;
    uint8_t d:1;
    uint8_t res6:1;
    uint8_t res7;

    CSDescriptor(Conformity conform, PrivilegeLevel priv, Presence present)
        : c(conform), one1(1), one2(1), dpl(priv), p(present), l(1) { }
};

/*
 * Structure of a System-Segment Descriptor.
 */
struct SystemDescriptor {
    uint16_t seg_limit1;
    uint16_t base_addr1;
    uint8_t base_addr2;
    uint8_t type:4;
    uint8_t zero:1;
    uint8_t dpl:2;
    uint8_t p:1;
    uint8_t seg_limit2:4;
    uint8_t avl:1;
    uint8_t res:2;
    uint8_t g:1;
    uint8_t base_addr3;
    uint32_t base_addr4;
    uint8_t ign;
    uint8_t zero2:4;
    uint8_t ign2:4;
    uint16_t ign3;
};

/*
 * Structure of a Call-Gate descriptor.
 */
struct CallGateDescriptor {
    uint16_t target_offset1;
    SegmentSelector target_selector;
    uint8_t ign;
    uint8_t type:4;
    uint8_t zero:1;
    uint8_t dpl:2;
    uint8_t p:1;
    uint16_t target_offset2;
    uint32_t target_offset3;
    uint8_t ign2;
    uint8_t zero2:5;
    uint8_t ign3:3;
    uint16_t ign4;
};

/*
 * Structure of an Interrupt-Gate and Trap-Gate descriptor.
 */
struct IntOrTrapGateDescriptor {
    uint16_t target_offset1;
    SegmentSelector target_selector;
    uint8_t ist:3;
    uint8_t ign:5;
    uint8_t type:4;
    uint8_t zero:1;
    uint8_t dpl:2;
    uint8_t p:1;
    uint16_t target_offset2;
    uint32_t target_offset3;
    uint32_t ign2;

    IntOrTrapGateDescriptor(uint64_t toff, SegmentSelector sel, SystemType type,
                            PrivilegeLevel priv, Presence present)
        : target_offset1(toff & 0xffff), target_selector(sel), type(type),
          dpl(priv), p(present), target_offset2((toff >> 16) & 0xffff),
          target_offset3((toff >> 32) & 0xffffffff) { }
};

inline void load_gdtr(const Dtr *gdtr)
{
    __asm volatile ("lgdt %0" : : "m"(*gdtr));
}

inline void store_gdtr(Dtr *gdtr)
{
    __asm volatile ("sgdt %0" : "=m"(*gdtr));
}

inline void load_idtr(const Dtr *idtr)
{
    __asm volatile ("lidt %0" : : "m"(*idtr));
}

inline void store_idtr(Dtr *idtr)
{
    __asm volatile ("sidt %0" : "=m"(*idtr));
}

} // namespace Descriptor end
