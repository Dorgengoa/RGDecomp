/* rgp:protos */
#define RGP_SELF_MenuCursorBobToCell_2949f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_004823B8;

s32 MenuCursorBobToCell_2949f0(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 sp5C;
    s32 sp58;
    f32 temp_f2;

    PhaseAdvanceWrapPi_28b630(&D_004823B8, D_0047D3B8);
    temp_f2 = 6.0f * Sinf_128fd0(D_004823B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp5C, &sp58, (s32)((f32)arg2 + temp_f2),
                 (s32)((f32) * (s16 *)((u8 *)arg0 + 0x12) + ((f32)arg3 + temp_f2)));
    UiMoveWidgetUniform_290f50(arg1, 0x227, sp5C, sp58, 0.25f, 0);
    return 1;
}
