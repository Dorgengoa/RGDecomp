/* rg-override: replaces game/src/main/gs/GsPktClose_13f5b0.c sha256 0ad625ce82a38f0e5a2b73d9890384663e8f690a2b6bdb16db0f40110f0b2afd
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern s32 MemStackAllocQw_14d950(void *stack, s32 nqw);
/* widescreen stage 2 (src/settings/rg_layout.h, docs/WIDESCREEN.md "Stage 2"): the finished
   2D packet is handed to the layout transform; a no-op unless a wide canvas is active */
extern int rg_layout_packet(void *pkt, const void *caller);
extern void nr_im_note_xscaled(void); /* src/native/render/nr_im.c */

/* Packet layout used here (byte offsets; pointers are 32-bit host pointers):
     +0x00 memory stack   +0xE8 "not open" flag   +0xEC packet base
     +0xF4 write cursor   +0xF8/+0xFC/+0x100 starts of the DMA-tag, VIF and
     GIF-tag regions      +0x104/+0x108 where to patch the DMA tag / VIF code */
#define PK_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PK_PTR(p, o) (*(u8 **)((u8 *)(p) + (o)))

void GsPktClose_13f5b0(void *pkt)
{
    u8 *cur, *base;
    s32 ndma, nvif, ngif;

    if (PK_S32(pkt, 0xE8) != 0)
        return;

    /* closing A+D NOP qword (reg 0x3F) */
    cur = PK_PTR(pkt, 0xF4);
    *(u64 *)(cur + 0x0) = 0;
    *(u64 *)(cur + 0x8) = 0x3F;
    cur = PK_PTR(pkt, 0xF4) + 0x10;
    PK_PTR(pkt, 0xF4) = cur;

    base = PK_PTR(pkt, 0xF8);
    ndma = (s32)(cur - base) / 16 - 1;
    nvif = (s32)(cur - PK_PTR(pkt, 0xFC)) / 16 - 1;
    ngif = (s32)(cur - PK_PTR(pkt, 0x100)) / 16 - 1;

    if (ndma > 0 && nvif > 0) {
        *(u32 *)PK_PTR(pkt, 0x104) = (u32)ndma | 0x10000000u; /* DMAtag cnt, QWC */
        *(u32 *)PK_PTR(pkt, 0x108) = (u32)nvif | 0x50000000u; /* VIF DIRECT, size */
        *(u32 *)PK_PTR(pkt, 0x100) = (u32)ngif | 0x8000u;     /* GIFtag NLOOP|EOP */
        if (rg_layout_packet(pkt, __builtin_return_address(0)))
            nr_im_note_xscaled(); /* squeezed 2D: upscaled point sprites unsnapped in X */
    } else {
        PK_PTR(pkt, 0xF4) = base; /* nothing drawn: rewind */
    }

    if (PK_S32(pkt, 0xE8) == 0)
        MemStackAllocQw_14d950(*(void **)pkt,
                               (s32)(PK_PTR(pkt, 0xF4) - PK_PTR(pkt, 0xEC)) / 16);
}
