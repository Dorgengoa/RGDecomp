/* rgp:protos */
#define RGP_SELF_RingBufSetLoop_1c1670 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

extern void WaitSema(s32 sema);
extern void SignalSema(s32 sema);

void RingBufSetLoop_1c1670(void *self, u32 v)
{
    u8 *p = (u8 *)self;
    volatile struct Lock { volatile s32 *s; } lk;
    volatile s32 *t;
    s32 n;

    t = (volatile s32 *)(p + 0xC);
    n = *t;
    lk.s = t;
    if (n > 0) {
        WaitSema(*t);
    }
    *(u8 *)(p + 0x28) = 1;
    *(u32 *)(p + 0x2C) = *(u32 *)(p + 0x0) * (v / *(u32 *)(p + 0x0));
    *(u32 *)(p + 0x30) = v % *(u32 *)(p + 0x0);
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
}
