#include "types.h"

extern void *ObjRecGetLiveObject_1c4a90(void *);
extern s32 CBlurTexFindTex_1791a0(void *);
extern void ModelObjSetCBlurTexMaybe_1ad5d0(void *, s32);
extern void ModelObjSetCBlurAlphaMaybe_1ad5c0(void *, f32);

void GameSceneObjSetCBlurMaybe_1cf900(void *p, s32 unused, f32 t, s32 flag)
{
    void *r;
    f32 v;
    s32 x;

    r = ObjRecGetLiveObject_1c4a90(p);
    if (r == 0) return;
    v = 1.0f;
    x = 0;
    if (flag != 0) {
        x = CBlurTexFindTex_1791a0((void *)((s32)p + 0x58C0));
        v = t;
    }
    ModelObjSetCBlurTexMaybe_1ad5d0(r, x);
    ModelObjSetCBlurAlphaMaybe_1ad5c0(r, v);
}
