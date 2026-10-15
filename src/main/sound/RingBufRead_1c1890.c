#include "types.h"

typedef struct {
    u8 pad0[4];
    u8 *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    volatile s32 unk14;
    u8 unk18;
    u8 pad19;
    u8 unk1A;
    u8 pad1B;
    u8 pad1C[4];
    s32 unk20;
    volatile s32 unk24;
} S_001c1890;

typedef struct Lock {
    volatile s32 *s;
} Lock;

extern s32 RingBufSplitSpan_1c1aa0(s32 *, s32 *, s32, u32, s32);
extern void RingBufConsume_1c1bd0(S_001c1890 *, s32);
extern s32 SignalSema(s32);
extern s32 WaitSema(s32);
extern void *memcpy(void *, const void *, u32);

s32 RingBufRead_1c1890(S_001c1890 *arg0, u8 *dst, u32 req)
{
    s32 size;
    s32 base;
    s32 avail;
    s32 u;
    s32 total;
    s32 i;
    s32 count;
    s32 *sz;
    s32 d;
    volatile s32 *t;
    s32 v;
    volatile Lock lk2;
    volatile Lock lk;
    s32 offs[2];
    s32 sizes[2];

    t = &arg0->unkC;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    avail = arg0->unk10 - arg0->unk14;
    if (avail == 0 && arg0->unk18 != 0) {
        u = 0;
    } else if (avail <= 0) {
        u = avail + arg0->unk8;
    } else {
        u = avail;
    }
    if (arg0->unk24 != 0) {
        d = arg0->unk24 - arg0->unk20;
        if (d < u) {
            u = d;
        }
    }
    t = lk.s;
    base = arg0->unk14;
    size = arg0->unk8;
    if (*t > 0) {
        SignalSema(*t);
    }
    if (u == 0 || (u32)u < req) {
        t = &arg0->unkC;
        v = *t;
        lk2.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        if (arg0->unk1A != 0) {
            req = u;
        } else {
            t = lk2.s;
            if (*t > 0) {
                SignalSema(*t);
            }
            return 0;
        }
        t = lk2.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
    count = RingBufSplitSpan_1c1aa0(offs, sizes, base, req, size);
    total = 0;
    for (i = 0; i < count; i++) {
        sz = &sizes[i];
        if (*sz != 0) {
            memcpy(dst, arg0->unk4 + offs[i], *sz);
            dst += *sz;
            total += *sz;
        }
    }
    RingBufConsume_1c1bd0(arg0, total);
    return total;
}
