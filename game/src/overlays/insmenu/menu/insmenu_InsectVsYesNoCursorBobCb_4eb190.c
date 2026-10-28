/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsYesNoCursorBobCb_4eb190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EB190 -- BYTE-IDENTICAL (lane L2, 2026-08-26), 35 words,
 * scored by build/dv_oslit_im02.py against retail/BIN/INSMENU.BIN.
 * The sibling of insmenu_InsectVsSourceChoiceBobCb_4f8560 with the target widget as a parameter.
 *
 * !! DO NOT ADD TO config/ocunits/insmenu.txt UNTIL scripts/i_olink.py RUNS A
 * `.lit4` RETARGET (build/lit4_im02.py; patch site text+0x0008,
 * C78C0000 -> C78C8260, pool address 0x0047D3D0).  Unpatched the gp immediate
 * links as 0 -- a WRONG image of the RIGHT LENGTH.
 *
 * * OVERTURNS this file's old "gp-float prologue rotation is a BOUNDED
 * NEGATIVE" header.  0x0047D1D0-0x0047D7FF is mwcc's `.lit4` FLOAT LITERAL
 * POOL, not globals -- 0x0047D3D0 is 0.1570796371 (pi/20).  Writing the
 * literal instead of `extern f32 D_0047D3D0` lets the load hoist past the
 * callee-saved stores, which is retail's schedule.  4 -> 0 on one token.
 * See memory levers.d/mwcc-float-literal-pool.md.
 */

extern f32 D_00484308;      /* gp - 0xE68  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsYesNoCursorBobCb_4eb190(void *o, const void *w)
{
    s32 sp3C;
    s32 sp38;

    PhaseAdvanceWrapPi_28b630(&D_00484308, 0.1570796371f);
    GetGridCellPosOffset_28ecd0(o, &sp3C, &sp38, (s32)(8.0f * Sinf_128fd0(D_00484308)), 0);
    UiMoveWidgetUniform_290f50(w, 9, sp3C, sp38, 0.5f, 0);
    return 1;
}
