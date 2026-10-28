/* rgp:protos */
#define RGP_SELF_MenuPartyCursorAnimCbMaybe_341dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1FC;
extern f32 D_0047D2CC;
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0047D450;
extern s32 D_00482360;
extern void * D_00482378;
extern f32 D_00482D00;
extern f32 D_00482D08;
extern s16 D_00482D0C;
extern f32 D_00482D28;

s32 MenuPartyCursorAnimCbMaybe_341dd0(s16 *arg0, s32 arg1)
{
    f32 temp_f12;
    f32 temp_f1;
    s8 temp_17;
    void *p;

    PhaseAdvanceWrapPi_28b630(&D_00482D00, D_0047D3B8);
    { f32 t = 8.0f * Sinf_128fd0(D_00482D00); UiMoveWidgetUniform_290f50(arg1, 0x19E, (s32)(arg0[0] + t), arg0[1], 0.25f, 0); }
    temp_17 = *(volatile s8 *)((u8 *)D_00482378 + 0x6C);
    p = GetGameData_1fede0();
    if (PartyGetSlotId_3c3120(*(s32 *)((u8 *)p + 0x18), temp_17) != 8) {
        temp_f1 = D_00482D28 + D_0047D450;
        D_00482D28 = temp_f1;
        if (!(temp_f1 <= 0.0f)) {
            D_00482D28 = temp_f1 - D_0047D1FC;
        }
        UiMoveWidgetUniform_290f50(arg1, 0x18E, (s32)(320.0f + 4.0f * Sinf_128fd0(D_00482D28)), 0x12, 0.25f, 0);
    }
    if (!(D_00482D08 <= 1.0f) || (D_00482D08 < 0.5f)) {
        D_00482D0C = -D_00482D0C;
    }
    D_00482D08 += D_0047D2CC * (f32)D_00482D0C;
    UiSetWidgetAlpha_2907a0(D_00482360, 0x198, D_00482D08);
    return 1;
}
