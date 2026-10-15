#include "types.h"

struct Src { u8 pad[0x8]; s32 m8; };
struct Ent { Src *m0; f32 m4; f32 m8; };
struct X { u8 pad[0xC]; s32 mC; u8 pad10[0xC]; s32 m1C; };
struct Mgr { s32 m80; void *m84; s32 m88; void *m8C; };
struct Obj { u8 pad[0x104]; s32 *m104; u8 pad108[0x18]; u8 m120[4]; };
struct It {
    Ent *volatile p;
    bool operator==(const It &o) const { return p == o.p; }
    s32 operator!=(const It &o) const { return (p == o.p) ^ 1; }
    It &operator++() { p++; return *this; }
    Ent &operator*() const { return *p; }
};
struct Vec {
    s32 m0; s32 count; Ent *data;
    It begin() { It r; r.p = data; return r; }
    It end() { It r; r.p = data + count; return r; }
};

static inline u8 ok(X *x) { s32 r = x->m1C != 0; if (r) { r = x->mC > 0; } return r; }
static inline bool itEq(It *a, It *b) { return a->p == b->p; }
static inline bool itNe(It *a, It *b) { return !itEq(a, b); }

extern "C" {
void ModelApplyMotionBlendKeys_1505a0(Obj *, X *, f32, X *, f32, f32);
s32 ArrayGetCountIndirect_1527c0(void *);
void *OperatorNewArray_100900(s32);
void *ConstructNewArray_100710(void *, s32, s32, s32, s32);
void AnimBlendBufInit_153370(Mgr *, void *, s32, void *, s32);
void Vec3VectorReserve_171230(Vec *, s32);
void AmixerSampleEventsMaybe_170590(void *, Vec *, f32);
void AnimBlendBufAccumulate_1533f0(Mgr *, s32, f32, f32);
void Vec3VectorDeletingDtor_1713b0(Vec *, s32);
void AnimBlendBufApplyToModel_171430(Mgr *, Obj *);
void OperatorDeleteArray_100820(void *);
}

static inline s32 collect(X *x, Vec *v, f32 f)
{
    if (!ok(x)) {
        return 0;
    }
    AmixerSampleEventsMaybe_170590(&x->mC, v, f);
    return 1;
}

extern "C" s32 ModelApplyMotionBlend_171680(Obj *obj, X *a, X *b, f32 fa, f32 fb, f32 fc)
{
    It it;
    It end;
    f32 w[2];
    X *objs[2];
    f32 fs[2];
    Vec vec;
    Mgr mgr;
    s32 n1;
    s32 n2;
    s32 *p;
    u8 *z;
    u32 n;
    s32 i;
    s32 r;
    void *b1;
    X *x;
    Ent *e;
    X **po;
    f32 *pf;

    if (obj == 0 || a == 0 || b == 0) {
        return 0;
    }
    if (!ok(a) && !ok(b)) {
        ModelApplyMotionBlendKeys_1505a0(obj, a, fa, b, fb, fc);
        return 1;
    }
    p = obj->m104;
    if (p == 0) {
        return 0;
    }
    n1 = *p;
    n2 = ArrayGetCountIndirect_1527c0(obj->m120);
    mgr.m88 = 0;
    mgr.m80 = 0;
    b1 = ConstructNewArray_100710(OperatorNewArray_100900(n1 * 0x60 + 0x10), 0, 0, 0x60, n1);
    AnimBlendBufInit_153370(&mgr, b1, n1, ConstructNewArray_100710(OperatorNewArray_100900(n2 * 0x30 + 0x10), 0, 0, 0x30, n2), n2);
    z = (u8 *)w; n = 8; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); }
    w[0] = 1.0f - fc;
    w[1] = fc;
    z = (u8 *)objs; n = 8; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); }
    objs[0] = a;
    objs[1] = b;
    z = (u8 *)fs; n = 8; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); }
    fs[0] = fa;
    fs[1] = fb;
    for (i = 0; i < 2; i++) {
        vec.m0 = 0;
        vec.count = 0;
        vec.data = 0;
        Vec3VectorReserve_171230(&vec, 0x20);
        pf = &fs[i];
        po = &objs[i];
        if (collect(*po, &vec, *pf)) {
            it.p = vec.data;
            end.p = vec.data + vec.count;
            while (it != end) {
                e = it.p;
                AnimBlendBufAccumulate_1533f0(&mgr, e->m0->m8, e->m4, e->m8 * w[i]);
                it.p = it.p + 1;
            }
        } else {
            AnimBlendBufAccumulate_1533f0(&mgr, (s32)*po, *pf, w[(u32)i]);
        }
        Vec3VectorDeletingDtor_1713b0(&vec, 0);
    }
    AnimBlendBufApplyToModel_171430(&mgr, obj);
    if (mgr.m84 != 0) {
        OperatorDeleteArray_100820((u8 *)mgr.m84 - 0x10);
    }
    if (mgr.m8C != 0) {
        OperatorDeleteArray_100820((u8 *)mgr.m8C - 0x10);
    }
    return 1;
}
