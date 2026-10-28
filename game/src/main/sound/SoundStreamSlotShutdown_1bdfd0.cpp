#include "types.h"
#pragma inline_depth(4)

extern "C" {

typedef struct Q {
    u8 pad0[4];
    s32 w4;
    u8 pad8[4];
    volatile s32 sema;
    u8 pad10[0x3C];
    s8 b4C;
    u8 b4D;
    u8 pad4E[2];
    u8 b50;
    u8 pad51[3];
    u32 head;
    u32 tail;
    u8 buf[24];
} Q;

s32 WaitSema(s32);
s32 SignalSema(s32);
void SoundRpcWorkerKick_1bd6a0(void);
void SoundStreamSlotInit_1be9f0(Q *);
s32 GetSoundStreamTable_1bf7c0(void);
void SoundStreamCloseByHandle_1bf7d0(s32, s32 *);
void SemaHandleDelete_1c2150(volatile s32 *);

struct Lock {
    volatile s32 *s;
};

static inline bool IsEmpty(Q *q) {
    return q->b50 != 0 && q->head == q->tail;
}

static inline bool BusyA(Q *q) {
    s32 r = 0;
    if (q->sema > 0) {
        WaitSema(q->sema);
    }
    if (q->b4D != 0 || !IsEmpty(q)) {
        r = 1;
    }
    if (q->sema > 0) {
        SignalSema(q->sema);
    }
    return r;
}

static inline bool Busy(Q *q) {
    s32 r = 0;
    if (q->sema > 0) {
        WaitSema(q->sema);
    }
    if (q->b4D != 0 || !IsEmpty(q)) {
        r = 1;
    }
    if (q->sema > 0) {
        SignalSema(q->sema);
    }
    return r ? r != 0 : 0;
}

static inline s32 StateIs(Q *q, s32 st) {
    volatile Lock lk __attribute__((aligned(16)));
    volatile s32 *t;
    s32 v;
    bool r;

    t = &q->sema;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    r = q->b4C == st;
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
    return r;
}

static inline void Push(Q *q, u8 cmd) {
    volatile Lock lk __attribute__((aligned(16)));
    volatile s32 *t;
    s32 v;

    t = &q->sema;
    v = *t;
    lk.s = t;
    if (v > 0) {
        WaitSema(*t);
    }
    if (q->b50 != 0 || q->head != q->tail) {
        q->buf[q->tail] = cmd;
        q->tail = (q->tail + 1) % 24;
        q->b50 = 0;
    }
    t = lk.s;
    if (*t > 0) {
        SignalSema(*t);
    }
}

static inline void PushW(Q *q, u8 cmd) { Push(q, cmd); }
void SoundStreamSlotShutdown_1bdfd0(Q *q) {
    s32 sp4C;
    s32 h;

    while ((Busy(q) ? 0 : StateIs(q, 0)) == 0) {
        PushW(q, 2);
        for (;;) {
            if (!BusyA(q)) {
                break;
            }
            SoundRpcWorkerKick_1bd6a0();
        }
    }
    while ((Busy(q) ? 0 : StateIs(q, 7)) == 0) {
        PushW(q, 0xA);
        for (;;) {
            if (!BusyA(q)) {
                break;
            }
            SoundRpcWorkerKick_1bd6a0();
        }
    }
    SemaHandleDelete_1c2150(&q->sema);
    h = GetSoundStreamTable_1bf7c0();
    sp4C = q->w4;
    SoundStreamCloseByHandle_1bf7d0(h, &sp4C);
    SoundStreamSlotInit_1be9f0(q);
}

}
