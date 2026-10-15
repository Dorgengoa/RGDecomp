#include "types.h"

void RingBufConsume_1c1bd0(void *, u32);
void SignalSema(s32);
void WaitSema(s32);

typedef struct {
    u8 pad0[8];
    s32 unk8;
    s32 sema;
    s32 unk10;
    s32 unk14;
    u8 unk18;
    u8 pad19[7];
    volatile u32 unk20;
    volatile u32 unk24;
    u8 unk28;
    u8 pad29[3];
    u32 unk2C;
    u32 unk30;
} Q;

struct Lock {
    volatile s32 *s;
};

static inline u8 full(Q *q)
{
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;
    u8 r;

    t = &q->sema;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    if (q->unk24 == 0) {
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
        return 0;
    }
    r = q->unk20 >= q->unk24;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
    return r;
}

static inline s32 used(Q *q)
{
    s32 d = q->unk10 - q->unk14;
    if (d == 0) {
        if (q->unk18 != 0) return 0;
    }
    if (d <= 0) d += q->unk8;
    return d;
}

s32 RingBufLoopRewind_1c1430(Q *arg0)
{
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;
    u32 n;

    if (arg0->unk28 == 0) {
        return 0;
    }
    if (!full(arg0)) {
        return 0;
    }
    t = &arg0->sema;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    if (arg0->unk30 != 0) {
        s32 d = used(arg0);
        if ((u32)d < arg0->unk30) {
            t = lk.s;
            if (*t > 0) {
                SignalSema(*t);
            }
            return 0;
        }
    }
    arg0->unk20 = arg0->unk2C;
    n = arg0->unk30;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
    if (n != 0) {
        RingBufConsume_1c1bd0(arg0, n);
    }
    return 1;
}
