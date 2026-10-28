/* SPDX-License-Identifier: CC0-1.0
 *
 * Helpers for the GENERATED native module table (tools/gen_overlay_registry.py ->
 * ovl_native_gen.c, docs/OVERLAY.md section 8): symbol spelling inside top-level
 * asm (the segment labels) and the MAIN -> overlay import trampoline.
 *
 * The trampoline keeps the caller's frame untouched (cdecl arguments, sret
 * pointer, eax/edx/st(0) returns pass straight through: 21 imports have different
 * prototypes in different overlays, so the caller's declaration decides): it asks
 * the module table for the host function of (import index, active module) and
 * tail-jumps to it.  eax/ecx/edx are caller-saved, so the lookup may clobber them.
 * i686 only (PLAN.md D1); x64 (P7) needs its own spelling.
 */
#ifndef RG_NATIVE_OVL_GEN_H
#define RG_NATIVE_OVL_GEN_H

#include <stdint.h>
#include <string.h>

/* lifted ctors: float arguments from their bit patterns */
static inline float rg_ovl_bits_f32(int bits)
{
    float f;
    memcpy(&f, &bits, sizeof f);
    return f;
}

#define RG_OVL_STR2(x) #x
#define RG_OVL_STR(x) RG_OVL_STR2(x)
/* C symbol as the assembler sees it ("_name" on i686 Windows, "name" on ELF). */
#define RG_OVL_ASM_SYM(n) RG_OVL_STR(__USER_LABEL_PREFIX__) #n
#define RG_OVL_ASM_BSS_SECTION ".bss"
#define RG_OVL_ASM_PREVIOUS ".text"

#if defined(__i386__)
#define RG_OVL_TRAMPOLINE(name, table, idx)                                   \
    __attribute__((naked, used)) void name(void)                              \
    {                                                                         \
        __asm__ volatile(                                                     \
            "pushl $" #idx "\n\t"                                             \
            "pushl $" RG_OVL_ASM_SYM(table) "\n\t"                            \
            "call " RG_OVL_ASM_SYM(rg_ovl_call_import_at) "\n\t"              \
            "addl $8, %esp\n\t"                                               \
            "jmp *%eax\n\t");                                                 \
    }
#elif defined(__x86_64__)
/* Win64 (docs/X64-PLAN.md step 4): the argument registers (rcx rdx r8 r9, xmm0-3)
 * survive the resolver call; 32 bytes of shadow space; rsp 16-aligned at the call
 * (entry rsp = 8 mod 16, 4 pushes, 0x68 = 4 x 16 xmm + 32 shadow + 8). */
#define RG_OVL_TRAMPOLINE(name, table, idx)                                   \
    __attribute__((naked, used)) void name(void)                              \
    {                                                                         \
        __asm__ volatile(                                                     \
            "pushq %rcx\n\t"                                                  \
            "pushq %rdx\n\t"                                                  \
            "pushq %r8\n\t"                                                   \
            "pushq %r9\n\t"                                                   \
            "subq $0x68, %rsp\n\t"                                            \
            "movdqu %xmm0, 0x20(%rsp)\n\t"                                    \
            "movdqu %xmm1, 0x30(%rsp)\n\t"                                    \
            "movdqu %xmm2, 0x40(%rsp)\n\t"                                    \
            "movdqu %xmm3, 0x50(%rsp)\n\t"                                    \
            "leaq " RG_OVL_ASM_SYM(table) "(%rip), %rcx\n\t"                  \
            "movl $" #idx ", %edx\n\t"                                        \
            "call " RG_OVL_ASM_SYM(rg_ovl_call_import_at) "\n\t"              \
            "movdqu 0x20(%rsp), %xmm0\n\t"                                    \
            "movdqu 0x30(%rsp), %xmm1\n\t"                                    \
            "movdqu 0x40(%rsp), %xmm2\n\t"                                    \
            "movdqu 0x50(%rsp), %xmm3\n\t"                                    \
            "addq $0x68, %rsp\n\t"                                            \
            "popq %r9\n\t"                                                    \
            "popq %r8\n\t"                                                    \
            "popq %rdx\n\t"                                                   \
            "popq %rcx\n\t"                                                   \
            "jmp *%rax\n\t");                                                 \
    }
#else
#error "RG_OVL_TRAMPOLINE: i686 or x64 only"
#endif

#endif
