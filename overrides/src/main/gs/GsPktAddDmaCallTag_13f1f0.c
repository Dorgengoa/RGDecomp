/* rg-override: replaces game/src/main/gs/GsPktAddDmaCallTag_13f1f0.c sha256 b66d5e1a04defa7e9fe8ca49b42554491a0f39a20a37283fb54eaf42ba29d95e
 * why: asm body (asmexclude, L5 library); C port from the retail listing.
 * A DMA CALL tag (word 0 = 0x50000000: id 5, QWC 0; word 1 = ADDR; the rest 0).  Retail
 * keeps the low 28 bits of the address (dsll32 4 / dsrl32 4 = the EE physical address);
 * the port's DMAC reads packets in host memory and every other tag the game builds
 * carries the host address unmasked (PS2_PHYS is the identity, include/port/hwaccess.h),
 * so ADDR is the full host pointer.  Caller: ModelDrawOffscreenCompositeMaybe_16aac0. */
#include "types.h"

void GsPktAddDmaCallTag_13f1f0(void *pkt, const void *addr)
{
    u32 *p = *(u32 **)((u8 *)pkt + 0xF4);
    p[0] = 0x50000000u;
    p[1] = (u32)(unsigned long)addr;
    p[2] = 0;
    p[3] = 0;
    *(u8 **)((u8 *)pkt + 0xF4) = (u8 *)p + 0x10;
}
