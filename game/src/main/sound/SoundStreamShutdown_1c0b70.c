/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_SoundStreamShutdown_1c0b70 1
#define RGP_SELF_s_isBusy 1
#define RGP_SELF_s_isEmpty 1
#define RGP_SELF_s_isRunning 1
#define RGP_SELF_s_kick 1
#define RGP_SELF_s_lock 1
#define RGP_SELF_s_push 1
#define RGP_SELF_s_unlock 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 PollSema(s32);
s32 WaitSema(s32);
s32 SignalSema(s32);
s32 DeleteSema(s32);
s32 TerminateThread(s32);
s32 DeleteThread(s32);
/*rgp*/
struct Lock {
    volatile s32 *s;
};

typedef struct S1c0b70 {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
    volatile s32 sema10;
    s32 w14;
    s32 w18;
    u8 b1C;
    u8 b1D;
    u8 b1E;
    u8 pad1F[0x38 - 0x1F];
    s32 thread;
    s32 sema3C;
    volatile s32 sema40;
    s8 b44;
    u8 b45;
    u8 pad46[2];
    u8 b48;
    u8 pad49[3];
    s32 rd;
    s32 wr;
    u8 ring[16];
    s32 w64;
    s32 w68;
    s32 w6C;
    s32 w70;
    u8 b74;
    u8 pad75[3];
    s32 w78;
} S1c0b70;

static inline void s_lock(S1c0b70 *s) {
    if (s->sema40 > 0) {
        WaitSema(s->sema40);
    }
}
static inline void s_unlock(S1c0b70 *s) {
    if (s->sema40 > 0) {
        SignalSema(s->sema40);
    }
}
static inline void s_kick(S1c0b70 *s) {
    if (s->sema3C > 0 && PollSema(s->sema3C) < 0) {
        SignalSema(s->sema3C);
    }
}
static inline s32 s_isEmpty(S1c0b70 *s) {
    return s->b48 != 0 && s->rd == s->wr;
}
static inline s32 s_isRunning(S1c0b70 *s) {
    s32 r;
    s_lock(s);
    r = s->b44 != 0;
    s_unlock(s);
    return r;
}
static inline u16 s_push(S1c0b70 *s, u8 v) {
    u16 sent;
    s_lock(s);
    if (s->b48 == 0 && s->rd == s->wr) {
        sent = 0;
    } else {
        s->ring[s->wr] = v;
        s->wr = (s->wr + 1) & 0xF;
        s->b48 = 0;
        sent = 1;
    }
    s_unlock(s);
    return sent;
}
static inline s32 s_isBusy(S1c0b70 *s) {
    s32 busy = 0;
    s_lock(s);
    if (s->b45 != 0 || !s_isEmpty(s)) {
        busy = 1;
    }
    s_unlock(s);
    return busy;
}

void SoundStreamShutdown_1c0b70(S1c0b70 *s)
{
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk __attribute__((aligned(16)));

    if (s_isRunning(s)) {
        if (s_push(s, 2)) {
            s_kick(s);
        }
        for (; (rg_spin_hint(0x001C0C54), 1);) {
            if (!s_isBusy(s)) {
                break;
            }
            s_kick(s);
        }
    }
    SoundStreamQueueStop_1bff30(s);
    for (; (rg_spin_hint(0x001C0CF8), 1);) {
        if (!s_isBusy(s)) {
            break;
        }
        s_kick(s);
    }
    if (s->thread > 0) {
        TerminateThread(s->thread);
        DeleteThread(s->thread);
        s->thread = -1;
    }
    if (s->sema3C > 0) {
        DeleteSema(s->sema3C);
    }
    s->sema3C = -1;
    if (s->sema40 > 0) {
        DeleteSema(s->sema40);
    }
    s->sema40 = -1;
    {
        t = &s->sema10;
        v = *t;
        lk.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        s->w14 = 0;
        s->w18 = 0;
        s->b1C = 1;
        s->b1E = 0;
        s->b1D = 0;
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
    if (s->sema10 > 0) {
        DeleteSema(s->sema10);
    }
    s->sema10 = -1;
    s->w8 = 0;
    s->wC = 0;
    s->w0 = -1;
    s->w70 = 0;
    s->thread = -1;
    s->b44 = -1;
    s->b48 = 1;
    s->rd = 0;
    s->wr = 0;
    s->w64 = 0;
    s->w6C = 0;
    s->b45 = 0;
    s->w68 = 0;
    s->b74 = 0;
    s->w78 = 0;
}
