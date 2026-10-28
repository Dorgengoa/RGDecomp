/* rg-override: replaces game/src/main/gs/GsPktSetXYZVecI_13eeb0.c sha256 bf629122cd0e250944ea85e04c50f7075afb26a74fcfe69c99fd20ebc607e28c
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* XYZ2 (reg 5) from an int vector (12.4 x, y; z) plus the origin. */
void GsPktSetXYZVecI_13eeb0(void *pkt, const s32 *v)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    s32 xf = (s32)((u32)v[0] + *(u32 *)((u8 *)pkt + 0x120));
    s32 yf = (s32)((u32)v[1] + *(u32 *)((u8 *)pkt + 0x124));
    *(u64 *)(p + 0x0) = ((u64)(u32)v[2] << 32) | (u64)(s64)xf | ((u64)(s64)yf << 16);
    *(u64 *)(p + 0x8) = 5;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
