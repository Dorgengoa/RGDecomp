/* rg-override: replaces game/src/main/gs/GsPktSetTexa_13eca0.c sha256 30092387179c11c597e2f817848ad2570b6ef29385d07de50280ce22e6045752
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* A+D write of TEXA (GS register 0x3B); the 64-bit value arrives whole in $5. */
void GsPktSetTexa_13eca0(void *pkt, u64 texa)
{
    u8 *p = *(u8 **)((u8 *)pkt + 0xF4);
    *(u64 *)(p + 0x0) = texa;
    *(u64 *)(p + 0x8) = 0x3B;
    *(u8 **)((u8 *)pkt + 0xF4) = *(u8 **)((u8 *)pkt + 0xF4) + 0x10;
}
