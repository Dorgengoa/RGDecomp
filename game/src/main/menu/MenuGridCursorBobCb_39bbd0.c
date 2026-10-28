/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_39bbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0048362C;
extern u8 D_004E9660[0x100];

s32 MenuGridCursorBobCb_39bbd0(s32 arg0)
{
    s32 sp2C;
    s32 sp28;

    PhaseAdvanceWrapPi_28b630(&D_0048362C, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp2C, &sp28, (s32)(8.0f * Sinf_128fd0(D_0048362C)), 0);
    UiMoveWidgetUniform_290f50(D_004E9660, 0xD, sp2C, sp28, 0.25f, 0);
    return 1;
}
