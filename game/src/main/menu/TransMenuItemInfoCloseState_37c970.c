/* rgp:protos */
#define RGP_SELF_TransMenuItemInfoCloseState_37c970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00484710;
extern void *D_0048470C;
extern f32 D_0047D960;
extern f32 D_0047D964;
extern const struct { s32 v; s32 pad[3]; } D_004659F0;
extern const struct { s32 v; s32 pad[3]; } D_004659F8;
extern u8 D_004E9230[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TransMenuItemInfoCloseState_37c970(s32 unused, s32 en)
{
    s32 i;
    s32 n;

    if (en != 0) {
        UiFadeWidgetAlpha_290690(D_00484710, 0x7658, 0.0f, D_0047D960, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7622, 0.0f, D_0047D960, -1.0f);
        UiFadeWidgetColor_2904e0(D_00484710, 0x75F8, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D964);
        i = 0;
        n = D_004659F0.v * D_004659F8.v;
        while (i < n) {
            UiSetSpriteFlags_290bd0(D_00484710, 0x7602, (long long)(0x20), -1, i, 0);
            UiSetSpriteFlags_290bd0(D_00484710, 0x7600, (long long)(0x20), -1, i, 0);
            UiSetSpriteFlags_290bd0(D_00484710, 0x7602, (long long)(0x18), 1, i, 0);
            UiSetSpriteFlags_290bd0(D_00484710, 0x7600, (long long)(0x18), 1, i, 0);
            i++;
        }
    }
    StateMachineSetState_28ede0(D_0048470C, 0x23, 0);
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
