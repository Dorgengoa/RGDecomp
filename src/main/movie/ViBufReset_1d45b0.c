#include "types.h"

typedef struct {
    s64 a;
    s64 b;
    s32 pos;
    s32 len;
} Ent;

typedef struct {
    u8 *buf;
    u8 *desc;
    s32 size;
    s32 rd;
    s32 cnt;
    s32 bytes;
    u8 pad18[0x44 - 0x18];
    s32 active;
    u8 pad48[0x50 - 0x48];
    Ent *ents;
    s32 n;
    s32 count;
    s32 head;
} Ring;

void DmaTagMake_1d4770(u8 *, u32, s32, s32);
void ViBufSetD4Chcr_1d47a0(s32);

s32 ViBufReset_1d45b0(Ring *r) {
    s32 i;
    s32 j;
    u32 a;

    r->rd = 0;
    r->cnt = 0;
    r->bytes = 0;
    r->active = 1;
    r->count = 0;
    r->head = 0;
    for (i = 0; i < r->n; i++) {
        r->ents[i].a = -1;
        r->ents[i].b = -1;
        r->ents[i].pos = 0;
        r->ents[i].len = 0;
    }
    for (j = 0; j < r->size; j++) {
        a = j * 2048;
        a = (u32)(r->buf + a);
        DmaTagMake_1d4770(r->desc + j * 16, a & 0x0FFFFFFF, 3, 0x80);
    }
    DmaTagMake_1d4770(r->desc + j * 16, (u32)r->desc & 0x0FFFFFFF, 2, 0);
    *(volatile s32 *)0x1000B420 = 0;
    *(volatile u32 *)0x1000B410 = (u32)r->buf & 0x0FFFFFFF;
    *(volatile u32 *)0x1000B430 = (u32)r->desc & 0x0FFFFFFF;
    ViBufSetD4Chcr_1d47a0(5);
    return 1;
}
