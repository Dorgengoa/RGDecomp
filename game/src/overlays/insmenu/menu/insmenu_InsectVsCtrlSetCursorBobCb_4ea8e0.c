/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsCtrlSetCursorBobCb_4ea8e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EA8E0 (412 bytes, 103 instructions) -- the two-stage variant of
 * insmenu_InsectVsYesNoCursorBobCb_4eb190 / insmenu_InsectVsMenuCursorBob_4ee610: the same
 * func_28B630 / func_128FD0 / func_28ECD0 / func_290F50 caption sweep run for
 * field 0xF, then either a second sweep at half the phase for field 0xE, or the
 * two-row rebuild loop that insmenu_InsectVsMenuStateCtrlSetOpen_4eadb0's else-arm also writes.
 *
 * 0x0047D3D0 (gp - 0x7DA0) is a `.lit4` POOL entry (0.1570796371, pi/20), not a
 * global -- the literal spelling is what lets the lwc1 hoist above the
 * callee-saved sq's.  See levers.d/mwcc-float-literal-pool.md.
 *
 * `w` and the loop counter share $16: their live ranges are disjoint (w is dead
 * in the else-arm), so mwcc coalesces them.  They are two variables.
 *
 * !! DO NOT ADD TO config/ocunits/insmenu.txt UNTIL scripts/i_olink.py RUNS A
 * `.lit4` RETARGET (build/lit4_im07.py; patch site text+0x0008,
 * C78C0000 -> C78C8260, pool address 0x0047D3D0).  Unpatched the gp immediate
 * links as 0 -- a WRONG image of the RIGHT LENGTH.  Same blocker as lanes
 * L1/L2's ten units.
 *
 * BYTE-IDENTICAL at 103 words (declared 0x19C / 4 = 103), scored by
 * build/os_im07.py on 2026-08-26.  Plain dv_osbuild with no retarget reports
 * exactly one bad word at 0x004EA8E8, which is that same gp immediate.
 */

extern u8 insmenu_D_004FA180[];
extern u8 D_004B27E0[];

extern f32 D_00484308;      /* gp - 0xE68 */
extern s32 D_004842FC;      /* gp - 0xE74 */
extern u8 D_00484314[2];    /* gp - 0xE5C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsCtrlSetCursorBobCb_4ea8e0(void *o, const void *w)
{
    s32 sp3C;
    s32 sp38;
    s32 i;

    PhaseAdvanceWrapPi_28b630(&D_00484308, 0.1570796371f);
    GetGridCellPosOffset_28ecd0(o, &sp3C, &sp38, (s32)(8.0f * Sinf_128fd0(D_00484308)), 0);
    UiMoveWidgetUniform_290f50(w, 0xF, sp3C, sp38, 0.5f, 0);
    if (((unsigned char)PadIsAnalogMode_184960(D_004B27E0)) != 0) {
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0xE, 1, 1);
        GetGridCellPosOffset_28ecd0(o, &sp3C, &sp38, (s32)(4.0f * Sinf_128fd0(D_00484308 / 2.0f)), 0);
        UiMoveWidgetUniform_290f50(w, 0xE, sp3C, sp38, 0.5f, 0);
    } else {
        for (i = 0; i < 2; i++) {
            D_00484314[i] = 0;
            UiSetTextString_28f510(insmenu_D_004FA180, 0xC, MsgTableLookup_28aa30(D_004842FC, 8), i + 2);
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x44, 0xE8, i + 1);
        }
        UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0xE, 0, 1);
    }
    return 1;
}
