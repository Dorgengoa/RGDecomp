/* SPDX-License-Identifier: CC0-1.0 */
/* `vcallms imm` for the port: run a VU0 microprogram on the src/ps2/vu
 * interpreter with the SAME register file the macro-mode model uses
 * (include/port/vu0.h, docs/PORT-HEADERS.md "VU0 micro mode").
 *
 * On the PS2 macro mode (COP2 instructions from the EE) and micro mode (a
 * program in VU0 micro memory) are one VU0: vf00-vf31, ACC, vi00-vi15, Q, P,
 * I, R and the clip flag are the same registers.  The port keeps two
 * representations (rg_vu0 for the inline macro ops, a vu_state for the
 * interpreter), so they are made the same state at the only points where
 * the other side can look: rg_vu0 -> vu_state when vcallms starts, and
 * vu_state -> rg_vu0 when the program has ended.  That is exact because the
 * model is synchronous: nothing in macro mode runs while the program runs.
 * (Hardware: a COP2 macro instruction issued while VU0 is busy waits for the
 * program to end; the game always follows vcallms with vnop, so the EE code
 * never observes the program half-way.)
 *
 * Not shared: the MAC and status flags (the macro model does not keep them;
 * cfc2 of vi16/vi17 reads 0 there), which stay the interpreter's own across
 * calls, and the EE GPR temps (micro mode cannot see them).
 *
 * The VU0 whose micro memory holds the program is the runtime's (it is what
 * VIF0 MPG uploads fill: GfxSysInit sends the D_00445810 VIF0 chain);
 * src/runtime binds it with rg_vu0_micro_bind().  Tests bind their own. */
#include <stdio.h>
#include <string.h>

#include "port/vu0.h"
#if !RG_VU0_IS_LOCAL
#include "vu.h"
#endif

/* cycle budget of one vcallms; the retail program behind MatFromSRTVu0 /
 * MatRotateVu0 takes a few hundred */
#define RG_VCALLMS_BUDGET 1000000u

static struct vu_state *g_vu0;
static unsigned g_unbound_reports;

void rg_vu0_micro_bind(struct vu_state *vu)
{
    g_vu0 = vu;
}

struct vu_state *rg_vu0_micro_bound(void)
{
    return g_vu0;
}

#if RG_VU0_IS_LOCAL
/* RG_VU0_MODE local / native (docs/NATIVE-CPU.md): there is no shared VU0
 * register file and no interpreter on this path.  The game's one
 * microprogram is native C (rg_vu0_srt, src/sce/vu0/vu0_srt.c) and its two
 * callers call it directly; anything that still reaches vcallms is a bug. */
int rg_vu0_vcallms(unsigned imm)
{
    if (g_unbound_reports++ < 4)
        fprintf(stderr, "rg_vu0_vcallms(0x%x): no VU0 interpreter on the native VU0 path "
                        "(RG_VU0_MODE local/native); nothing run\n", imm);
    return -1;
}
#else
/* macro model -> interpreter */
static void sync_in(vu_state *vu)
{
    int r;
    vu_drain(vu); /* no flag/Q/P write from a previous program may land late */
    for (r = 1; r < 32; r++)
        memcpy(vu->vf[r].u, rg_vu0.vf[r].u, 16);
    memcpy(vu->acc.u, rg_vu0.acc.u, 16);
    for (r = 1; r < 16; r++)
        vu->vi[r] = (uint16_t)(rg_vu0.vi[r] & 0xFFFFu);
    vu->vi[0] = 0;
    vu->q = rg_vu0.q;
    vu->p = rg_vu0.p;
    vu->i = rg_vu0.i;
    vu->r = rg_vu0.r;
    vu->clip = rg_vu0.clip & 0xFFFFFFu;
    /* the macro writes have all landed */
    memset(vu->vf_ready, 0, sizeof vu->vf_ready);
}

/* interpreter -> macro model */
static void sync_out(const vu_state *vu)
{
    int r;
    for (r = 1; r < 32; r++)
        memcpy(rg_vu0.vf[r].u, vu->vf[r].u, 16);
    memcpy(rg_vu0.acc.u, vu->acc.u, 16);
    for (r = 1; r < 16; r++)
        rg_vu0.vi[r] = vu->vi[r];
    rg_vu0.vi[0] = 0;
    rg_vu0.q = vu->q;
    rg_vu0.p = vu->p;
    rg_vu0.i = vu->i;
    rg_vu0.r = vu->r;
    rg_vu0.clip = vu->clip & 0xFFFFFFu;
}

int rg_vu0_vcallms(unsigned imm)
{
    vu_state *vu = g_vu0;
    vu_stop st;
    if (!vu) {
        if (g_unbound_reports++ < 4)
            fprintf(stderr, "rg_vu0_vcallms(0x%x): no VU0 bound (rg_vu0_micro_bind); "
                            "registers left unchanged\n", imm);
        return -1;
    }
    sync_in(vu);
    vu_start(vu, (imm & 0xFFFFu) * 8u);
    st = vu_run(vu, RG_VCALLMS_BUDGET);
    vu_drain(vu);
    sync_out(vu);
    if (st != VU_STOP_EBIT) {
        fprintf(stderr, "rg_vu0_vcallms(0x%x): program did not end (stop %d%s%s)\n", imm,
                (int)st, vu->error[0] ? ": " : "", vu->error);
        vu->running = 0;
        return -1;
    }
    return 0;
}
#endif
