/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityListScrollCb_2b46b0 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D240;
extern f32 D_0047D34C;
extern s32 D_00482360;
extern s32 D_00482370;

s32 MenuCharaAbilityListScrollCb_2b46b0(u8 *arg0)
{
    s32 sp48[2];
    s32 sp30[6] __attribute__((aligned(16)));
    u8 *g;
    s32 v;
    s16 h;

    h = *(s16 *)(arg0 + 0x12);
    if (h == (((__typeof__((MenuGetScrollTop_29fa40(D_00482370)) + 0LL))(MenuGetScrollTop_29fa40(D_00482370)) << 0x30) >> 0x30)) {
        UiMoveWidgetUniform_290f50(D_00482360, 0x12E, 0x18A, (s32)((f32)*(s16 *)(arg0 + 0x16) * MenuGetScrollStep_29f9a0(D_00482370) + 36.0f), D_0047D34C, 0);
        MenuCharaAbilityListFill_29b180(D_00482370, MenuGetCursorIndex_29fa80(D_00482370), *(s16 *)(arg0 + 0x16));
    }
    g = ((u8 *)GetGameData_1fede0());
    v = PartyGetSlotChara_3c2fb0(*(s32 *)(g + 0x18), MenuGetCursorIndex_29fa80(D_00482370));
    if (v == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(sp30, v, -1, -1);
    IterInit_370170(sp48, sp30, 0, 0);
    MenuCharaAbilityInfoBoxSetup_29afe0(D_00482370, IterSeek_36fff0(sp48, *(s16 *)(arg0 + 0x12) + *(s16 *)(arg0 + 0x16), 0, 0), 0x1AA, 0x1A9, 0x5D, 0x146, D_0047D240);
    UiSetWidgetPos_290f60(D_00482360, 0x123, 0xA, *(s16 *)(arg0 + 0x12) * *(s16 *)(arg0 + 0x6) - 0xC);
    MenuSetScrollTop_29fa50(D_00482370, *(s16 *)(arg0 + 0x12));
    return 1;
}
