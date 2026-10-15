#include "types.h"
#pragma divbyzerocheck on

struct StrmPlayer {
    u32 blockSize;
    s8 _4[0xC];
    s32 x14;
    s32 x18;
    u8 x1C;
    u8 x1D;
    u8 x1E;
    u8 _1f;
    s32 x20;
    s32 x24;
    s8 _24[0x14];
};

struct Strm {
    s32 fd;
    StrmPlayer pl;
    s32 sema2;
    volatile s32 sema;
    s8 state;
    s8 busy;
    s8 _46[2];
    u8 qflag;
    s8 _49[3];
    s32 rd;
    s32 wr;
    s8 q[16];
    u8 *ptr;
    volatile s32 cnt;
    s32 x6C;
    f32 x70;
    u8 x74;
    s8 _75[3];
    u32 x78;
};

struct StrmInfo {
    s32 pad;
    s32 a;
    s32 b;
};

struct StrmLock {
    volatile s32 *s;
};

extern "C" {
void FileSlotClose_180540(s32);
s32 FileSlotOpen_180710(u8 *, s32);
void RingBufFillFromFile_1c1090(StrmPlayer *, s32, f32);
void RingBufConsume_1c1bd0(StrmPlayer *, s32);
s32 SignalSema(s32);
s32 WaitSema(s32);
s32 FileSlotGetSizeThunk_180d50(s32, s32 *, s32);
void FileSlotSeekThunk_180ed0(s32, s32, s32);
s32 SoundStreamProcessCmds_1c05f0(Strm *s);
}

static inline void lock(Strm *s) {
    if (s->sema > 0) {
        WaitSema(s->sema);
    }
}

static inline void unlock(Strm *s) {
    if (s->sema > 0) {
        SignalSema(s->sema);
    }
}

static inline bool isEmpty(Strm *s) {
    lock(s);
    bool r = false;
    if (s->qflag && s->rd == s->wr) {
        r = true;
    }
    unlock(s);
    return r;
}

static inline bool pop(Strm *s, s8 *out) {
    if (s->qflag && s->rd == s->wr) {
        return false;
    }
    *out = s->q[s->rd];
    s->rd = (s->rd + 1) & 0xF;
    if (s->rd == s->wr) {
        s->qflag = 1;
    }
    return true;
}

static inline void closeFile(Strm *s) {
    if (s->fd >= 0) {
        FileSlotClose_180540(s->fd);
    }
    s->fd = -1;
    lock(s);
    if (s->ptr != 0) {
        *s->ptr = 0;
    }
    unlock(s);
}

s32 SoundStreamProcessCmds_1c05f0(Strm *s) {
    StrmInfo info;
    volatile StrmLock lk;
    u8 open = 0;
    bool resume = false;
    bool close = false;
    bool stop = false;
    bool start = false;
    s8 cmd;
    u8 c;

    for (;;) {
        if (!isEmpty(s)) {
            break;
        }
        if (s->sema2 > 0) {
            WaitSema(s->sema2);
        }
    }
    {
        volatile s32 *t = &s->sema;
        s32 v = *t;
        lk.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
    }
    if (!pop(s, &cmd)) {
        cmd = 0;
    }
    c = cmd;
    if (c == 4) {
        s->cnt--;
        if (s->cnt < 0) {
            s->cnt = 0;
        }
    }
    if (c == 5) {
        s->state = 5;
        stop = true;
        s->busy = 1;
    }
    switch (s->state) {
    case 0:
        if (c == 1) {
            s->state = 1;
            open = 1;
            s->busy = 1;
        }
        break;
    case 2:
        switch (c) {
        case 2:
            s->state = 3;
            close = true;
            s->busy = 1;
            break;
        case 3:
            start = true;
            s->state = 4;
            s->busy = 1;
            break;
        default:
            if (c == 4) {
                resume = true;
            }
            break;
        }
        break;
    case 5:
        break;
    }
    {
        volatile s32 *t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
    if (stop) {
        closeFile(s);
        lock(s);
        s->state = -1;
        s->busy = 0;
        unlock(s);
        return 1;
    }
    if (start) {
        s32 fd = s->fd;
        u32 total = s->x78;
        if (fd >= 0) {
            u32 bs = s->pl.blockSize;
            s32 aligned = bs * (total / bs);
            s32 rem = total % bs;
            s->pl.x14 = 0;
            s->pl.x18 = 0;
            s->pl.x1C = 1;
            s->pl.x1E = 0;
            s->pl.x1D = 0;
            s->pl.x24 = aligned;
            s->pl.x20 = aligned;
            FileSlotSeekThunk_180ed0(fd, aligned, 0);
            if (rem > 0) {
                RingBufFillFromFile_1c1090(&s->pl, fd, 0.0f);
                RingBufConsume_1c1bd0(&s->pl, rem);
            }
        }
        lock(s);
        s->state = 2;
        s->busy = 0;
        unlock(s);
    }
    if (open) {
        bool ok;
        s8 ns;
        u8 *pp = s->ptr;
        if (s->fd >= 0) {
            ok = false;
        } else {
            s32 fd = FileSlotOpen_180710(pp, 1);
            s->fd = fd;
            if (fd < 0) {
                info.b = 0;
                ok = false;
            } else {
                info.b = FileSlotGetSizeThunk_180d50(fd, &info.a, 0);
                ok = true;
            }
        }
        if (ok) {
            ns = 2;
        } else {
            s32 fd = s->fd;
            ns = 0;
            info.b = 0;
            if (fd >= 0) {
                FileSlotClose_180540(fd);
            }
            s->fd = -1;
            lock(s);
            if (s->ptr != 0) {
                *s->ptr = 0;
            }
            unlock(s);
        }
        lock(s);
        {
            s32 b_ = info.b;
            s->state = ns;
            s->x6C = b_;
        }
        s->busy = 0;
        unlock(s);
    }
    if (close) {
        closeFile(s);
        lock(s);
        s->state = 0;
        s->x6C = 0;
        s->busy = 0;
        unlock(s);
    }
    if (resume && s->fd >= 0) {
        f32 t;
        lock(s);
        t = *(volatile f32 *)&s->x70;
        if (*(volatile u8 *)&s->x74) {
            t = 0.0f;
        }
        s->x74 = 0;
        unlock(s);
        RingBufFillFromFile_1c1090(&s->pl, s->fd, t);
    }
    return 0;
}
