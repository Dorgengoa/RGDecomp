/* SPDX-License-Identifier: CC0-1.0
 * Synthetic trace symbols for rg-runtime-demo (trace_demo_syms.h). */
#include <string.h>

#include "demo_guest.h"
#include "rg_runtime.h"
#include "rg_trace.h"
#include "trace_demo_syms.h"

/* Host pointers in 32-bit slots, as game structs hold them on i686. */
static void *g_ptrs[3];

static void after_init(void *user)
{
    (void)user;
    uint8_t *heap = (uint8_t *)rg_crt0_sbrk(64);
    if (heap == (uint8_t *)-1)
        return;
    for (int i = 0; i < 64; i++)
        heap[i] = (uint8_t)(0xA5 ^ (i * 7));
    g_ptrs[1] = heap;
}

void rg_trace_demo_register(void)
{
    static int done;
    if (done)
        return;
    done = 1;
    rg_demo_result *r = (rg_demo_result *)rg_demo_get_result();
    rg_trace_add_symbol(RG_TRACE_DEMO_VBL, 4, &r->fields_done, "demo.fields_done");
    rg_trace_add_symbol(RG_TRACE_DEMO_PAD_WORDS, (uint32_t)sizeof r->pad_word, r->pad_word, "demo.pad_word");
    rg_trace_add_symbol(RG_TRACE_DEMO_PAD_READS, 4, &r->pad_reads, "demo.pad_reads");
    rg_trace_add_symbol(RG_TRACE_DEMO_GFX, 4, &r->gfx_frames, "demo.gfx_frames");
    rg_trace_add_symbol(RG_TRACE_DEMO_STABLE, 4, &r->pad_stable_field, "demo.pad_stable_field");
    g_ptrs[0] = &r->pad_reads;
    g_ptrs[1] = NULL;
    g_ptrs[2] = NULL;
    rg_trace_add_symbol(RG_TRACE_DEMO_PTRS, (uint32_t)sizeof g_ptrs, g_ptrs, "demo.ptrs");
    rg_runtime_set_service_hook(after_init, NULL);
}
