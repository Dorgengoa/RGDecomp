/* PARK s17d try1: length 0x1EC vs retail 0x204, 18 words short. */
#include "types.h"

extern void ActCfgTableRunEvntByName_21f680(s32, s16, void *);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectReleaseNodesByKey_2e1250(s32, s16, s32);
extern u8 D_0045CA70[];
extern u8 D_0045CA80[];
extern u8 D_0045CA90[];
extern u8 D_0045CAA0[];

void CharaRemoveWeapon_214410(void *arg0, s32 arg1)
{
    u8 *e;
    s32 var_3;
    s32 t;

    e = (u8 *)arg0;

    var_3 = (arg1 >= 0 && arg1 < 0xC) ? ((arg1 * 4) + 0xC) : -1;
    if (arg1 == var_3) {
        EffectReleaseNodesByKey_2e1250(GetEffectMgr_2d9040(), *(s16 *)(e + 0x424), 0x1388);
        t = *(s32 *)(e + 0x428);
        if (t != 0) {
            ActCfgTableRunEvntByName_21f680(t, *(s16 *)(e + 0x424), D_0045CA70);
        }
        *(s32 *)(e + 0xA54) = *(s32 *)(e + 0xA54) & 0x7FFFFFFF;
    }

    var_3 = (arg1 >= 0 && arg1 < 0xC) ? ((arg1 * 4) + 0xD) : -1;
    if (arg1 == var_3) {
        EffectReleaseNodesByKey_2e1250(GetEffectMgr_2d9040(), *(s16 *)(e + 0x424), 0x1389);
        t = *(s32 *)(e + 0x428);
        if (t != 0) {
            ActCfgTableRunEvntByName_21f680(t, *(s16 *)(e + 0x424), D_0045CA80);
        }
        *(s32 *)(e + 0xA54) = *(s32 *)(e + 0xA54) & 0xBFFFFFFF;
    }

    var_3 = (arg1 >= 0 && arg1 < 0xC) ? ((arg1 * 4) + 0xE) : -1;
    if (arg1 == var_3) {
        EffectReleaseNodesByKey_2e1250(GetEffectMgr_2d9040(), *(s16 *)(e + 0x424), 0x138A);
        t = *(s32 *)(e + 0x428);
        if (t != 0) {
            ActCfgTableRunEvntByName_21f680(t, *(s16 *)(e + 0x424), D_0045CA90);
        }
        *(s32 *)(e + 0xA54) = *(s32 *)(e + 0xA54) & 0xDFFFFFFF;
    }

    var_3 = (arg1 >= 0 && arg1 < 0xC) ? ((arg1 * 4) + 0xF) : -1;
    if (arg1 == var_3) {
        EffectReleaseNodesByKey_2e1250(GetEffectMgr_2d9040(), *(s16 *)(e + 0x424), 0x138B);
        t = *(s32 *)(e + 0x428);
        if (t != 0) {
            ActCfgTableRunEvntByName_21f680(t, *(s16 *)(e + 0x424), D_0045CAA0);
        }
        *(s32 *)(e + 0xA54) = *(s32 *)(e + 0xA54) & 0xEFFFFFFF;
    }
}
