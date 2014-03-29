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

namespace CPUID {

inline void cpuid(uint32_t eax_in, uint32_t ecx_in, uint32_t *__restrict eax_out,
                  uint32_t *__restrict ebx_out, uint32_t *__restrict ecx_out,
                  uint32_t *__restrict edx_out)
{
    __asm volatile ("cpuid" : "=a"(*eax_out), "=b"(*ebx_out), "=c"(*ecx_out),
                    "=d"(*edx_out) : "a"(eax_in), "c"(ecx_in));
}

constexpr size_t VENDOR_STR_BUF_SIZE = 13;

// @buf needs to be at least VENDOR_STR_BUF_SIZ bytes large
inline char *get_vendor_string(char *buf)
{
    uint32_t eax;
    uint32_t *p = (uint32_t *)buf;
    cpuid(0x00, 0, &eax, p, p+2, p+1);
    buf[12] = '\0';
    return buf;
}

/*
 * Version Information as defined by Figure 3-5 in Intel's instruction set
 * manual.
 */
struct VersionInfo {
    uint32_t stepping_id:4;
    uint32_t model:4;
    uint32_t family_id:4;
    uint32_t proc_type:2;
    uint32_t res:2;
    uint32_t ext_model_id:4;
    uint32_t ext_family_id:8;
    uint32_t res2:4;
};

static_assert(sizeof(VersionInfo) == sizeof(uint32_t), "size mismatch");

inline VersionInfo get_version_info()
{
    VersionInfo eax;
    uint32_t ebx, ecx, edx;
    cpuid(0x01, 0x00, (uint32_t *)&eax, &ebx, &ecx, &edx);
    return eax;
}

struct AuxInfo {
    uint8_t brand_index;
    uint8_t clflush_line_size;
    uint8_t max_num_cpus;
    uint8_t initial_apic_id;
};

static_assert(sizeof(AuxInfo) == sizeof(uint32_t), "size mismatch");

inline AuxInfo get_aux_info()
{
    AuxInfo ebx;
    uint32_t eax, ecx, edx;
    cpuid(0x01, 0x00, &eax, (uint32_t *)&ebx, &ecx, &edx);
    return ebx;
}

/*
 * Feature information as returned by CPUID in ECX & EDX for EAX == 0x01.
 * Defined in Figures 3-6 & Figure 3-7 of Intel's instruction reference manual.
 */
struct FeatureInfo {
    uint32_t sse3:1; // SSE3 extensions
    uint32_t pclmulqdq:1; // Carryless Multiplication
    uint32_t dtes64:1; // 64-bit DS Area
    uint32_t monitor:1; // MONITOR/MWAIT
    uint32_t ds_cpl:1; // CPL Qualified Debug Store
    uint32_t vmx:1; // Virtual Machine Extensions
    uint32_t smx:1; // Safer Mode Extensions
    uint32_t est:1; // Enhanced Intel SpeedStep Technology
    uint32_t tm2:1; // Thermal Monitor 2
    uint32_t ssse3:1; // SSSE3 Extensions
    uint32_t cnxt_id:1; // L1 Context ID
    uint32_t res:1;
    uint32_t fma:1; // Fused Multiply Add
    uint32_t cmpxchg16b:1;
    uint32_t xtpr_update_control:1;
    uint32_t pdcm:1; // Perf/Debug Capability MSR
    uint32_t res2:1;
    uint32_t pcid:1; // Process-context Identifiers
    uint32_t dca:1; // Direct Cache Access
    uint32_t sse4_1:1; // SSE4.1
    uint32_t sse4_2:1; // SSE4.2
    uint32_t x2apic:1;
    uint32_t movbe:1;
    uint32_t popcnt:1;
    uint32_t tsc_deadline:1;
    uint32_t aes:1;
    uint32_t xsave:1;
    uint32_t osxsave:1;
    uint32_t avx:1;
    uint32_t f16c:1;
    uint32_t rdrand:1;
    uint32_t zero:1;

    uint32_t fpu:1; // x87 FPU on Chip
    uint32_t vme:1; // Virtual-8086 Mode Enhancement
    uint32_t de:1; // Debugging Extensions
    uint32_t pse:1; // Page Size Extensions
    uint32_t tsc:1; // Time Stamp Counter
    uint32_t msr:1; // RDMSR and WRMSR Support
    uint32_t pae:1; // Physical Address Extensions
    uint32_t mce:1; // Machine Check Exception
    uint32_t cx8:1; // CMPXCHG8B Inst.
    uint32_t apic:1; // APIC on Chip
    uint32_t res3:1;
    uint32_t sep:1; // SYSENTER and SYSEXIT
    uint32_t mtrr:1; // Memory Type Range Registers
    uint32_t pge:1; // PTE Global Bit
    uint32_t mca:1; // Machine Check Architecture
    uint32_t cmov:1; // Conditional Move/Compare Instruction
    uint32_t pat:1; // Page Attribute Table
    uint32_t pse_36:1; // Page Size Extension
    uint32_t psn:1; // Processor Serial Number
    uint32_t clfsh:1; // CFLUSH instruction
    uint32_t res4:1;
    uint32_t ds:1; // Debug Store
    uint32_t acpi:1; // Thermal Monitor and Clock Ctrl
    uint32_t mmx:1; // MMX Technology
    uint32_t fxsr:1; // FXSAVE/FXRSTOR
    uint32_t sse:1; // SSE Extensions
    uint32_t sse2:1; // SSE2 Extensions
    uint32_t ss:1; // Self Snoop
    uint32_t htt:1; // Multi-threading
    uint32_t tm:1; // Therm. Monitor
    uint32_t res5:1;
    uint32_t pbe:1; // Pend. Brk. EN.
};

static_assert(sizeof(FeatureInfo) == sizeof(uint64_t), "size mismatch");

inline FeatureInfo get_feature_info()
{
    FeatureInfo ecx_edx;
    uint32_t eax, ebx;
    cpuid(0x01, 0x00, &eax, &ebx, (uint32_t *)&ecx_edx, (uint32_t *)&ecx_edx+1);
    return ecx_edx;
}

} // namespace CPUID end
