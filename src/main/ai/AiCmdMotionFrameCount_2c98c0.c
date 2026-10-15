#include "types.h"

typedef struct {
    s32 a;
    s32 b;
} Cur;

typedef struct {
    u8 pad0[0x24];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
} Q;

typedef struct {
    u8 pad0[0x1F0];
    s32 unk1F0;
    s32 unk1F4;
    s32 unk1F8;
} P;

extern Q *MotionListFindByName_1721d0(s32 *, s32, void *, void *);
extern s32 ModelObjGetMotionName_1add90(P *);
extern P *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void ScriptSlotStoreIntRef_2cc900(Cur *, s32);
extern f32 ScriptSlotGetFloat_2cc9a0(Cur *);
extern s32 ScriptSlotGetInt_2cc9c0(void);
extern s32 D_004DB920[];

s32 AiCmdMotionFrameCount_2c98c0(Cur *arg0, s32 arg1)
{
    u8 sp6C[4];
    u8 sp68[4];
    s32 v[3];
    s32 key;
    P *p;
    Q *q;
    s32 r;
    s32 n;
    f32 f;
    f32 a;
    f32 b;
    f32 t;

    key = D_004DB920[0];
    arg0++;
    p = ObjRecGetLiveObject_1c4a90(key, ScriptSlotGetInt_2cc9c0());
    if (p == NULL) {
        return 0;
    }
    v[0] = p->unk1F0;
    v[1] = p->unk1F4;
    v[2] = p->unk1F8;
    r = ModelObjGetMotionName_1add90(p);
    if (r == 0) {
        return 1;
    }
    q = MotionListFindByName_1721d0(v, r, sp6C, sp68);
    if (q == NULL) {
        return 1;
    }
    f = q->unk2C;
    if (f == 0.0f) {
        return 1;
    }
    n = (q->unk28 - q->unk24) / f;
    if (arg1 == 4) {
        a = ScriptSlotGetFloat_2cc9a0(arg0++);
        b = ScriptSlotGetFloat_2cc9a0(arg0++);
        n = (f32)n * (b - a);
    }
    ScriptSlotStoreIntRef_2cc900(arg0, n);
    return 1;
}
