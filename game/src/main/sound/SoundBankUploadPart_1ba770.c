/* rgp:protos */
#define RGP_SELF_SoundBankUploadPart_1ba770 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct Sub {
    s32 x0;
    s32 x4;
    u32 x8;
    u32 xC;
    s32 x10;
    u8 pad14[0x38 - 0x14];
} Sub;

typedef struct Ent {
    s32 h;
    s32 x4;
    s32 x8;
    u8 padC[8];
    s32 x14;
    Sub subs[5];
    u8 pad130[0x1E0 - 0x130];
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0049E880[];
extern u8 D_0049E894[];
extern Ent D_0049EB10[];

void SoundBankUploadPart_1ba770(s32 idx, s32 sub, s32 src, u32 size, s32 arg4, u32 total)
{
    Ent *e;
    Sub *s;
    s32 h;
    s32 align;
    s32 min;
    s32 t;

    if (idx < 0 || idx > 0x10) {
        e = NULL;
    } else {
        e = &D_0049EB10[idx];
    }
    if (e == NULL) {
        return;
    }
    if (sub < 0 || sub >= 5) {
        s = NULL;
    } else {
        s = &e->subs[sub];
    }
    if (s == NULL) {
        return;
    }
    h = e->h;
    if (h == 0) {
        return;
    }
    if (size & 3) {
        size = ((size >> 2) + 1) * 4;
    }
    t = IopHeapAllocLocked_1c22d0(size + 4);
    s->x4 = t;
    if (t != 0) {
        SifDmaSendSync_1c21e0(src, (t + 3) & ~3, size);
    }
    s->x8 = 0;
    align = D_0049E880[0];
    min = *(s32 *)(D_0049E894 + idx * 0x24);
    if (align < 0x40) {
        align = 0x40;
    }
    if (align % 64 != 0) {
        align = (align / 64 + 1) * 64;
    }
    if (min > 0 && total < (u32)min) {
        total = min;
    }
    if (total % (u32)align != 0) {
        total = align * (total / (u32)align + 1);
    }
    if (e->x14 > 0) {
        s->x8 = BlockHeapAllocBottomAddr_1c2430(h, total, align);
    } else if (e->x14 < 0) {
        s->x8 = BlockHeapAllocTopAddr_1c2400(h, total, align);
    }
    if (s->x8 != 0) {
        t = IopHeapAllocLocked_1c22d0(0x404);
        SoundSpuTransferChunks_1b6450(arg4, s->x8, total, (t + 3) & ~3, 0x400);
        IopHeapFreeLocked_1c2290(t);
    }
    t = SoundSendCmd_1b6cc0(5, 5, -1, (s->x4 + 3) & ~3, size, (*(volatile __typeof__(s->x8) *)&(s->x8)), total);
    s->xC = total;
    s->x10 = t;
    if (e->x4 >= 0) {
        SoundSendCmd_1b6cc0(8, 3, e->x4, s->x10, sub);
    }
    if (e->x8 >= 0) {
        SoundSendCmd_1b6cc0(8, 3, e->x8, s->x10, sub);
    }
}
