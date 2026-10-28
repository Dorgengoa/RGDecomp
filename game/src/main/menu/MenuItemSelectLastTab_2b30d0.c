/* rgp:protos */
#define RGP_SELF_MenuItemSelectLastTab_2b30d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00482374 {
    u8 pad0[0x10];
    s8 unk10;
    s8 unk11;
} S00482374;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482360;
extern S00482374 *D_00482374;
extern s32 D_004823D8;

void MenuItemSelectLastTab_2b30d0(void)
{
    s32 var_16;
    s32 var_16_2;
    s32 var_16_3;
    s32 var_16_4;

    var_16 = 1;
    do {
        UiSetSpriteFlags_290bd0(D_00482360, 0x65, (long long)(8), 1, var_16, 0);
        var_16 += 1;
    } while (var_16 < 0xB);
    var_16_2 = 0;
    do {
        UiSetSpriteFlags_290bd0(D_00482360, 0x67, (long long)(8), 1, var_16_2, 0);
        var_16_2 += 1;
    } while (var_16_2 < 0x10);
    var_16_3 = 0;
    do {
        UiSetSubItemFlags_28ef30(D_00482360, 0x69, (long long)(0x80), 1, var_16_3);
        var_16_3 += 1;
    } while (var_16_3 < 8);
    var_16_4 = 0;
    do {
        UiSetSubItemFlags_28ef30(D_00482360, 0x77, (long long)(0x80), 1, var_16_4);
        var_16_4 += 1;
    } while (var_16_4 < 0x28);
    MenuItemSetOpenModeMaybe_2a4ed0(D_00482374, 2);
    D_00482374->unk11 = (s8) (D_00482374->unk10 - 1);
    MenuItemSelectTab_2b3550(D_00482374->unk11, 2, 0);
    UiSetTextString_28f510(D_00482360, 0x73, MsgTableLookup_28aa30(D_004823D8, 0x3EF), 0);
}
