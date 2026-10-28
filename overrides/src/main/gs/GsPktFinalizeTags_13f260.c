/* rg-override: replaces game/src/main/gs/GsPktFinalizeTags_13f260.c sha256 9044c6f38f5a5316ec28e1267621c47d09513bf2b963d9fa523b04f97722c648
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* Patches the open DMA tag (+0x104), VIF DIRECT code (+0x108) and GIF tag
   (+0x100) with the qword counts up to the cursor (+0xF4); rewinds the cursor
   to +0xF8 when nothing was written.  With +0x114 set (a REGLIST/PACKED GIF
   tag opened by GsPktOpenGifTag) the GIF NLOOP is the qword count divided by
   the register count at +0x118. */
#define PK_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PK_PTR(p, o) (*(u8 **)((u8 *)(p) + (o)))

void GsPktFinalizeTags_13f260(void *pkt)
{
    u8 *cur = PK_PTR(pkt, 0xF4);
    u8 *base = PK_PTR(pkt, 0xF8);
    s32 ndma = (s32)(cur - base) / 16 - 1;
    s32 nvif = (s32)(cur - PK_PTR(pkt, 0xFC)) / 16 - 1;
    s32 ngif = (s32)(cur - PK_PTR(pkt, 0x100)) / 16 - 1;

    if (ndma <= 0 || nvif <= 0) {
        PK_PTR(pkt, 0xF4) = base;
        return;
    }
    *(u32 *)PK_PTR(pkt, 0x104) = (u32)ndma | 0x10000000u;
    *(u32 *)PK_PTR(pkt, 0x108) = (u32)nvif | 0x50000000u;
    if (PK_S32(pkt, 0x114) == 0) {
        *(u32 *)PK_PTR(pkt, 0x100) = (u32)ngif | 0x8000u;
    } else {
        s32 nreg = PK_S32(pkt, 0x118);
        /* retail: `div` then `break 7` when nreg == 0 (trap); the port
           stores NLOOP 0 instead of trapping. */
        s32 nloop = nreg != 0 ? ngif / nreg : 0;
        *(u32 *)PK_PTR(pkt, 0x100) = (u32)nloop | 0x8000u;
    }
}
