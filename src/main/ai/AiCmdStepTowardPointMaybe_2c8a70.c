#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

extern f32 Acosf_129178(f32);
extern f32 Vu0InnerProduct_13bd60(V4 *, V4 *);
extern void VecNormalize_13bd90(V4 *, V4 *);
extern void VecScale_13be00(V4 *, V4 *, f32);
extern void VecAdd_13be20(V4 *, V4 *, V4 *);
extern void VecSub_13be40(V4 *, V4 *, V4 *);
extern u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void CharaSetPosVec_2387a0(s32, V4 *);
extern void CharaGetPos_2388a0(s32, V4 *);
extern void ScriptSlotStoreIntRef_2cc900(u8 *, s32);
extern f32 ScriptSlotGetFloat_2cc9a0(u8 *);
extern s32 ScriptSlotGetInt_2cc9c0(u8 *);
extern f32 D_0047D1FC;
extern s32 D_004DB920[];
extern s32 D_004DB92C[];

s32 AiCmdStepTowardPointMaybe_2c8a70(u8 *arg0)
{
    V4 vb;
    V4 va;
    V4 c;
    V4 e;
    V4 d;
    s64 *p;
    u8 *self;
    u8 *obj;
    f32 f;
    f32 g;

    p = (s64 *)arg0;
    if (D_004DB92C[0] == 0) {
        return 0;
    }
    CharaGetPos_2388a0(D_004DB92C[0], &va);
    self = (u8 *)p;
    ScriptSlotGetInt_2cc9c0((u8 *)p++);
    if (*(s32 *)p == 1) {
        vb.x = ScriptSlotGetFloat_2cc9a0((u8 *)p++);
        vb.y = ScriptSlotGetFloat_2cc9a0((u8 *)p++);
        vb.z = ScriptSlotGetFloat_2cc9a0((u8 *)p++);
        vb.w = 0.0f;
    } else if (*(s32 *)p == 0) {
        obj = ObjRecGetLiveObject_1c4a90(D_004DB920[0], ScriptSlotGetInt_2cc9c0((u8 *)p++));
        if (obj == 0) {
            return 0;
        }
        *(u128 *)&vb = *(u128 *)(obj + 0x180);
        vb.w = 0.0f;
    }
    f = ScriptSlotGetFloat_2cc9a0((u8 *)p);
    if (va.x == vb.x && va.z == vb.z) {
        ScriptSlotStoreIntRef_2cc900(self, 1);
        return 1;
    }
    VecSub_13be40(&c, &va, &vb);
    c.y = 0.0f;
    VecNormalize_13bd90(&c, &c);
    VecSub_13be40(&d, &vb, &va);
    d.y = 0.0f;
    VecNormalize_13bd90(&d, &d);
    VecScale_13be00(&d, &d, f);
    VecAdd_13be20(&va, &va, &d);
    CharaSetPosVec_2387a0(D_004DB92C[0], &va);
    VecSub_13be40(&e, &va, &vb);
    e.y = 0.0f;
    VecNormalize_13bd90(&e, &e);
    g = Acosf_129178(Vu0InnerProduct_13bd60(&e, &c));
    g = (g < 0.0f) ? -g : g;
    if (g < D_0047D1FC) {
        ScriptSlotStoreIntRef_2cc900(self, 0);
    } else {
        ScriptSlotStoreIntRef_2cc900(self, 1);
    }
    return 1;
}
