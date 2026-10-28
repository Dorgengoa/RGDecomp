/* rgp:protos */
#define RGP_SELF_DeathEffectSpawn_2d8270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004616E0[];
extern f32 D_0047DB00;
extern const struct { f32 v; f32 pad[3]; } D_0045B080;

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
/*rgp*/

void DeathEffectSpawn_2d8270(s32 k)
{
    f32 a[4] __attribute__((aligned(16)));
    f32 b[4] __attribute__((aligned(16)));
    u8 m[0x20] __attribute__((aligned(16)));
    void *s;
    u8 *r;
    void *o;
    f32 w;
    void *p;

    s = GetCurrentScene_1f5be0();
    r = ((u8 *)ObjRecGetLiveObject_1c4a90(s, k));
    if (r == 0) {
        return;
    }
    if (ObjGetNthAttachPointPosSafe_23b0c0(r, 0, 0, b) == 0) {
        return;
    }
    if (ObjGetNthAttachPointPosSafe_23b0c0(r, 1, 0, a) == 0) {
        return;
    }
    b[1] = 4.0f + a[1];
    o = GetEffectMgr_2d9040();
    EffectCreateByName_2e1020(m, o, D_004616E0, -1);
    EffectSetId_2e0100(o, m, k);
    EffectSetPos_2e0bb0(o, m, b);
    EffectSetRotXyz_2e0910(o, m, 0.0f, D_0047DB00 * (RandFloat_13c010() - 0.5f), 0.0f);
    w = ModelObjGetScaledRadius_23b140(r) / D_0045B080.v;
    if (w < 0.25f) {
        w = 0.25f;
    }
    EffectSetScaleXyz_2e0c90(o, m, w, w, w);
    p = GameSceneSoundSlot5GetHandle_1d0790(s);
    SoundPlayScaledVolume_1b9520(p, 0x48, SoundNextPlayHandle_1b81c0(), 1.0f);
}
