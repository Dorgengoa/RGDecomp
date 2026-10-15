#include "types.h"

typedef struct {
    u8 pad0[8];
    s32 m8;
} Obj171a10;

typedef struct {
    Obj171a10 *o;
    f32 a;
    f32 b;
} Elem171a10;

typedef struct {
    s32 m0;
    Elem171a10 *begin;
    s32 count;
    Elem171a10 *data;
} Vec171a10;

typedef struct {
    s32 m0;
    s32 m4;
    s32 m8;
    s32 mC;
} Bld171a10;

extern s32 ConstructNewArray_100710(s32, s32, s32, s32, s32);
extern void OperatorDeleteArray_100820(s32);
extern s32 OperatorNewArray_100900(s32);
extern void ModelApplyMotionKeys_150650(u8 *, u8 *, f32);
extern s32 ArrayGetCountIndirect_1527c0(u8 *);
extern void AnimBlendBufInit_153370(Bld171a10 *, s32, s32, s32, s32);
extern void AnimBlendBufAccumulate_1533f0(Bld171a10 *, s32, f32, f32);
extern void AmixerSampleEventsMaybe_170590(u8 *, s32 *, f32);
extern void Vec3VectorReserve_171230(s32 *, s32);
extern void Vec3VectorDeletingDtor_1713b0(s32 *, s32);
extern void AnimBlendBufApplyToModel_171430(Bld171a10 *, u8 *);

s32 ModelApplyMotion_171a10(u8 *arg0, u8 *arg1, f32 f)
{
    Bld171a10 b;
    s32 v[3];
    Elem171a10 *volatile it;
    Elem171a10 *volatile end;
    s32 *p;
    s32 n;
    s32 m;
    s32 ok;
    s32 r;
    s32 a1;
    s32 cnt;

    if (arg0 == NULL || arg1 == NULL) {
        return 0;
    }
    p = *(s32 **)(arg0 + 0x104);
    if (p == NULL) {
        return 0;
    }
    n = *p;
    m = ArrayGetCountIndirect_1527c0(arg0 + 0x120);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    Vec3VectorReserve_171230(v, 0x20);
    ok = *(s32 *)(arg1 + 0x1C) != 0;
    if (ok) {
        ok = *(s32 *)(arg1 + 0xC) > 0;
    }
    if (!(ok & 0xFF)) {
        r = 0;
    } else {
        AmixerSampleEventsMaybe_170590(arg1 + 0xC, v, f);
        r = 1;
    }
    if (r == 0) {
        ModelApplyMotionKeys_150650(arg0, arg1, f);
        Vec3VectorDeletingDtor_1713b0(v, 0);
        return 1;
    }
    b.m8 = 0;
    b.m0 = 0;
    a1 = ConstructNewArray_100710(OperatorNewArray_100900(n * 0x60 + 0x10), 0, 0, 0x60, n);
    AnimBlendBufInit_153370(&b, a1, n, ConstructNewArray_100710(OperatorNewArray_100900(m * 0x30 + 0x10), 0, 0, 0x30, m), m);
    cnt = 0;
    it = (Elem171a10 *)v[2];
    end = (Elem171a10 *)v[2] + v[1];
    while ((it == end) ^ 1) {
        { Elem171a10 *e = it; AnimBlendBufAccumulate_1533f0(&b, e->o->m8, e->a, e->b); }
        cnt++;
        it = it + 1;
    }
    if (cnt > 0) {
        AnimBlendBufApplyToModel_171430(&b, arg0);
    }
    if (b.m4 != 0) {
        OperatorDeleteArray_100820(b.m4 - 0x10);
    }
    if (b.mC != 0) {
        OperatorDeleteArray_100820(b.mC - 0x10);
    }
    Vec3VectorDeletingDtor_1713b0(v, 0);
    return 1;
}
