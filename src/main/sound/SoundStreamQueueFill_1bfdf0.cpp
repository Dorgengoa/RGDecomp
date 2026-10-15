#include "types.h"

extern "C" {
s32 PollSema(s32);
void SignalSema(s32);
void WaitSema(s32);
}

struct L1bfdf0 {
    volatile s32 *volatile p;
};

static inline void lock(L1bfdf0 *l, s32 *q)
{
    volatile s32 *s;
    l->p = q;
    s = q;
    if (*s > 0) {
        WaitSema(*s);
    }
}

static inline void unlock(L1bfdf0 *l)
{
    volatile s32 *s = l->p;
    if (*s > 0) {
        SignalSema(*s);
    }
}

struct S1bfdf0 {
    u8 pad0[0x3C];
    s32 m3C;
    volatile s32 m40;
    u8 pad44[4];
    u8 m48;
    u8 pad49[3];
    s32 m4C;
    s32 m50;
    u8 m54[0x10];
    s32 m64;
    volatile s32 m68;
};

extern "C" bool SoundStreamQueueFill_1bfdf0(S1bfdf0 *self)
{
    bool flag;
    L1bfdf0 lk;

    lock(&lk, (s32 *)&self->m40);
    if (self->m68 > 0) {
        unlock(&lk);
        return 0;
    }
    self->m68++;
    unlock(&lk);
    if (self->m40 > 0) {
        WaitSema(self->m40);
    }
    if (self->m48 == 0 && self->m4C == self->m50) {
        flag = false;
    } else {
        flag = true;
        self->m54[self->m50] = 4;
        self->m50 = (self->m50 + 1) & 0xF;
        self->m48 = 0;
    }
    if (self->m40 > 0) {
        SignalSema(self->m40);
    }
    if (flag) {
        if (self->m3C > 0 && PollSema(self->m3C) < 0) {
            SignalSema(self->m3C);
        }
    }
    return flag;
}
