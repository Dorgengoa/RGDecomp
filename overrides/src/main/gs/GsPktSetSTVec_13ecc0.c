/* rg-override: replaces game/src/main/gs/GsPktSetSTVec_13ecc0.c sha256 85292ecb799d3050e95c0c0c458e2dee8e6c2e17344c26f8c2c9eeaf8fdd46b3
 * why: asm body (asmexclude, L5 library); C port from the retail listing
 * (docs/UNBOUND-TRIAGE.md P1: an overridden sibling exists) */
#include "types.h"

/* ST (reg 2) from an f32[3] vector: S bits 31:0, T bits 63:32; v[2] (Q) is stored at
   +0x110 for the next RGBAQ (as GsPktSetST_13ed10). */
void GsPktSetSTVec_13ecc0(void *pkt, const f32 *v)
{
    u32 sb, tb;
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    __builtin_memcpy(&sb, &v[0], 4);
    __builtin_memcpy(&tb, &v[1], 4);
    *(f32 *)((u8 *)pkt + 0x110) = v[2];
    *(u64 *)(p + 0x0) = (u64)sb | ((u64)tb << 32);
    *(u64 *)(p + 0x8) = 2;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
