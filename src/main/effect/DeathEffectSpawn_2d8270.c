#include "types.h"

extern u8 D_004616E0[];
extern f32 D_0047DB00;
extern const struct { f32 v; f32 pad[3]; } D_0045B080;

extern void *GetCurrentScene_1f5be0(void);
extern u8 *ObjRecGetLiveObject_1c4a90(void *s, s32 k);
extern s32 ObjGetNthAttachPointPosSafe_23b0c0(void *r, s32 a, s32 b, f32 *o);
extern void *GetEffectMgr_2d9040(void);
extern void EffectCreateByName_2e1020(void *m, void *o, void *n, s32 a);
extern void EffectSetId_2e0100(void *o, void *m, s32 k);
extern void EffectSetPos_2e0bb0(void *o, void *m, f32 *v);
extern f32 RandFloat_13c010(void);
extern void EffectSetRotXyz_2e0910(void *o, void *m, f32 a, f32 b, f32 c);
extern f32 ModelObjGetScaledRadius_23b140(void *r);
extern void EffectSetScaleXyz_2e0c90(void *o, void *m, f32 a, f32 b, f32 c);
extern void *GameSceneSoundSlot5GetHandle_1d0790(void *s);
extern void *SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolume_1b9520(void *p, s32 a, void *q, f32 t);

void DeathEffectSpawn_2d8270(s32 k)
{
    f32 a[4];
    f32 b[4];
    u8 m[0x20];
    void *s;
    u8 *r;
    void *o;
    f32 w;
    void *p;

    s = GetCurrentScene_1f5be0();
    r = ObjRecGetLiveObject_1c4a90(s, k);
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
