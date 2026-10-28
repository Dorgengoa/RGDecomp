/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialChoiceOpen_4edc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EDC10 -- the per-tick handler for panel id 0x899E
 * (dispatch table entry at main 0x00454F..).  400 bytes, 100 instructions,
 * 3 conditional branches.
 *
 * Sibling of the 004ED6D0 seed: identical opening (unused first parameter, the
 * flag in $5, the INVERTED `w == 0` early return), identical `jal + ori + sh`
 * id block, identical `>= 1.0f` float tail guard.
 *
 * Per-unit constants: widget id 0x6D (0x76 for the first fade), glyph id
 * 0x8926, sound id 0x899E, pool float `D_0047D510` (_gp - 0x7C60, also 0.4f
 * but a DIFFERENT .lit4 entry from the seed's D_0047D500).
 *
 * The middle of the body is the `factory_FactoryMaterialChoiceHighlightCb_4ed7e0` arrow-placement idiom:
 * `func_2910A0` fills two `s32` out-params -- declared `x` before `y` so `x`
 * lands at sp+0x2C -- and the +6 / +5 adjustments are written INLINE at the
 * `func_290F60` call (there is no store back to 0x2C/0x28).
 *
 * `func_2910A0`'s first argument is a FRESH read of `D_00484A58->f40`, not
 * `$16`: retail reloads `-0x718($28)` there, and mwcc does not CSE the global
 * across a call.
 */

typedef struct Glyph {
    u8  pad00[0x14];
    s16 f14;
    s16 f16;
} Glyph;

typedef struct View {
    u8    pad00[0x40];
    void *f40;
    void *f44;
    void *f48;
} View;

extern View *D_00484A58;                        /* _gp - 0x718  */
extern f32   D_0047D510;                        /* _gp - 0x7C60 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialChoiceOpen_4edc10(s32 unused, s32 start)
{
    s32    x;
    s32    y;
    Glyph *g;
    void  *w;

    w = D_00484A58->f40;
    if (w == 0) {
        return 0;
    }
    if (start != 0) {
        UiSetWidgetVisible_290010(w, 0x6D, 1, -1);
        UiSetWidgetAlpha_2907a0(w, 0x76, 0.0f);
        UiSetWidgetAlpha_2907a0(w, 0x6D, 0.0f);
        UiFadeWidgetAlpha_290690(w, 0x6D, 1.0f, D_0047D510, -1.0f);
        g = ((Glyph *)UiEntryListFindByTag_28ea40(D_00484A58->f44, 0x8926));
        g->f14 = 0;
        g->f16 = 0;
        UiGetWidgetPos_2910a0(D_00484A58->f40, 0x6D, &x, &y);
        UiSetWidgetsVisibleById_291110(w, 0x67, 1, 1);
        UiSetWidgetAlpha_2907a0(w, 0x67, 1.0f);
        UiSetWidgetPos_290f60(w, 0x67, x + 6, y + 5);
        UiSetSpriteW_28fbf0(w, 0x6D, 0, 0);
        UiSetSpriteUvW_28f850(w, 0x6D, 0, 0);
        UiSetSpriteW_28fbf0(w, 0x6D, 0x3C, 1);
        UiSetSpriteUvW_28f850(w, 0x6D, 4, 1);
    }
    if (UiGetWidgetAlpha_290770(w, 0x6D) >= 1.0f) {
        StateMachineSetState_28ede0(D_00484A58->f48, 0x899E, 0);
    }
    return 1;
}
