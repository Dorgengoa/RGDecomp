#include "types.h"

#pragma divbyzerocheck on

extern "C" {
void WaitSema(s32);
void SignalSema(s32);
s32 FileReadChunked_180400(s32, s32, s32);
s32 RingBufSplitSpan_1c1aa0(s32 *, s32 *, s32, u32, u32);
u32 RingBufCommitFill_1c1da0(void *, u32);
void FileSlotSeekThunk_180ed0(s32, s32, s32);
}

struct Lock {
    volatile s32 *s;
};

struct Ring {
    u32 blk;
    s32 base;
    s32 size;
    s32 sema;
    s32 rd;
    s32 wr;
    u8 full;
    u8 pad19;
    u8 x1A;
    u8 pad1B;
    s32 x1C;
    s32 x20;
    s32 x24;
    u8 x28;
    u8 pad29[3];
    s32 x2C;
};

extern "C" s32 RingBufGetWriteSpan_1c2010(volatile Ring *, u32 *, u32 *);

static inline u32 rdown(u32 v, u32 b) { return b * (v / b); }
static inline u32 rup(u32 v, u32 b) { return b * (v / b + 1); }

static inline bool IsDone(volatile Ring *r)
{
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk2;
    bool b;

    t = &r->sema;
    v = *t;
    lk2.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    if (r->x24 == 0) {
        t = lk2.s;
        if (*t > 0) {
            SignalSema(*t);
        }
        return false;
    }
    b = (u32)r->x1C >= (u32)r->x24;
    t = lk2.s;
    if (*t > 0) {
        SignalSema(*t);
    }
    return b;
}

extern "C" s32 RingBufFillFromFile_1c1090(volatile Ring *r, s32 fd, f32 rate)
{
    u32 avail;
    u32 size;
    s32 start;
    u32 need;
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk;
    s32 n;
    s32 pos;
    bool ok;
    s32 total;
    s32 off[2];
    s32 len[2];
    s32 cnt;
    s32 i;
    s32 got;
    bool flag;
    bool done;
    bool fire;
    u32 have;
    volatile struct Lock lk3;
    volatile struct Lock lk4;


    total = 0;
    start = RingBufGetWriteSpan_1c2010(r, &avail, &size);
    need = (u32)(rate * (f32)size);
    t = &r->sema;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    n = r->wr - r->rd;
    if (n == 0 && r->full == 0) {
        have = 0;
    } else {
        if (n <= 0) {
            n += r->size;
        }
        have = rdown(n, r->blk);
    }
    ok = have >= need;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
    if (avail != 0 && ok) {
        cnt = RingBufSplitSpan_1c1aa0(off, len, start, avail, size);
        for (i = 0; i < cnt; i++) {
            s32 *lp;
            if (*(lp = len + i) != 0) {
                got = FileReadChunked_180400(fd, r->base + off[i], *lp);
                if (got >= 0) {
                    total += got;
                    if ((u32)got % r->blk != 0) {
                        got = rup(got, r->blk);
                    }
                    RingBufCommitFill_1c1da0((void *)r, got);
                }
            }
        }
    }
    flag = false;
    if (r->x24 != 0) {
        if (avail < have && avail == 0) {
            flag = true;
        }
    } else if (ok && total == 0) {
        flag = true;
    }
    if (flag) {
        if (r->x28 != 0) {
            pos = 0;
            fire = false;
            done = IsDone(r);
            if (done) {
                t = &r->sema;
                v = *t;
                lk3.s = t;
                if (v > 0) {
                    WaitSema(*t);
                }
                if (r->x28 != 0) {
                    pos = r->x2C;
                    fire = true;
                    r->x1C = pos;
                    r->x1A = 0;
                } else {
                    r->x1A = 1;
                }
                t = lk3.s;
                if (*t > 0) {
                    SignalSema(*t);
                }
            }
            if (fire) {
                FileSlotSeekThunk_180ed0(fd, pos, 0);
            }
        } else {
            t = &r->sema;
            v = *t;
            lk4.s = t;
            if (v > 0) {
                WaitSema(*t);
            }
            r->x1A = 1;
            t = lk4.s;
            if (*t > 0) {
                SignalSema(*t);
            }
        }
    }
    return total;
}
