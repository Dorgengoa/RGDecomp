/* rg-override: replaces game/src/main/gs/GsPktSetXYZPixel_13f110.c sha256 5fc919fe4724c9a44f6a2222514887dcdbc3068b108aa47f5927e391749bf837
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* XYZ2 (reg 5) from pixel coordinates: x<<4 + origin X (+0x120),
   y<<4 + origin Y (+0x124), z in bits 63:32.  X and Y are sign-extended to
   64 bits before the OR (as retail). */
void GsPktSetXYZPixel_13f110(void *pkt, s32 x, s32 y, s32 z)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    s32 xf = (s32)(((u32)x << 4) + *(u32 *)((u8 *)pkt + 0x120));
    s32 yf = (s32)(((u32)y << 4) + *(u32 *)((u8 *)pkt + 0x124));
    *(u64 *)(p + 0x0) = ((u64)(u32)z << 32) | (u64)(s64)xf | ((u64)(s64)yf << 16);
    *(u64 *)(p + 0x8) = 5;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
