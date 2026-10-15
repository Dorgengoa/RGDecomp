#include "types.h"

/* insmenu 0x004F8560 -- BYTE-IDENTICAL (lane L2, 2026-08-26), 33 words,
 * scored by build/dv_oslit_im02.py against retail/BIN/INSMENU.BIN.
 * Lay out one scrolling caption: seed the phase, measure the string, publish
 * the extent.
 *
 * !! DO NOT ADD TO config/ocunits/insmenu.txt UNTIL scripts/i_olink.py RUNS A
 * `.lit4` RETARGET.  This source writes the FLOAT LITERAL, so mwcc emits a
 * `.lit4` section with an `@N` symbol and an R_MIPS_LITERAL relocation.  The
 * constant already exists in MAIN at 0x0047D3B8 and the overlay cannot reach
 * its own data through main's $gp, so the object must be patched the way
 * scripts/t_lit4.py patches title's -- build/lit4_im02.py is that tool with
 * the object dir swapped (patch site: text+0x0008, C78C0000 -> C78C8248).
 * Unpatched, the gp immediate links as 0, which is a WRONG image of the
 * RIGHT LENGTH.
 *
 * * OVERTURNS the header this file used to carry.  It called the residue the
 * "gp-float prologue rotation" and a BOUNDED NEGATIVE: retail issues
 * `lwc1 $f12, <gp>` before the callee-saved `sq`s and mwcc issues it after.
 * That was an EXTERN-SPELLING ARTEFACT.  0x0047D1D0-0x0047D7FF is mwcc's
 * `.lit4` FLOAT LITERAL POOL, not globals -- 0x0047D3B8 is 0.07853981853
 * (pi/40).  A pool entry has no alias hazard so it hoists past the prologue
 * stores; an `extern f32` load is pinned at its use.  One token, 2 -> 0.
 * See memory levers.d/mwcc-float-literal-pool.md.
 */

extern f32 D_00484378;      /* gp - 0xDF8  */
extern const u8 D_004FA180[];

extern void func_28B630(f32 *a, f32 v);
extern f32 func_128FD0(f32 t);
extern void func_28ECD0(void *a, s32 *x, s32 *y, s32 n, s32 e);
extern void func_290F50(const void *a, s32 b, s32 x, s32 y, s32 e, f32 t);

s32 insmenu_InsectVsSourceChoiceBobCb_4f8560(void *o)
{
    s32 sp2C;
    s32 sp28;

    func_28B630(&D_00484378, 0.078539819f);
    func_28ECD0(o, &sp2C, &sp28, (s32)(8.0f * func_128FD0(D_00484378)), 0);
    func_290F50(D_004FA180, 0x5E, sp2C, sp28, 0, 1.0f);
    return 1;
}
