/* rg-override: replaces game/src/main/gs/GsPktSetUVFixed_13ed90.c sha256 ab62bb053ed7eb2ce7396d29e44246893590189f1db112df16f4611393e7aecb
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* UV (reg 3) from values already in 12.4 fixed point; both are
   sign-extended to 64 bits before the OR (as retail). */
void GsPktSetUVFixed_13ed90(void *pkt, s32 u, s32 v)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    *(u64 *)(p + 0x0) = (u64)(s64)u | ((u64)(s64)v << 16);
    *(u64 *)(p + 0x8) = 3;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
