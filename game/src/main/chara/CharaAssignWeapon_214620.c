/* rgp:protos */
#define RGP_SELF_CharaAssignWeapon_214620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern u8 D_0045CAB0[0x400];
extern u8 D_0045CAC0[0x400];
extern u8 D_0045CAD0[0x400];
extern u8 D_0045CAE0[0x400];

void CharaAssignWeapon_214620(void *arg0, s32 arg1) {
    s32 temp_4;
    s32 var_3;
    u8 *temp_17;
    s32 var_4;

    temp_17 = (u8 *)arg0;

    var_3 = (arg1 >= 0 && arg1 < 0xC) ? (arg1 * 4) + 0xC : -1;
    if (arg1 == var_3) {
        EffectReleaseNodesByKey_2e1250(((s32)GetEffectMgr_2d9040()), *(s16 *)(temp_17 + 0x424), -1);
        temp_4 = *(s32 *)(temp_17 + 0x428);
        if (temp_4 != 0) {
            ActCfgTableRunEvntByName_21f680(temp_4, *(s16 *)(temp_17 + 0x424), &(*(u8 *)D_0045CAB0));
        }
        var_4 = *(s32 *)(temp_17 + 0xA54);
        *(s32 *)(temp_17 + 0xA54) = var_4 | 0x80000000;
    }

    var_3 = (arg1 >= 0 && arg1 < 0xC) ? (arg1 * 4) + 0xD : -1;
    if (arg1 == var_3) {
        EffectReleaseNodesByKey_2e1250(((s32)GetEffectMgr_2d9040()), *(s16 *)(temp_17 + 0x424), -1);
        temp_4 = *(s32 *)(temp_17 + 0x428);
        if (temp_4 != 0) {
            ActCfgTableRunEvntByName_21f680(temp_4, *(s16 *)(temp_17 + 0x424), &(*(u8 *)D_0045CAC0));
        }
        var_4 = *(s32 *)(temp_17 + 0xA54);
        *(s32 *)(temp_17 + 0xA54) = var_4 | 0x40000000;
    }

    var_3 = (arg1 >= 0 && arg1 < 0xC) ? (arg1 * 4) + 0xE : -1;
    if (arg1 == var_3) {
        EffectReleaseNodesByKey_2e1250(((s32)GetEffectMgr_2d9040()), *(s16 *)(temp_17 + 0x424), -1);
        temp_4 = *(s32 *)(temp_17 + 0x428);
        if (temp_4 != 0) {
            ActCfgTableRunEvntByName_21f680(temp_4, *(s16 *)(temp_17 + 0x424), &(*(u8 *)D_0045CAD0));
        }
        var_4 = *(s32 *)(temp_17 + 0xA54);
        *(s32 *)(temp_17 + 0xA54) = var_4 | 0x20000000;
    }

    var_3 = (arg1 >= 0 && arg1 < 0xC) ? (arg1 * 4) + 0xF : -1;
    if (arg1 == var_3) {
        EffectReleaseNodesByKey_2e1250(((s32)GetEffectMgr_2d9040()), *(s16 *)(temp_17 + 0x424), -1);
        temp_4 = *(s32 *)(temp_17 + 0x428);
        if (temp_4 != 0) {
            ActCfgTableRunEvntByName_21f680(temp_4, *(s16 *)(temp_17 + 0x424), &(*(u8 *)D_0045CAE0));
        }
        *(s32 *)(temp_17 + 0xA54) = *(s32 *)(temp_17 + 0xA54) | 0x10000000;
    }
}
