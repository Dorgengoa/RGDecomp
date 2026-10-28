/* rg-override: replaces game/src/main/gs/GsPktSetXYZPixelVec_13ef70.c sha256 58f64316ae301619888d68cf2871b00d8ecc90707585c63412b24d895a59d450
 * why: asm body (asmexclude, L5 library); C port from the retail listing
 * (docs/UNBOUND-TRIAGE.md P1: an overridden sibling exists) */
#include "types.h"

/* XYZ2 (reg 5) from a pixel-coordinate s32[3] vector: as GsPktSetXYZPixel_13f110,
   x<<4 + origin X (+0x120), y<<4 + origin Y (+0x124) sign-extended, z in 63:32. */
void GsPktSetXYZPixelVec_13ef70(void *pkt, const s32 *v)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    s32 xf = (s32)(((u32)v[0] << 4) + *(u32 *)((u8 *)pkt + 0x120));
    s32 yf = (s32)(((u32)v[1] << 4) + *(u32 *)((u8 *)pkt + 0x124));
    *(u64 *)(p + 0x0) = ((u64)(u32)v[2] << 32) | (u64)(s64)xf | ((u64)(s64)yf << 16);
    *(u64 *)(p + 0x8) = 5;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
