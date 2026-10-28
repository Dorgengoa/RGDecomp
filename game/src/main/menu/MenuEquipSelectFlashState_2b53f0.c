/* rgp:protos */
#define RGP_SELF_MenuEquipSelectFlashState_2b53f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D35C __attribute__((section(".sdata")));
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0047D5D0 __attribute__((section(".sdata")));
extern f32 D_0047D688 __attribute__((section(".sdata")));
extern s32 D_0048235C __attribute__((section(".sdata")));
extern s32 D_00482360;
extern s32 D_00482364 __attribute__((section(".sdata")));
extern f32 D_00482544;
extern s32 D_00482558 __attribute__((section(".sdata")));
extern s16 D_00482580;

s32 MenuEquipSelectFlashState_2b53f0(s32 unused0, s32 arg1)
{
        s32 arg_h1;

    f32 temp_f0;
    f32 temp_f1;
    s16 temp_2;
    s32 temp_9;
    void *temp_16;

    if (arg1 != 0) {
        SoundPlayScaledVolume_1b9520(D_00482558, 9, 0, 1.0f);
        D_00482580 = 1;
        arg_h1 = 0x17F;
        UiFadeWidgetColor_2904e0(D_00482360, arg_h1, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D5D0);
    } else if (D_00482580 != 0) {
        temp_f0 = UiGetWidgetAlpha_290770(D_00482360, 0x17F);
        if (temp_f0 >= D_0047D35C) {
            UiFadeWidgetColor_2904e0(D_00482360, 0x17F, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D688);
        } else {
            if (temp_f0 <= 1.0f) {
                temp_2 = D_00482580 + 1;
                D_00482580 = temp_2;
                if (temp_2 > 6) {
                    StateMachineSetState_28ede0(D_0048235C, 0x65, 0);
                }
            }
        }
    }
    temp_16 = UiEntryListFindByTag_28ea40(D_00482364, 0x15);
    PhaseAdvanceWrapPi_28b630(&D_00482544, D_0047D3B8);
    temp_f1 = 6.0f * Sinf_128fd0(D_00482544);
    temp_9 = *(s16 *)((u8 *)temp_16 + 0x14) * *(s16 *)((u8 *)temp_16 + 0x8);
    UiMoveWidgetUniform_290f50(D_00482360, 0x186, (s32)(temp_f1 + (f32)(*(s16 *)((u8 *)temp_16 + 0x4) + 0x42 + temp_9)), (s32)(temp_f1 + (f32)(*(s16 *)((u8 *)temp_16 + 0x6) + 0x42 +
            (*(s16 *)((u8 *)temp_16 + 0x16) * *(s16 *)((u8 *)temp_16 + 0xA)))), 0.25f, 0


);
    return 1;
}
