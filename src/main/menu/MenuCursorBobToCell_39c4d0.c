/* PARK 2 bad (was 9, then 4): two real fixes banked -- (1) the gp lwc1 of
   D_0047D3D0 needed [[mwcc-const-sdata-load-hoist]] const+.sdata, (2) the
   function has FOUR parameters, not three: retail keeps $4/$6/$7, so there
   is an UNUSED second parameter.  Remaining 2 words are the creation order
   of two independent constants at 0x39C53C (retail materialises the 0.5f
   `lui 0x3F00` BEFORE the D_004E9610 `lui 0x4F`); naming either the float
   or the address as its own local, in either position, is INERT. */
#include "types.h"

extern f32 Sinf_128fd0(f32);
extern void PhaseAdvanceWrapPi_28b630(f32 *, f32);
extern void GetGridCellPosOffset_28ecd0(s32, s32 *, s32 *, s32, s32);
extern void UiMoveWidgetUniform_290f50(f32, s32, s32, s32, s32, s32);
extern const f32 D_0047D3D0 __attribute__((section(".sdata")));
extern f32 D_0048362C;
extern u8 D_004E9610[];

s32 MenuCursorBobToCell_39c4d0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp4C;
    s32 sp48;
    f32 term;
    f32 base;

    PhaseAdvanceWrapPi_28b630(&D_0048362C, D_0047D3D0);
    term = 8.0f * Sinf_128fd0(D_0048362C);
    base = (f32)arg2;
    GetGridCellPosOffset_28ecd0(arg0, &sp4C, &sp48, (s32)(base + term), arg3);
    UiMoveWidgetUniform_290f50(0.5f, (s32)D_004E9610, 4, sp4C, sp48, 0);
    return 1;
}
