/* rgp:protos */
#define RGP_SELF_JudgeObjectOnMapHit_3141f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct S0026 {
    u8 pad0[0x20];
} S0026;

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

void JudgeObjectOnMapHit_3141f0(void *arg0, s32 arg1, s32 arg2)
{
        void * arg_h0;

    s32 temp_18;
    s16 temp_3;
    s32 temp_17;
    u8 sp50[0x20] __attribute__((aligned(16)));
    u8 *temp_16;
    u8 *temp_2;
    u8 *base;

    base = (u8 *) arg0;
    *(s32 *) (base + 0x80) = arg2;
    if (arg2 & 1) {
        arg_h0 = base + 0x150;
        VecCopy_1cbe30(arg_h0, arg1 + 0x30);
        VecCopy_1cbe30(base + 0x160, arg1 + 0x40);
        if (*(u16 *) (base + 0xBE) & 4) {
            GuardEffectSpawn_2d8fb0(base + 0x150, base + 0x160);
            *(u16 *) (base + 0xBE) = (u16) (*(u16 *) (base + 0xBE) & 0xFFFB);
        }
        if (*(s16 *) (base + 0xBA) == 0) {
            temp_18 = ((s32)GetEffectMgr_2d9040());
            temp_2 = (u8 *) ExecInfoGetEffObjMaybe_3a70b0(base + 0x10, 0);
            temp_17 = *(s16 *) (base + 0x86) + 0xE0;
            if (temp_2 != NULL) {
                temp_16 = *(u8 **) (temp_2 + 0x20);
                if (temp_16 != NULL) {
                    temp_3 = *(s16 *) temp_16;
                    switch (temp_3) {
                    case 0x641:
                        LightningRequestOnObj_2d7de0(temp_17, 0x1E);
                        break;
                    case 0x645:
                        EffectSpawnHitBullet_2d7eb0(temp_17, base + 0x150);
                        break;
                    case 0x64B:
                        EffectSpawnHitBulletAlt_2d7e00(temp_17, base + 0x150);
                        break;
                    default:
                        EffectReleaseByNameKey_2e0e50(temp_18, *(s32 *) (temp_16 + 8), temp_17);
                        EffectCreateByName_2e1020(sp50, temp_18, *(s32 *) (temp_16 + 8), 0xFA0);
                        EffectSetId_2e0100(temp_18, sp50, temp_17);
                        EffectSetPos_2e0bb0(temp_18, sp50, base + 0x150);
                        break;
                    }
                }
            }
        }
        *(s16 *) (base + 0xBA) = (s16) (*(s16 *) (base + 0xBA) + 1);
    }
}
