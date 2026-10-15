#include "types.h"

/* MAIN TopMenuLayoutRows_296790 -- lays out eight rows of the D_004DB1B0 dialogue plus
   two fixed items.  `$17 = ((i*5)<<3) - i` is the *39 strength reduction of
   the row pitch and `$f20` is the row's y, live across both calls.

   THE WHOLE RESIDUE WAS ONE PRAGMA.  Without it mwcc contracts
   `D_0047D4CC + D_0047D580 * (f32)i` through the float ACC and emits
   `mtc1 $zero,$f0 / adda.s / madd.s` -- one word LONGER than retail's
   `mul.s` + `add.s` -- and no source spelling reaches it: naming the product
   in a local (the settled NORMAL lever), reassociating, `i <= 7` for `i < 8`,
   moving the float parameter to position one and hoisting the shared 1 all
   give the IDENTICAL object 8aa2d56d.  `usefloatacc off` closes it, and the
   named-product arm stays inert UNDER the pragma (same object 4ef6d640), so
   the pragma is the entire lever and the source axis measured nothing.

   The floats are .lit4 pool addresses resolved BY GP OFFSET:
   D_0047D4CC = gp-0x7CA4, D_0047D580 = gp-0x7BF0, D_0047D798 = gp-0x79D8.  */

#pragma usefloatacc off

extern void UiMoveWidgetUniform_290f50(void *, u16, s32, s32, s32, f32);
extern void UiSetWidgetsVisibleById_291110(void *, u16, s32, s32);

extern u8 D_004DB1B0[];
extern f32 D_0047D4CC;
extern f32 D_0047D580;
extern f32 D_0047D798;

s32 TopMenuLayoutRows_296790(void)
{
    s32 i;
    s32 t;
    f32 f;

    for (i = 0; i < 8; i++) {
        f = D_0047D4CC + D_0047D580 * (f32)i;
        t = i * 39;
        UiMoveWidgetUniform_290f50(D_004DB1B0, (u16)(i + 0x16), -0x4A, t + 0x50, 0, f);
        UiMoveWidgetUniform_290f50(D_004DB1B0, (u16)(i + 0xD), -0x47, t + 0x53, 0, f);
        UiSetWidgetsVisibleById_291110(D_004DB1B0, (u16)(i + 0x1E), 1, 1);
    }
    UiMoveWidgetUniform_290f50(D_004DB1B0, 0x33, 0x9A, -0x3C, 0, D_0047D798);
    UiMoveWidgetUniform_290f50(D_004DB1B0, 0x32, 0x9D, -0x39, 0, D_0047D798);
    return 0;
}
