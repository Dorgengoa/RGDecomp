#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 *buf;
    u8 *desc;
    s32 size;
    s32 rd;
    s32 cnt;
    s32 bytes;
    u8 pad18[0x40 - 0x18];
    s32 sema;
    s32 active;
} Ring001d4240;

typedef struct {
    u32 lo : 28;
    u32 hi : 4;
} Chcr001d4240;

extern void DmaTagMake_1d4770(u8 *, u8 *, s32, s32);
extern void ViBufSetD4Chcr_1d47a0(u32);
extern s32 ViBufGetFifoIndex_1d4860(Ring001d4240 *, s32);
extern void SignalSema(s32);
extern void WaitSema(s32);

s32 ViBufAddDma_1d4240(Ring001d4240 *r)
{

    s32 d;
    s32 i;
    s32 n;
    u32 ch;
    s32 j;
    s32 ok;
    s32 f;
    s32 idx;
    ok = 0;
    WaitSema(r->sema);
    if (r->active == 0) {
        return 0;
    }
    ViBufSetD4Chcr_1d47a0(5);
    ch = *(volatile u32 *)0x1000B400;
    d = ViBufGetFifoIndex_1d4860(r, *(volatile s32 *)0x1000B410);
    d = (d + r->size - r->rd) % r->size;
    r->rd = (r->rd + d) % r->size;
    r->cnt = r->cnt - d;
    idx = (r->rd + r->cnt) % r->size;
    n = r->bytes / 2048;
    r->bytes = r->bytes % 2048;
    if (n > 0) {
        j = (r->size + (r->rd + r->cnt - 1)) % r->size;
        DmaTagMake_1d4770(r->desc + j * 16, r->buf + j * 2048, 3, 0x80);
        ok = 1;
    }
    for (i = 0; i < n; i++) {
        if (i == n - 1) {
            f = 0;
        } else {
            f = 3;
        }
        DmaTagMake_1d4770(r->desc + idx * 16, r->buf + idx * 2048, f, 0x80);
        idx = (idx + 1) % r->size;
    }
    r->cnt += n;
    if (r->cnt != 0) {
        if (ok) {
            ch = (ch & 0x0FFFFFFF) | 0x30000000;
        }
        ViBufSetD4Chcr_1d47a0(ch | 0x100);
    }
    SignalSema(r->sema);
    return 1;
}
