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

#include <cstdint>
#include <misc.h>

namespace Descriptor {

enum class PrivilegeLevel {
    KERNEL = 0,
    USER = 3
};

enum class Conformity {
    NON_CONFORMING = 0,
    CONFORMING = 1
};

enum class Presence {
    NOT_PRESENT = 0,
    PRESENT = 1
};

enum class SystemType {
    LDT = 0b0010,
    TSS_AVAIL = 0b1001,
    TSS_BUSY = 0b1011,
    CALL_GATE = 0b1100,
    INT_GATE = 0b1110,
    TRAP_GATE = 0b1111
};

enum class TableIndicator {
    GDT = 0,
    LDT = 1
};

/*
 * Structure of a Segment Selector.
 */
struct SegmentSelector {
    uint16_t rpl:2; // Requestor Privilege Level
    uint16_t ti:1; // Table Indicator
    uint16_t si:13; // Selector Index
};

inline uint16_t segment_selector_to_scalar(SegmentSelector sel)
{
    uint16_t val = sel.si;
    val = (val << 1) | sel.ti;
    val = (val << 2) | sel.rpl;
    return val;
}

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
        : c(to_underlying_type(conform)),
          one1(1),
          one2(1),
          dpl(to_underlying_type(priv)),
          p(to_underlying_type(present)),
          l(1) { }
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
    uint16_t target_selector;
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
    uint16_t target_selector;
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
        : target_offset1(toff & 0xffff),
          target_selector(segment_selector_to_scalar(sel)),
          type(to_underlying_type(type)),
          dpl(to_underlying_type(priv)),
          p(to_underlying_type(present)),
          target_offset2((toff >> 16) & 0xffff),
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
