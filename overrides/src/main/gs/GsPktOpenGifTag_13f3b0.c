/* rg-override: replaces game/src/main/gs/GsPktOpenGifTag_13f3b0.c sha256 2ebec9ee545cc835081e30bd3d5439fdfdfb6be2dfa6b15de351d52864fe9731
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* Opens a DMA tag + VIF DIRECT qword (patched later by GsPktFinalizeTags)
   and a PACKED GIF tag with PRE=1: PRIM = the 11-bit prim word at +0x70,
   REGS = regs_lo/regs_hi, NREG = nreg. */
#define PK_PTR(p, o) (*(u8 **)((u8 *)(p) + (o)))

void GsPktOpenGifTag_13f3b0(void *pkt, s32 prim, s32 regs_lo, s32 regs_hi, s32 nreg)
{
    u8 *p;
    u32 primbits;

    *(s32 *)((u8 *)pkt + 0x114) = 1;
    *((u8 *)pkt + 0x70) = (u8)((*((u8 *)pkt + 0x70) & ~7) | (prim & 7));
    *(u32 *)((u8 *)pkt + 0x110) = 0x3F800000u; /* Q = 1.0f */
    PK_PTR(pkt, 0xF8) = PK_PTR(pkt, 0xF4);
    PK_PTR(pkt, 0xFC) = PK_PTR(pkt, 0xF4);

    p = PK_PTR(pkt, 0xF4);
    *(u32 *)(p + 0x0) = 0;
    *(u32 *)(p + 0x4) = 0;
    *(u32 *)(p + 0x8) = 0;
    *(u32 *)(p + 0xC) = 0;
    PK_PTR(pkt, 0x104) = p;
    PK_PTR(pkt, 0x108) = p + 0xC;
    PK_PTR(pkt, 0xF4) = PK_PTR(pkt, 0xF4) + 0x10;

    /* ld 0x70 & 0x7FF: the low 11 bits of the little-endian u64 at +0x70 */
    primbits = (*(u32 *)((u8 *)pkt + 0x70) & 0x7FF) << 15;
    *(s32 *)((u8 *)pkt + 0x118) = nreg;
    p = PK_PTR(pkt, 0xF4);
    PK_PTR(pkt, 0x100) = p;
    *(u32 *)(p + 0x0) = 0x8000;
    *(u32 *)(p + 0x4) = ((u32)*(s32 *)((u8 *)pkt + 0x118) << 28) | primbits | 0x4000;
    *(s32 *)(p + 0x8) = regs_lo;
    *(s32 *)(p + 0xC) = regs_hi;
    PK_PTR(pkt, 0xF4) = PK_PTR(pkt, 0xF4) + 0x10;
}
