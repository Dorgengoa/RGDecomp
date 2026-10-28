/* SPDX-License-Identifier: CC0-1.0
 * Synthetic trace symbols for rg-runtime-demo (docs/TRACE-PORT.md "Demo"):
 * the demo guest's result globals at made-up PS2 addresses, so the whole
 * recorder -> TSV -> compare pipeline runs before the game links. */
#ifndef RG_TRACE_DEMO_SYMS_H
#define RG_TRACE_DEMO_SYMS_H

#ifdef __cplusplus
extern "C" {
#endif

/* PS2 addresses used by tests/trace/data/demo_regions.cfg */
#define RG_TRACE_DEMO_VBL       0x004810C4u /* rg_demo_result.fields_done (stands in for the game counter) */
#define RG_TRACE_DEMO_PAD_WORDS 0x00500000u /* pad_word[4096] (u16) */
#define RG_TRACE_DEMO_PAD_READS 0x00502000u
#define RG_TRACE_DEMO_GFX       0x00502004u
#define RG_TRACE_DEMO_STABLE    0x00502008u
#define RG_TRACE_DEMO_PTRS      0x00502100u /* void *[3]: &pad_reads, heap block, NULL */

/* Register the symbols, plus a service hook that allocates the heap block
 * (rg_crt0_sbrk: PS2 0x00528200, the first heap address) once the runtime is
 * up.  Call before rg_runtime_init (and before rg_trace_apply_env). */
void rg_trace_demo_register(void);

#ifdef __cplusplus
}
#endif
#endif
