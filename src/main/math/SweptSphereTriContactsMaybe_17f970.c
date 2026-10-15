#pragma optimization_level 3
#include "types.h"
#include "vec.h"
#pragma vu0_mmi_reg_binding on
extern __int128 vz17f970 asm("vf0");

extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void MtxTransformPoints_13c810(Vec4 *, Mtx4 *, Vec4 *, s32);
extern void VecTriCross_13de70(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
extern s32 SphereTriIntersectMaybe_17fb20(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
extern void sceVu0OuterProduct(Vec4 *, Vec4 *, Vec4 *);
extern void sceVu0TransposeMatrix(Mtx4 *, Mtx4 *);
extern f32 D_0047D444;

s32 SweptSphereTriContactsMaybe_17f970(Vec4 *pos, Vec4 *dir, Vec4 *rot, Vec4 *v, Vec4 *out)
{
    Mtx4 m;
    Mtx4 mt;
    Vec4 up;
    Vec4 t[5];
    Vec4 pts[11];
    f32 y;
    s32 n;
    s32 i;
    Vec4 *p;

    VecNormalize_13bd90(&m.r[1], dir);
    y = m.r[1].y;
    *(s32 *)&m.r[1].w = 0;
    VEC4_ZERO(up);
    if (y < 0.0f) {
        y = -y;
    }
    if (y < D_0047D444) {
        up.y = 1.0f;
    } else {
        up.z = 1.0f;
    }
    sceVu0OuterProduct(&m.r[0], &m.r[1], &up);
    *(s32 *)&m.r[0].w = 0;
    sceVu0OuterProduct(&m.r[2], &m.r[0], &m.r[1]);
    *(s32 *)&m.r[2].w = 0;
    if (out) { out = (Vec4 *)(s32)(u32)out; }
    p = &m.r[3];
    if (p) { p = (Vec4 *)(s32)(u32)p; }
    *(__int128 *)p = vz17f970;
    sceVu0TransposeMatrix(&mt, &m);
    t[0] = rot[0];
    t[0].w = 1.0f;
    t[1] = rot[1];
    t[1].w = 1.0f;
    t[2] = rot[2];
    t[2].w = 1.0f;
    t[3] = *v;
    *(s32 *)&t[3].w = 0;
    t[4] = *pos;
    t[4].w = 1.0f;
    MtxTransformPoints_13c810(t, &mt, t, 5);
    VecTriCross_13de70(&t[3], &t[0], &t[1], &t[2]);
    VecNormalize_13bd90(&t[3], &t[3]);
    t[4].w = pos->w;
    n = SphereTriIntersectMaybe_17fb20(&t[4], t, &t[3], pts);
    if (n == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        pts[i].w = 1.0f;
    }
    MtxTransformPoints_13c810(out, &m, pts, n);
    return n;
}
