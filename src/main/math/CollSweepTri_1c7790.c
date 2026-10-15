#include "types.h"

extern u8 CollSweepTriFace_1c7950(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 CollSweepTriEdge_1c7bf0(void *arg0, s32 arg1, s32 arg2);
extern u8 CollSweepTriVertex_1c7f30(void *arg0, s32 arg1);
extern void TriCalcBounds_1cb540(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3, s32 arg4);

s32 CollSweepTri_1c7790(u8 *o, s32 a, s32 b, s32 c)
{
    f32 mn[3];
    f32 mx[3];
    u8 r;

    TriCalcBounds_1cb540(mn, mx, a, b, c);
    if (mn[0] < *(f32 *)(o + 0x50) || mn[1] < *(f32 *)(o + 0x54) || mn[2] < *(f32 *)(o + 0x58)) return 0;
    if (!(mx[0] <= *(f32 *)(o + 0x60)) || !(mx[1] <= *(f32 *)(o + 0x64)) || !(mx[2] <= *(f32 *)(o + 0x68))) return 0;
    r = CollSweepTriFace_1c7950(o, a, b, c) != 0;
    r = (r | CollSweepTriEdge_1c7bf0(o, a, b)) != 0;
    r = (r | CollSweepTriEdge_1c7bf0(o, b, c)) != 0;
    r = (r | CollSweepTriEdge_1c7bf0(o, c, a)) != 0;
    r = (r | CollSweepTriVertex_1c7f30(o, a)) != 0;
    r = (r | CollSweepTriVertex_1c7f30(o, b)) != 0;
    r = (r | CollSweepTriVertex_1c7f30(o, c)) != 0;
    return r;
}
