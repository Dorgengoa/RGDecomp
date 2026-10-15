#include "types.h"

#pragma divbyzerocheck on

s32 SignalSema(s32);
s32 WaitSema(s32);

typedef struct {
    u32 unit;
    s32 pad4;
    u32 cap;
    s32 sema;
    u32 rd;
    u32 wr;
    u8 full;
    u8 f19;
    u8 f1A;
    u8 pad1B;
    s32 pad1C;
    u32 f20;
    volatile u32 f24;
} Ring;

typedef volatile struct { volatile s32 *s; } Lk1c1bd0;

u32 RingBufConsume_1c1bd0(Ring *r, u32 n)
{
    Lk1c1bd0 lk;
    volatile s32 *t;
    s32 v;
    s32 d;
    s32 e;
    s32 u;

    if (n == 0) {
        return 0;
    }
    t = &r->sema;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    d = *(volatile u32 *)&r->rd - *(volatile u32 *)&r->wr;
    if (d == 0 && r->full != 0) {
        u = 0;
    } else if (d <= 0) {
        u = d + r->cap;
    } else {
        u = d;
    }
    if (r->f24 != 0) {
        e = r->f24 - r->f20;
        if (e < u) {
            u = e;
        }
    }
    if ((u32)u < n) {
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
        return 0;
    }
    r->wr = (r->wr + n) % r->cap;
    r->f20 += n;
    if (r->f24 != 0 && r->f20 >= r->f24) {
        if (r->wr % r->unit != 0) {
            r->f20 = r->f24;
            r->wr = r->unit * (r->wr / r->unit + 1) % r->cap;
        }
    }
    if (r->wr == r->rd) {
        r->full = 1;
        if (r->f1A != 0) {
            r->f19 = 1;
        }
    }
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
    return n;
}
