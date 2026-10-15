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

extern const u8 D_004FA180[];
extern const u8 D_004B27E0[];

extern f32 D_00484308;      /* gp - 0xE68 */
extern s32 D_004842FC;      /* gp - 0xE74 */
extern u8 D_00484314[2];    /* gp - 0xE5C */

extern void func_28B630(f32 *a, f32 v);
extern f32 func_128FD0(f32 t);
extern void func_28ECD0(void *a, s32 *x, s32 *y, s32 n, s32 e);
extern void func_290F50(const void *a, s32 b, s32 x, s32 y, s32 e, f32 t);
extern s32 func_184960(const void *a);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);
extern void func_28F930(const void *a, s32 b, s32 c, s32 d);

s32 insmenu_InsectVsCtrlSetCursorBobCb_4ea8e0(void *o, const void *w)
{
    s32 sp3C;
    s32 sp38;
    s32 i;

    func_28B630(&D_00484308, 0.1570796371f);
    func_28ECD0(o, &sp3C, &sp38, (s32)(8.0f * func_128FD0(D_00484308)), 0);
    func_290F50(w, 0xF, sp3C, sp38, 0, 0.5f);
    if (func_184960(D_004B27E0) != 0) {
        func_291110(D_004FA180, 0xE, 1, 1);
        func_28ECD0(o, &sp3C, &sp38, (s32)(4.0f * func_128FD0(D_00484308 / 2.0f)), 0);
        func_290F50(w, 0xE, sp3C, sp38, 0, 0.5f);
    } else {
        for (i = 0; i < 2; i++) {
            D_00484314[i] = 0;
            func_28F510(D_004FA180, 0xC, func_28AA30(D_004842FC, 8), i + 2);
            func_28F930(D_004FA180, 0x44, 0xE8, i + 1);
        }
        func_291110(D_004FA180, 0xE, 0, 1);
    }
    return 1;
}
