/* SPDX-License-Identifier: CC0-1.0
 *
 * Helpers for the GENERATED overlay sources (tools/gen_overlay_registry.py,
 * docs/OVERLAY.md): symbol spelling inside top-level asm, arena / MAIN-bss
 * address macros used by the lifted static initializers, and the MAIN ->
 * overlay import trampoline.  i686 only (PLAN.md D1); the trampoline is the
 * one piece that changes for x64 (P7).
 */
#ifndef RG_PS2_OVL_ASM_H
#define RG_PS2_OVL_ASM_H

#include "../../native/ovl/ovl_gen.h"   /* asm spelling, trampoline, bit casts (src/native/ovl) */

#define RG_OVL_ARENA_BASE 0x004E9E80u
extern unsigned char rg_ovl_arena[];
/* Host address of a PS2 arena address (the shared block, whatever is resident). */
#define RG_OVL_ARENA_PTR(a) ((void *)(rg_ovl_arena + ((uint32_t)(a) - RG_OVL_ARENA_BASE)))

/* MAIN .bss without a symbol (the overlays' per-TU ios_base::Init objects and
 * their RegisterGlobalObject nodes live in MAIN's .sbss, reached through MAIN's
 * $gp).  MAIN's .bss is one block at the snapshot (data2c: data2c_main_bss,
 * 0x00481080..0x004E9E80); the integration may rename it with RG_MAIN_BSS_SYM. */
#ifndef RG_MAIN_BSS_SYM
#define RG_MAIN_BSS_SYM data2c_main_bss
#endif
#define RG_MAIN_BSS_BASE 0x00481080u
extern unsigned char RG_MAIN_BSS_SYM[];
#define RG_MAIN_BSS_PTR(a) ((void *)(RG_MAIN_BSS_SYM + ((uint32_t)(a) - RG_MAIN_BSS_BASE)))

#endif
