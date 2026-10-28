/* rg-override: replaces game/src/main/gs/GsPktBeginPrimAD_13f6b0.c sha256 ceb0903fedaec9d5106d3e07439ac3b23285540d73b5e0b359017ba27b9208cd
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* Opens a DMA tag + VIF DIRECT qword, an A+D GIF tag (NREG 1, REGS 0xE) and
   writes the PRIM register (reg 0) from the u64 at +0x70. */
#define PK_PTR(p, o) (*(u8 **)((u8 *)(p) + (o)))

void GsPktBeginPrimAD_13f6b0(void *pkt)
{
    u8 *p;

    PK_PTR(pkt, 0xF8) = PK_PTR(pkt, 0xF4);
    PK_PTR(pkt, 0xFC) = PK_PTR(pkt, 0xF4);
    p = PK_PTR(pkt, 0xF4);
    *(u32 *)(p + 0x0) = 0;
    *(u32 *)(p + 0x4) = 0;
    *(u32 *)(p + 0x8) = 0;
    *(u32 *)(p + 0xC) = 0;
    PK_PTR(pkt, 0x104) = p;
    PK_PTR(pkt, 0x108) = p + 0xC;

    p = PK_PTR(pkt, 0xF4);
    PK_PTR(pkt, 0xF4) = p + 0x10;
    PK_PTR(pkt, 0x100) = p + 0x10;
    *(u32 *)(p + 0x10) = 0x8000;
    *(u32 *)(p + 0x14) = 0x10000000;
    *(u32 *)(p + 0x18) = 0xE;
    *(u32 *)(p + 0x1C) = 0;

    p = PK_PTR(pkt, 0xF4);
    PK_PTR(pkt, 0xF4) = p + 0x10;
    *(u64 *)(p + 0x10) = *(u64 *)((u8 *)pkt + 0x70);
    *(u64 *)(p + 0x18) = 0;
    PK_PTR(pkt, 0xF4) = p + 0x20;
}
