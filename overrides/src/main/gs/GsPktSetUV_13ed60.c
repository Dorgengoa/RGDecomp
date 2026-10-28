/* rg-override: replaces game/src/main/gs/GsPktSetUV_13ed60.c sha256 a6e519c109697a3ba91f33a0e9ae1ecf1d644813c335b7fa76ba696712f9003a
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* UV (reg 3) from texel coordinates: `sll 4` (32-bit, result sign-extended)
   then v << 16 | u as 64-bit values. */
void GsPktSetUV_13ed60(void *pkt, s32 u, s32 v)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    s32 uf = (s32)((u32)u << 4);
    s32 vf = (s32)((u32)v << 4);
    *(u64 *)(p + 0x0) = (u64)(s64)uf | ((u64)(s64)vf << 16);
    *(u64 *)(p + 0x8) = 3;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
