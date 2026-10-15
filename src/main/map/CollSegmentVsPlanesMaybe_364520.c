#include "types.h"

typedef struct {
    f32 x, y, z, w;
} Vec4;

typedef struct {
    s32 a;
    u8 *p;
    s32 b;
    s32 c;
} Hit;

extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern f32 Vu0InnerProduct_13bd60(Vec4 *, Vec4 *);
extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern s32 MeshRaycastTris_16f3c0(Hit *, Vec4 *, Vec4 *, s32, s32, s32);
extern f32 D_0047D29C;
extern f32 D_0047F8F0;
extern f32 D_0047F8F4;
extern f32 D_0047F8F8;
extern f32 D_0047F8FC;

s32 CollSegmentVsPlanesMaybe_364520(u8 *arr, s32 n, Vec4 *p0, Vec4 *p1, s32 arg4, Vec4 *nrm, f32 *dist) {
    Hit h;
    Vec4 e;
    Vec4 d;
    Vec4 c;
    Vec4 b;
    Vec4 a;
    Vec4 m;
    s32 i;
    s32 r;
    f32 f;

    if (arr == NULL) {
        return -1;
    }
    for (i = 0; i < n; i++) {
        h.a = 1;
        h.b = 0;
        h.c = 0;
        h.p = arr + i * 0x60;
        VecNormalize_13bd90(nrm, (Vec4 *)(h.p + 0x30));
        {
            f32 *pb = (f32 *)&b;
            pb[0] = D_0047F8F0;
            pb[1] = D_0047F8F4;
            pb[2] = D_0047F8F8;
            pb[3] = D_0047F8FC;
        }
        f = Vu0InnerProduct_13bd60(nrm, &b);
        f = f < 0.0f ? -f : f;
        if (f < D_0047D29C) {
            VecSub_13be40(&a, p1, p0);
            VecNormalize_13bd90(&a, &a);
            if (!(Vu0InnerProduct_13bd60(&a, nrm) <= 0.0f)) {
                continue;
            }
            r = MeshRaycastTris_16f3c0(&h, p0, p1, arg4, 1, 0x40);
            if (r != -1) {
                *dist = 0.0f;
            }
        } else {
            VecScale_13be00(&c, nrm, *dist);
            VecSub_13be40(&e, p0, &c);
            VecSub_13be40(&d, p1, &c);
            VecSub_13be40(&m, &d, &e);
            VecNormalize_13bd90(&m, &m);
            if (!(Vu0InnerProduct_13bd60(&m, nrm) <= 0.0f)) {
                continue;
            }
            r = MeshRaycastTris_16f3c0(&h, &e, &d, arg4, 1, 0x40);
        }
        if (r != -1) {
            return 1;
        }
    }
    return 0;
}
