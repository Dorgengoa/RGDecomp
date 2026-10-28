/* rg-override: replaces game/src/main/gs/GsPktSetXYZ_13ef10.c sha256 d0972a0ffc832c2a3e30228502c6ba453c9a1fe301e9b493950f282ad8ebef65
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* XYZ2 (reg 5) from 12.4 fixed-point x/y plus the origin at +0x120/+0x124;
   z in bits 63:32. */
void GsPktSetXYZ_13ef10(void *pkt, s32 x, s32 y, s32 z)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    s32 xf = (s32)((u32)x + *(u32 *)((u8 *)pkt + 0x120));
    s32 yf = (s32)((u32)y + *(u32 *)((u8 *)pkt + 0x124));
    *(u64 *)(p + 0x0) = ((u64)(u32)z << 32) | (u64)(s64)xf | ((u64)(s64)yf << 16);
    *(u64 *)(p + 0x8) = 5;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
