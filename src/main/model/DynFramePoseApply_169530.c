#include "types.h"

typedef unsigned __int128 u128;
typedef f32 VEC[4] __attribute__((aligned(16)));

typedef struct {
    s32 type;
    s32 pad4;
    s32 *idx;
    s32 flag;
} Arg2;

extern void VecNormalize_13bd90(f32 *, f32 *);
extern void VecScale_13be00(f32 *, f32 *, f32);
extern void VecAdd_13be20(f32 *, f32 *, f32 *);
extern void VecSub_13be40(f32 *, f32 *, f32 *);
extern void MtxInverse_13cf40(VEC *, VEC *);
extern void MtxMul_13d240(VEC *, VEC *, VEC *);
extern void FrameCalcWorldMatrix_148ff0(s32, VEC *);
extern void ModelFrameSetMatrix_14a190(void *, VEC *);
extern void sceVu0OuterProduct(f32 *, f32 *, f32 *);

void DynFramePoseApply_169530(u8 *arg0, u8 *arg1, Arg2 *arg2)
{
    VEC m[4];
    VEC c0;
    VEC c1;
    VEC e;
    VEC d;
    VEC rm[4];
    s32 r1;
    s32 r2;
    s32 r0;
    s32 r3;
    s32 r4;
    VEC *base;
    f32 *p0;
    f32 *p1;
    f32 *p2;
    f32 *p3;
    s32 *idx;
    s32 obj;

    if (arg1 == NULL) {
        return;
    }
    if (arg2->type == 0) {
        return;
    }
    r1 = 0;
    r2 = 1;
    r0 = 2;
    r3 = 2;
    r4 = 0;
    if (arg2->type != 1 && arg2->type != 5) {
        if (arg2->type == 2) {
        r2 = 2;
        r3 = 0;
        r0 = 1;
        r4 = 1;
        } else {
            if (arg2->type != 6) {
                return;
            }
        r2 = 2;
        r1 = 1;
        r4 = 1;
        r3 = 0;
        r0 = 0;
        }
    }
    idx = arg2->idx;
    base = *(VEC **)(arg0 + 0xA8);
    p0 = base[idx[0]];
    p1 = base[idx[1]];
    p2 = base[idx[2]];
    p3 = base[idx[3]];
    VecAdd_13be20(c0, p0, p1);
    VecScale_13be00(c0, c0, 0.5f);
    VecAdd_13be20(c1, p2, p3);
    VecScale_13be00(c1, c1, 0.5f);
    if (arg2->type == 5) {
        VecSub_13be40(d, p3, p2);
    } else {
        VecSub_13be40(d, p1, p0);
    }
    VecNormalize_13bd90(m[r0], d);
    m[r0][3] = 0.0f;
    VecSub_13be40(e, c1, c0);
    VecNormalize_13bd90(m[r1], e);
    m[r1][3] = 0.0f;
    sceVu0OuterProduct(m[r2], m[r3], m[r4]);
    m[r2][3] = 0.0f;
    sceVu0OuterProduct(m[r3], m[r4], m[r2]);
    VecNormalize_13bd90(m[r3], (f32 *)m + r3 * 4);
    *(u128 *)m[3] = *(u128 *)c0;
    m[3][3] = 1.0f;
    if (arg2->flag != 0) {
        obj = *(s32 *)(arg1 + 4);
        if (obj != 0) {
            FrameCalcWorldMatrix_148ff0(obj, rm);
            MtxInverse_13cf40(rm, rm);
            MtxMul_13d240(m, rm, m);
        }
    }
    ModelFrameSetMatrix_14a190(arg1, m);
}
