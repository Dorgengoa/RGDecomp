#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    f32 t0;
    f32 t1;
    u8 pad8[8];
    V4 c0;
    V4 d0;
    V4 e0;
    V4 f0;
    f32 x100;
    f32 x104;
} Ray;

typedef struct {
    u8 pad0[0x46];
    s16 unk46;
    u8 pad48[0x18];
} Obj;

extern s32 CollSweepTri_1c7790(V4 *, Obj *, void *, void *);
extern f32 VecLengthSq_1cb470(V4 *);
extern void VecMinMax_1cb570(V4 *, V4 *, V4 *, V4 *);
extern void VecLinearCombine_1cb8b0(V4 *, V4 *, V4 *, f32, f32);
extern void VecScale_1cbca0(V4 *, V4 *, f32);
extern void VecSub_1cbd00(V4 *, V4 *, V4 *);
extern void VecAdd_1cbdc0(V4 *, V4 *, V4 *);
extern void VecCopyAsPoint_1cbe10(V4 *, V4 *);
extern void VecCopyAsDir_1cbe20(V4 *, V4 *);
extern void VecCopy_1cbe30(s32, void *);

static inline void clear(u8 *q, u32 n)
{
    if (q) {
        for (; n != 0; n--) {
            *q++ = 0;
        }
    }
}

s32 CollRaycastNearestHit_1c8ad0(V4 *dst, s32 id, Obj *obj, s32 n, s32 mask, V4 *arg3, V4 *arg4, f32 *out)
{
    Ray r;
    V4 a;
    V4 b;
    V4 e;
    V4 c;
    V4 d;
    s32 best;
    Obj *o;
    s32 i;
    s32 k;

    if (out != NULL) {
        *out = 1.0f;
    }
    if (obj == NULL || n <= 0) {
        return -1;
    }
    VecCopyAsPoint_1cbe10(&b, arg3);
    VecCopyAsDir_1cbe20(&a, arg4);
    r.t0 = 0.0f;
    r.x100 = r.t0 * r.t0;
    r.x104 = VecLengthSq_1cb470(&a);
    r.t1 = 1.0f;
    VecLinearCombine_1cb8b0(&c, &a, &b, 1.0f, 1.0f);
    VecMinMax_1cb570(&r.d0, &r.c0, &b, &c);
    clear((u8 *)&d, sizeof(d));
    d.x = r.t0;
    d.y = r.t0;
    d.z = r.t0;
    VecAdd_1cbdc0(&r.f0, &r.d0, &d);
    VecSub_1cbd00(&r.e0, &r.c0, &d);
    k = id;
    best = -1;
    o = obj;
    for (i = 0; i < n; i++, o++) {
        if (!(o->unk46 & mask) && CollSweepTri_1c7790(&b, o, (u8 *)o + 0x10, (u8 *)o + 0x20) != 0) {
            best = i;
            k = id;
        }
    }
    if (out != NULL) {
        *out = r.t1;
    }
    if (best >= 0) {
        VecScale_1cbca0(&e, arg4, r.t1);
        VecAdd_1cbdc0(dst, &e, arg3);
        VecCopy_1cbe30(k, (u8 *)&obj[best] + 0x30);
    }
    return best;
}
