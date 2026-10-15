#include "types.h"

extern void XformGetMatrix_2e7750(void *p0, void *p1);
extern void EventVolumeRecDebugDraw_2e49b0(s32 p0, s32 p1, void *p2, s32 p3);
extern void MatMulPoint_1cb8e0(void *p0, void *p1, void *p2);
extern void DrawWireCubeAt_1cc160(s32 p0, void *p1, f32 p3, s32 p2);
extern const f32 D_0045B080;

void EvTargetDebugDraw_352440(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 sp70[0x40];
    u8 sp60[0x10];
    f32 prod;
    s32 i;

    if (arg2 == 0)
        return;

    XformGetMatrix_2e7750(arg0 + 0x38, sp70);
    EventVolumeRecDebugDraw_2e49b0(arg2, arg1, sp70, arg3);
    i = 0;
    prod = 0.25f * D_0045B080;
    while (i < *(s32 *)(arg0 + 0x130)) {
        MatMulPoint_1cb8e0(sp60, sp70, arg0 + i * 0x10 + 0xD0);
        DrawWireCubeAt_1cc160(arg1, sp60, prod, arg3);
        i++;
    }
}
