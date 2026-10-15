#include "types.h"

extern void MtxMulPoint_13c890(f32 *, void *, void *);
extern void VecSub_13be40(f32 *, f32 *, void *);
extern void VecAdd_13be20(f32 *, f32 *, void *);
extern s32  SegmentSphereIntersect_13da60(f32 *, f32 *, f32 *, f32);

/* Two-argument sibling of DynColliderEllipsoidHitSegmentMaybe_1668f0: same body, the second source vector
   comes from p+0xD0 instead of the caller's second object.  Stack locals are
   allocated in REVERSE declaration order and v2 is EIGHT floats, which is
   what leaves 0x50($29) unused and sizes the frame to 0x80. */

s32 DynColliderEllipsoidHitSweptPointMaybe_166a50(u8 *p, void *r)
{
    f32 v0[4];
    f32 v1[4];
    f32 v2[8];
    f32 v3[4];

    MtxMulPoint_13c890(v0, p + 0x50, r);
    VecSub_13be40(v0, v0, p + 0x120);
    v0[0] = v0[0] / *(f32 *)(p + 0x130);
    v0[1] = v0[1] / *(f32 *)(p + 0x134);
    v0[2] = v0[2] / *(f32 *)(p + 0x138);
    MtxMulPoint_13c890(v1, p + 0xD0, r);
    VecSub_13be40(v1, v1, p + 0x120);
    v1[0] = v1[0] / *(f32 *)(p + 0x130);
    v1[1] = v1[1] / *(f32 *)(p + 0x134);
    v1[2] = v1[2] / *(f32 *)(p + 0x138);
    if (SegmentSphereIntersect_13da60(v1, v0, v2, 1.0f) > 0) {
        v3[0] = v2[0] * *(f32 *)(p + 0x130);
        v3[1] = v2[1] * *(f32 *)(p + 0x134);
        v3[2] = v2[2] * *(f32 *)(p + 0x138);
        VecAdd_13be20(v3, v3, p + 0x120);
        MtxMulPoint_13c890(r, p + 0x10, v3);
        return 1;
    }
    return 0;
}
