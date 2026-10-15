#pragma opt_propagation off
#include "types.h"

typedef struct Obj {
    s16 x0;
    s16 x2;
    u16 pad4;
    u16 x6;
    u8 x8[0x20];
    f32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    s32 x4C;
} Obj;

extern void FrameCalcWorldMatrix_148ff0(s32, f32 (*)[4]);
extern void MatMulVec4Args_1cb7f0(f32 *, f32 (*)[4], f32, f32, f32, f32);
extern void VecNormalize_1cbb80(f32 *, f32 *);
extern s32 GetObjNodeByName_1ce3a0(s32, s32, void *);

s32 NodeRefUpdateWorldPos_319290(Obj *arg0)
{
    f32 m[4][4];
    f32 v[4];
    s32 t;
    s32 b;

    arg0->x40 = arg0->x34;
    arg0->x44 = arg0->x38;
    arg0->x48 = arg0->x3C;
    arg0->x4C = 0;
    b = (arg0->x6 & 1) != 0;
    arg0->x6 = b ? (arg0->x6 | 2) : (arg0->x6 & ~2);
    t = GetObjNodeByName_1ce3a0(arg0->x0, arg0->x2, arg0->x8);
    arg0->x4C = t;
    if (t == 0) {
        return 0;
    }
    FrameCalcWorldMatrix_148ff0(t, m);
    VecNormalize_1cbb80(m[0], m[0]);
    VecNormalize_1cbb80(m[1], m[1]);
    VecNormalize_1cbb80(m[2], m[2]);
    MatMulVec4Args_1cb7f0(v, m, arg0->x28, arg0->x2C, arg0->x30, 1.0f);
    arg0->x34 = v[0];
    arg0->x38 = v[1];
    arg0->x3C = v[2];
    arg0->x6 = arg0->x6 | 1;
    return 1;
}
