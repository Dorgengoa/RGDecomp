/* rgp:protos */
#define RGP_SELF_MenuLeaderChangeCheckState_2b4f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x24C];
    u8 unk24C;
} Sub20;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    u8 pad1C[0x20 - 0x1C];
    Sub20 *unk20;
} Obj001fede0;

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
extern f32 D_0047D35C;
extern f32 D_0047D5B8;
extern f32 D_0047D684;
extern s32 D_00481BBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482370;
extern s16 D_00482554;
extern s16 D_0048255C;

s32 MenuLeaderChangeCheckState_2b4f30(s32 pad0, s32 arg1)
{
        s32 arg_h0;

    f32 temp_f0;
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_2_2;
    u16 var_17;
    Obj001fede0 *temp_2;

    if (arg1 != 0) {
        arg_h0 = D_00482360;
        UiFadeWidgetColor_2904e0(arg_h0, 0x11D, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D5B8);
    } else {
        temp_f0 = UiGetWidgetAlpha_290770(D_00482360, 0x11D);
        if (temp_f0 >= D_0047D35C) {
            UiFadeWidgetColor_2904e0(D_00482360, 0x11D, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D684);
        } else {
            if (temp_f0 <= 1.0f) {
                MenuWidgetFadeInOut_29fb00(D_00482370, 0x11A, 0, 0);
                temp_16 = MenuGetCursorIndex_29fa80(D_00482370);
                temp_2 = ((Obj001fede0 *)GetGameData_1fede0());
                temp_16_2 = *(s32 *)((u8 *) PartyGetSlotChara_3c2fb0(temp_2->unk18, temp_16) + 0xC);
                temp_2_2 = ((short)MenuGetOpenLeaderId_29acd0());
                var_17 = 1;
                if (!(temp_2->unk20->unk24C & 1) && (CharaIsNearLeaderMaybe_1fb230(temp_16_2, temp_2_2) == 0)) {
                    var_17 = 0;
                }
                if (!var_17) {
                    UiSetTextString_28f510(D_00482360, 0x21E, MsgTableLookup_28aa30(D_00481BBC, 0x47), 0);
                    D_00482554 = 0x4B;
                    D_0048255C = 2;
                    StateMachineSetState_28ede0(D_0048235C, 0x4D, 0);
                } else {
                    StateMachineSetState_28ede0(D_0048235C, 0x67, 0);
                }
            }
        }
    }
    return 0;
}
