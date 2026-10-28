/* SPDX-License-Identifier: CC0-1.0 */
/* Reference half of rg-vu0native-tests: the retail VU0 microprogram (VIF0
 * chain D_00445810 from the retail ELF) on the src/ps2/vu interpreter.  Kept
 * in its own file: the interpreter headers and port/vu0.h are separate worlds
 * (the game-side header is freestanding).  Test-only: the game links none of
 * this (docs/NATIVE-CPU.md). */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "vif.h"
#include "vu.h"
#include "vu_retail.h"

static rg_elf g_elf;
static vu_state g_vu;
static vif_state g_vif;
static int g_ok = -1;

/* 0 = ready, 77 = no retail ELF, -1 = broken */
int vnr_setup(void)
{
    size_t n;
    const uint32_t *w;
    if (g_ok >= 0)
        return g_ok ? 0 : 77;
    if (rg_elf_load(&g_elf, rg_retail_elf_path())) {
        printf("SKIP: retail ELF not found at %s (set RG_ELF)\n", rg_retail_elf_path());
        g_ok = 0;
        return 77;
    }
    vu_init(&g_vu, 0);
    vif_init(&g_vif, 0, &g_vu);
    w = rg_vif_packet(&g_elf, 0x445810u, &n); /* GfxSysInit's VIF0 chain (MPG) */
    if (!w)
        return -1;
    vif_write(&g_vif, w, n);
    g_ok = 1;
    return 0;
}

/* vcallms 0 with vf1..3 = s, r, t (16 bytes each); out = vf4..vf7 */
int vnr_srt(const uint32_t s[4], const uint32_t r[4], const uint32_t t[4], uint32_t out[16])
{
    int i;
    memcpy(g_vu.vf[1].u, s, 16);
    memcpy(g_vu.vf[2].u, r, 16);
    memcpy(g_vu.vf[3].u, t, 16);
    vu_start(&g_vu, 0);
    if (vu_run(&g_vu, 100000) != VU_STOP_EBIT)
        return -1;
    vu_drain(&g_vu);
    for (i = 0; i < 4; i++)
        memcpy(out + 4 * i, g_vu.vf[4 + i].u, 16);
    return 0;
}
