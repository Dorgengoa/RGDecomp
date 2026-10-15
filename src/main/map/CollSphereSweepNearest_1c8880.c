#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V001c8880;

typedef struct {
    V001c8880 start;
    V001c8880 dir;
    f32 r;
    f32 t;
    u8 pad28[8];
    V001c8880 a;
    V001c8880 b;
    V001c8880 c;
    V001c8880 d;
    f32 r2;
    f32 len;
    u8 pad78[8];
} Sweep001c8880;

typedef struct {
    u8 pad0[0x46];
    s16 flags;
    u8 pad48[0x18];
} Tri001c8880;

extern f32 VecLengthSq_1cb470(V001c8880 *);
extern void VecMinMax_1cb570(V001c8880 *, V001c8880 *, V001c8880 *, V001c8880 *);
extern void VecLinearCombine_1cb8b0(V001c8880 *, V001c8880 *, V001c8880 *, f32, f32);
extern void VecNormalize_1cbb80(V001c8880 *, V001c8880 *);
extern void VecSub_1cbd00(V001c8880 *, V001c8880 *, V001c8880 *);
extern void VecAdd_1cbdc0(V001c8880 *, V001c8880 *, V001c8880 *);
extern void VecCopyAsPoint_1cbe10(V001c8880 *, V001c8880 *);
extern void VecCopyAsDir_1cbe20(V001c8880 *, V001c8880 *);
extern s32 CollSweepTri_1c7790(Sweep001c8880 *, void *, void *, void *);
extern void ClosestPointOnTri_1c9b60(V001c8880 *, void *, void *, void *, V001c8880 *);

static inline void clr(void *p, s32 n)
{
    if (p != NULL) {
        do {
            *((u8 *)p)++ = 0;
        } while (--n);
    }
}

s32 CollSphereSweepNearest_1c8880(V001c8880 *arg0, V001c8880 *arg1, Tri001c8880 *tris, s32 count, s32 mask, V001c8880 *from, V001c8880 *to, f32 *outp, f32 r)
{
    Sweep001c8880 sw;
    V001c8880 v100;
    V001c8880 vF0;
    V001c8880 vE0;
    V001c8880 vD0;
    s32 best;
    Tri001c8880 *p;
    s32 i;
    V001c8880 *k;

    if (outp != NULL) {
        *outp = 1.0f;
    }
    if (tris == NULL || count <= 0) {
        return -1;
    }
    VecCopyAsPoint_1cbe10(&sw.start, from);
    VecCopyAsDir_1cbe20(&sw.dir, to);
    r = (r < 0.0f) ? -r : r;
    sw.r2 = r * r;
    sw.r = r;
    sw.len = VecLengthSq_1cb470(&sw.dir);
    sw.t = 1.0f;
    VecLinearCombine_1cb8b0(&vE0, &sw.dir, &sw.start, 1.0f, 1.0f);
    VecMinMax_1cb570(&sw.b, &sw.a, &sw.start, &vE0);
    clr(&vD0, 0x10);
    vD0.x = sw.r;
    vD0.y = sw.r;
    vD0.z = sw.r;
    VecAdd_1cbdc0(&sw.d, &sw.b, &vD0);
    VecSub_1cbd00(&sw.c, &sw.a, &vD0);
    k = arg1;
    best = -1;
    p = tris;
    for (i = 0; i < count; i++, p++) {
        if (!(p->flags & mask) && CollSweepTri_1c7790(&sw, p, (u8 *)p + 0x10, (u8 *)p + 0x20) != 0) {
            best = i;
            k = arg1;
        }
    }
    if (outp != NULL) {
        *outp = sw.t;
    }
    if (best >= 0) {
        VecLinearCombine_1cb8b0(&v100, to, from, sw.t, 1.0f);
        ClosestPointOnTri_1c9b60(arg0, &tris[best], (u8 *)&tris[best] + 0x10, (u8 *)&tris[best] + 0x20, &v100);
        VecSub_1cbd00(&vF0, &v100, arg0);
        VecNormalize_1cbb80(k, &vF0);
    }
    return best;
}
