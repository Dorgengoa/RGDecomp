#include "types.h"

/* insmenu 0x004EE610 -- BYTE-IDENTICAL (lane L2, 2026-08-26), 38 words,
 * scored by build/dv_oslit_im02.py against retail/BIN/INSMENU.BIN.
 * The same caption layout as insmenu_InsectVsYesNoCursorBobCb_4eb190 with the field id taken as
 * a parameter; the `andi $5, $16, 0xFFFF` is the u16 parameter promoting to
 * the callee's s32, not a mask to write.
 *
 * !! DO NOT ADD TO config/ocunits/insmenu.txt UNTIL scripts/i_olink.py RUNS A
 * `.lit4` RETARGET (build/lit4_im02.py; patch site text+0x0008,
 * C78C0000 -> C78C8260, pool address 0x0047D3D0).  Unpatched the gp immediate
 * links as 0 -- a WRONG image of the RIGHT LENGTH.
 *
 * * OVERTURNS this file's old "gp-float prologue rotation is a BOUNDED
 * NEGATIVE" header.  0x0047D3D0 is a `.lit4` pool entry (0.1570796371,
 * pi/20), not a global.  Writing the literal lets the load hoist past the
 * callee-saved stores.  6 -> 0 on one token.
 * See memory levers.d/mwcc-float-literal-pool.md.
 */

extern f32 D_00484308;      /* gp - 0xE68  */

extern void func_28B630(f32 *a, f32 v);
extern f32 func_128FD0(f32 t);
extern void func_28ECD0(void *a, s32 *x, s32 *y, s32 n, s32 e);
extern void func_290F50(const void *a, s32 b, s32 x, s32 y, s32 e, f32 t);

s32 insmenu_InsectVsMenuCursorBob_4ee610(void *o, const void *w, u16 id)
{
    s32 sp4C;
    s32 sp48;

    func_28B630(&D_00484308, 0.1570796371f);
    func_28ECD0(o, &sp4C, &sp48, (s32)(8.0f * func_128FD0(D_00484308)), 0);
    func_290F50(w, id, sp4C, sp48, 0, 0.5f);
    return 1;
}
