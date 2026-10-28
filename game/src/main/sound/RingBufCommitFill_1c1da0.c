/* rgp:protos */
#define RGP_SELF_RingBufCommitFill_1c1da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

#pragma divbyzerocheck on

s32 SignalSema(s32);
s32 WaitSema(s32);

typedef struct {
    u32 unit;
    s32 pad4;
    u32 cap;
    s32 sema;
    volatile u32 rd;
    u32 wr;
    u8 full;
    u8 pad19[3];
    s32 f1C;
    s32 pad20;
    volatile s32 f24;
} Ring;

typedef struct Lock {
    volatile s32 *s;
} Lock;

u32 RingBufCommitFill_1c1da0(Ring *r, u32 n)
{
    volatile Lock lk __attribute__((aligned(16)));
    volatile s32 *t;
    s32 d;
    s32 avail;
    s32 e;

    if (n == 0) {
        return 0;
    }
    t = &r->sema;
    lk.s = t;
    if (r->sema > 0) {
        WaitSema(*t);
    }
    d = r->wr - r->rd;
    if (d == 0 && r->full == 0) {
        avail = 0;
    } else {
        if (d <= 0) {
            d += r->cap;
        }
        avail = r->unit * ((u32)d / r->unit);
    }
    if (r->f24 != 0) {
        e = r->f24 - r->f1C;
        if (e < 0) {
            e = 0;
        }
        if ((u32)e % r->unit != 0) {
            e = r->unit * ((u32)e / r->unit + 1);
        }
        if (e < avail) {
            avail = e;
        }
    }
    if ((u32)avail < n) {
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
        return 0;
    }
    r->rd = (r->rd + n) % r->cap;
    r->f1C += n;
    r->full = 0;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
    return n;
}
