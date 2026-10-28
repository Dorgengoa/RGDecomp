/* rgp:protos */
#define RGP_SELF_MenuItemUseTargetReserveFaceSprites_2a2230 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_loop_invariants off
#pragma opt_loop_invariants on

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00450D30[0x400];
extern u8 D_00450E30[0x400];

s32 MenuItemUseTargetReserveFaceSprites_2a2230(s32 *arg0, s32 arg1)
{
    u8 *var_5;
    u8 *var_4;
    u8 sp90[0x30] __attribute__((aligned(16)));
    s32 temp_17;
    s32 var_20;
    s32 var_3;
    s32 var_16;
    s32 temp_4;
    s32 var_5_2;
    s32 temp_2_3;
    s32 temp_18;
    s32 var_19;
    u8 *temp_11;
    u8 *temp_2;
    u8 *temp_2_2;

    temp_2 = (u8 *)GetGameData_1fede0();
    temp_18 = PartyCountReserve_3c1c20(*(s32 *)(temp_2 + 0x18), 1, 1);
    var_5 = (u8 *)&(*(s16 *)D_00450E30);
    var_4 = sp90;
    var_3 = 0x15;
    do {
        var_3 -= 1;
        *(s16 *)var_4 = *(s16 *)var_5;
        var_5 += 0x2;
        var_4 += 0x2;
    } while (var_3 > 0);
    temp_17 = arg1 & 0xFFFF;
    var_16 = 0;
    do {
        UiSetSpriteSizeUvSize_28f670(*arg0, (s16)(temp_17 + var_16), 0, 0, 0, 0, 0);
        var_16 += 1;
    } while (var_16 < 7);
    var_20 = temp_18 - 5;
    if (var_20 <= 0) {
        var_20 = 0;
    }
    var_19 = 0;
    while (var_19 < temp_18) {
        temp_2_2 = (u8 *) UiGetWidgetSprite_28fe10(*arg0, (s16)(temp_17 + var_19), 0);
        if (temp_2_2 == NULL) {
            return 0;
        } else {
            temp_2_3 = PartyGetReserveChara_3c1d20(*(s32 *)(temp_2 + 0x18), var_19);
            if (temp_2_3 == 0) {
                return 0;
            } else {
                temp_4 = *(s16 *)((u8 *)CharaGetIconRecMaybe_3ae3e0(temp_2_3) + 0x2C);
                var_5_2 = 0;
                *(s16 *)(temp_2_2 + 0xA) = 0;
                *(s16 *)(temp_2_2 + 0x8) = 0;
                do {
                    temp_11 = (u8 *)&(*(u8 *)D_00450D30) + (var_5_2 * 6);
                    if (temp_4 == *(s16 *)(temp_11 + 0)) {
                        *(s16 *)(temp_2_2 + 0x0) = *(s16 *)(sp90 + (var_20 * 0xE) + (var_19 * 2));
                        *(s16 *)(temp_2_2 + 0xA) = *(s16 *)(temp_11 + 4);
                        *(s16 *)(temp_2_2 + 0xE) = 0x42;
                        *(s16 *)(temp_2_2 + 0x6) = 0x42;
                        if (var_20 == 2) {
                            *(s16 *)(temp_2_2 + 0x8) = *(s16 *)(temp_11 + 2) + 4;
                            *(s16 *)(temp_2_2 + 0xC) = 0x2E;
                            *(s16 *)(temp_2_2 + 0x4) = 0x2E;
                        } else {
                            *(s16 *)(temp_2_2 + 0x8) = *(s16 *)(temp_11 + 2);
                            *(s16 *)(temp_2_2 + 0xC) = 0x36;
                            *(s16 *)(temp_2_2 + 0x4) = 0x36;
                        }
                    }
                    var_5_2 += 1;
                } while (var_5_2 < 0xA);
            }
        }
        var_19 += 1;
    }
    return 1;
}
