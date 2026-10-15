#include "types.h"

#pragma divbyzerocheck on

void WaitSema(s32);
void SignalSema(s32);
struct Lock {
    volatile s32 *s;
};

struct Ring {
    u32 blk;
    s32 x4;
    s32 size;
    s32 sema;
    s32 rd;
    s32 wr;
    u8 full;
    u8 pad19[3];
    s32 x1C;
    s32 x20;
    s32 x24;
};

static inline u32 rdown(u32 v, u32 b) { return b * (v / b); }
static inline u32 rup(u32 v, u32 b) { return b * (v / b + 1); }

s32 RingBufGetWriteSpan_1c2010(volatile struct Ring *r, s32 *out1, s32 *out2)
{
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;
    s32 n;
    s32 avail;
    s32 m;
    s32 ret;

    t = &r->sema;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    n = r->wr - r->rd;
    if (n == 0 && r->full == 0) {
        avail = 0;
    } else {
        if (n <= 0) {
            n += r->size;
        }
        avail = rdown(n, r->blk);
    }
    if (r->x24 != 0) {
        m = r->x24 - r->x1C;
        if (m < 0) {
            m = 0;
        }
        if ((u32)m % r->blk != 0) {
            m = rup(m, r->blk);
        }
        if (m < avail) {
            avail = m;
        }
    }
    *out1 = avail;
    {
        s32 x = r->size;
        t = lk.s;
        *out2 = x;
    }
    ret = r->rd;
    if (*t > 0) {
        SignalSema(*t);
    }
    return ret;
}
