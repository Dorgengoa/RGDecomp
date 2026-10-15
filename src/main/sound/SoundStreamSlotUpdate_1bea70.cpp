#include "types.h"

typedef struct Q2ea70 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Q2ea70;

typedef struct Str8ea70 {
    s32 m0;
    s32 m4;
    u8 pad8[0x1C - 8];
    s32 m1C;
    s32 m24pad;
    s32 m24;
    u8 pad28[0x34 - 0x28];
    s32 m34;
    s32 m38[2][3];
    s32 m50;
    u8 pad54[0x7C - 0x54];
    s32 m7C[2][3];
} Str8ea70;

typedef struct Snd {
    u8 pad0[4];
    s32 m4;
    Str8ea70 *m8;
    s32 sema;
    u8 *m10;
    u8 m14;
    u8 m15;
    u8 pad16[2];
    s32 m18;
    s32 m1C[2][3];
    s32 m34[2][3];
    s8 m4C;
    u8 m4D;
    u8 pad4E[2];
    u8 qEmpty;
    u8 pad51[3];
    u32 qHead;
    u32 qTail;
    s8 q[24];
    u8 pad74[8];
    u8 q2Empty;
    u8 pad7D[3];
    s32 q2Head;
    s32 q2Tail;
    Q2ea70 q2[4];
    s32 mC8;
    f32 mCC;
    Q2ea70 mD0;
    s32 mE0;
    u8 padE4[8];
    s32 mEC;
    u8 padF0[0x100 - 0xF0];
    s32 m100;
    s32 m104;
    u8 m108;
} Snd;

typedef struct Lk {
    volatile s32 *s;
} Lk;

extern "C" {
void WaitSema(s32);
void SignalSema(s32);
s32 WavHeaderParse_1bc220(Str8ea70 *, s32, s32);
s32 SoundGetVblankCount_1bd750(void);
void SoundStreamSlotSendToIopMaybe_1bd760(Snd *);
s32 SoundStreamSlotFillFromRingBuf_1bdb80(Snd *, s32);
s32 GetSoundStreamTable_1bf7c0(void);
void SoundStreamHandleResolve_1bfa50(s32 *, s32, s32 *);
void SoundStreamLockDtor_1bfab0(s32 *, s32);
s32 SoundStreamLockAcquire_1bfb40(s32 *);
void SoundStreamQueueFill_1bfdf0(s32);
s32 SoundStreamQueueSeek_1c00a0(s32, s32);
s32 SoundStreamQueueClose_1c01b0(s32);
s32 SoundStreamIsOpen_1c0280(s32);
s32 SoundStreamQueueOpen_1c0360(s32, u8 *);
s32 SoundStreamWaitIdle_1c0510(s32, s32);
void RingBufClearLoop_1c1610(s32);
void RingBufSetLoop_1c1670(s32, s32);
void RingBufReset_1c1810(s32);
s32 RingBufAddrAt_1c1a70(s32, s32);
s32 RingBufGetEndFlag_1c1b10(s32);
void RingBufSetLimit_1c1b70(s32, s32);
void RingBufConsume_1c1bd0(s32, s32);
s32 RingBufGetReadSpan_1c1f30(s32, s32 *, s32 *);
extern f32 D_0047D1D0;
}

#define LOCK(lk, p) { volatile s32 *t_ = &(p)->sema; s32 v_ = *t_; (lk).s = t_; if (v_ > 0) WaitSema(*t_); }
#define UNLOCK(lk) { volatile s32 *t_ = (lk).s; if (*t_ > 0) SignalSema(*t_); }

static inline bool qEmpty(Snd *p)
{
    return p->qEmpty != 0 && p->qHead == p->qTail;
}

static inline bool qPeek(Snd *p, s32 *out)
{
    if (qEmpty(p)) {
        return false;
    }
    *out = p->q[p->qHead];
    return true;
}

static inline void qPop(Snd *p, s32 *out)
{
    if (p->qEmpty == 0 || p->qHead != p->qTail) {
        *out = p->q[p->qHead];
        p->qHead = (p->qHead + 1) % 24;
        if (p->qHead == p->qTail) {
            p->qEmpty = 1;
        }
    }
}

extern "C" s32 SoundStreamSlotUpdate_1bea70(Snd *p)
{
    volatile Lk lk0;
    s32 lkA;
    s32 lkB;
    s32 o110;
    s32 o10C;
    s32 lkC;
    s32 lkD;
    s32 lkE;
    s32 lkF;
    volatile Lk lk1;
    volatile Lk lk2;
    s32 lkG;
    s32 oEC;
    s32 oE8;
    volatile Lk lk3;
    s32 lkH;
    s32 idA;
    s32 idB;
    s32 idC;
    s32 idD;
    s32 idE;
    s32 idF;
    s32 idG;
    s32 idH;
    volatile Lk lk4;
    s32 ctx;
    bool fA;
    bool fB;
    bool fC;
    bool fD;
    bool fE;
    s32 c;
    f32 f;

    ctx = GetSoundStreamTable_1bf7c0();
    fA = false;
    fB = false;
    fC = false;
    fD = false;
    LOCK(lk0, p);
    if (p->m4C == 7) {
        UNLOCK(lk0);
        return 1;
    }
    if (!qPeek(p, &c)) {
        c = 0;
    }
    if ((u8)c == 6) {
        goto q2;
    }
    if ((u8)c == 7) {
        bool v;
    q2:
        if (p->q2Empty != 0 && p->q2Head == p->q2Tail) {
            v = false;
        } else {
            p->mD0 = ((Q2ea70 *)((u8 *)p + 0x88))[p->q2Head];
            p->q2Head = (p->q2Head + 1) & 3;
            if (p->q2Head == p->q2Tail) {
                p->q2Empty = 1;
            }
            v = true;
        }
        if (v) {
            if (!(p->mD0.y < 0.0f)) {
                p->mCC = p->mD0.y;
            } else {
                p->mD0.y = p->mCC;
            }
            if ((u8)c == 6) {
                p->mC8 = 9;
            } else {
                p->mC8 = 10;
            }
        }
        qPop(p, &c);
        if (!qPeek(p, &c)) {
            c = 0;
        }
    }
    if ((u8)c == 9) {
        p->mCC = 1.0f;
        p->mC8 = 8;
        qPop(p, &c);
        if (!qPeek(p, &c)) {
            c = 0;
        }
    }
    switch (p->m4C) {
    case 0:
        fE = true;
        if ((u8)c == 1) {
            idA = p->m4;
            SoundStreamHandleResolve_1bfa50(&lkA, ctx, &idA);
            if (SoundStreamQueueOpen_1c0360(SoundStreamLockAcquire_1bfb40(&lkA), p->m10) != 0) {
                p->m4C = 1;
                p->m4D = 1;
            }
            p->m10[0] = 0;
            SoundStreamLockDtor_1bfab0(&lkA, -1);
        }
        break;
    case 1:
        fE = false;
        idB = p->m4;
        SoundStreamHandleResolve_1bfa50(&lkB, ctx, &idB);
        if (SoundStreamWaitIdle_1c0510(SoundStreamLockAcquire_1bfb40(&lkB), 0) != 0) {
            SoundStreamLockDtor_1bfab0(&lkB, -1);
            break;
        }
        if (SoundStreamIsOpen_1c0280(SoundStreamLockAcquire_1bfb40(&lkB)) == 0) {
            p->m4C = 0;
            p->m4D = 0;
            SoundStreamLockDtor_1bfab0(&lkB, -1);
            break;
        }
        {
            s32 s = SoundStreamLockAcquire_1bfb40(&lkB) + 4;
            RingBufGetReadSpan_1c1f30(s, &o110, &o10C);
            if (o110 == 0 && RingBufGetEndFlag_1c1b10(s) == 0) {
                SoundStreamQueueFill_1bfdf0(SoundStreamLockAcquire_1bfb40(&lkB));
                SoundStreamLockDtor_1bfab0(&lkB, -1);
                break;
            }
        }
        p->m4C = 3;
        p->m4D = 1;
        fA = true;
        SoundStreamLockDtor_1bfab0(&lkB, -1);
        break;
    case 2:
        fE = false;
        idC = p->m4;
        SoundStreamHandleResolve_1bfa50(&lkC, ctx, &idC);
        if (SoundStreamWaitIdle_1c0510(SoundStreamLockAcquire_1bfb40(&lkC), 0) != 0) {
            SoundStreamLockDtor_1bfab0(&lkC, -1);
            break;
        }
        RingBufReset_1c1810(SoundStreamLockAcquire_1bfb40(&lkC) + 4);
        p->m4C = 0;
        p->m4D = 0;
        SoundStreamLockDtor_1bfab0(&lkC, -1);
        break;
    case 4:
        fE = true;
        if ((u8)c == 4) {
            fC = true;
            p->m4C = 5;
            break;
        }
        if ((u8)c == 8) {
            if (p->mC8 != 8) {
                fE = false;
            }
        }
        fB = true;
        break;
    case 5:
        fE = true;
        if ((u8)c == 3) {
            p->m4C = 4;
            break;
        }
        if ((u8)c != 5) {
            break;
        }
        idD = p->m4;
        SoundStreamHandleResolve_1bfa50(&lkD, ctx, &idD);
        {
            Str8ea70 *s = p->m8;
            if (SoundStreamQueueSeek_1c00a0(SoundStreamLockAcquire_1bfb40(&lkD), s->m0 + p->m18 * s->m1C) != 0) {
                s32 i;
                s32 j;
                Str8ea70 *d;
                p->m4C = 6;
                p->m15 = 1;
                d = p->m8;
                d->m50 = p->m18;
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 3; j++) {
                        d->m7C[i][j] = p->m1C[i][j];
                        d->m38[i][j] = p->m34[i][j];
                    }
                }
            }
        }
        SoundStreamLockDtor_1bfab0(&lkD, -1);
        break;
    case 6:
        fE = false;
        idE = p->m4;
        SoundStreamHandleResolve_1bfa50(&lkE, ctx, &idE);
        if (SoundStreamWaitIdle_1c0510(SoundStreamLockAcquire_1bfb40(&lkE), 0) != 0) {
            SoundStreamLockDtor_1bfab0(&lkE, -1);
            break;
        }
        p->m15 = 0;
        p->m4C = 5;
        SoundStreamLockDtor_1bfab0(&lkE, -1);
        break;
    case 3:
    default:
        fE = true;
        break;
    }
    if (fE) {
        if ((u8)c == 2) {
            idF = p->m4;
            fB = false;
            fC = true;
            fA = false;
            SoundStreamHandleResolve_1bfa50(&lkF, ctx, &idF);
            if (SoundStreamIsOpen_1c0280(SoundStreamLockAcquire_1bfb40(&lkF)) != 0) {
                if (SoundStreamQueueClose_1c01b0(SoundStreamLockAcquire_1bfb40(&lkF)) != 0) {
                    p->m4C = 2;
                    p->m4D = 1;
                } else {
                    fE = false;
                }
            } else {
                p->m4C = 0;
                p->m4D = 0;
            }
            SoundStreamLockDtor_1bfab0(&lkF, -1);
        } else if ((u8)c == 10) {
            p->m4C = 7;
            fB = false;
            fC = false;
            p->m4D = 1;
            fA = false;
            fD = true;
        }
    }
    if (fE) {
        qPop(p, &c);
    }
    UNLOCK(lk0);
    if (fD) {
        LOCK(lk1, p);
        p->m4D = 0;
        UNLOCK(lk1);
        return 1;
    }
    if (p->mC8 != 8) {
        bool done;
        LOCK(lk2, p);
        f = ((p->mD0.z - p->mD0.y) / p->mD0.x) / 60.0f;
        done = false;
        if (p->mC8 == 9) {
            if (f <= 0.0f) {
                done = true;
            }
        }
        if (p->mC8 == 10) {
            if (!(f < 0.0f)) {
                done = true;
            }
        }
        if (!done) {
            if (!(p->mD0.w <= 0.0f)) {
                f32 t = p->mD0.w - D_0047D1D0;
                p->mD0.w = t;
                if (t < 0.0f) {
                    p->mD0.w = 0.0f;
                } else {
                    f = 0.0f;
                }
            }
            {
                s32 k = SoundGetVblankCount_1bd750();
                if (p->mE0 != k) {
                    p->mE0 = k;
                } else {
                    f = 0.0f;
                }
            }
            if (p->mC8 == 9) {
                p->mCC += f;
                if (!(p->mCC < p->mD0.z)) {
                    p->mCC = p->mD0.z;
                    p->mC8 = 8;
                }
            } else if (p->mC8 == 10) {
                p->mCC += f;
                if (p->mCC <= p->mD0.z) {
                    p->mCC = p->mD0.z;
                    p->mC8 = 8;
                }
            } else {
                done = true;
            }
        }
        if (done) {
            p->mCC = 1.0f;
            p->mC8 = 8;
        }
        UNLOCK(lk2);
    }
    if (fA) {
        idG = p->m4;
        fE = false;
        SoundStreamHandleResolve_1bfa50(&lkG, ctx, &idG);
        c = SoundStreamLockAcquire_1bfb40(&lkG) + 4;
        if (WavHeaderParse_1bc220(p->m8, RingBufAddrAt_1c1a70(c, RingBufGetReadSpan_1c1f30(c, &oEC, &oE8)), p->m14) != 0) {
            fE = true;
            RingBufSetLimit_1c1b70(c, p->m8->m0 + p->m8->m4);
            if (p->m8->m24 != 0) {
                RingBufSetLoop_1c1670(c, p->m8->m0 + p->m8->m34);
            } else {
                RingBufClearLoop_1c1610(c);
            }
            RingBufConsume_1c1bd0(c, p->m8->m0);
        }
        SoundStreamLockDtor_1bfab0(&lkG, -1);
        LOCK(lk3, p);
        if (fE) {
            p->m4C = 5;
        }
        p->m4D = 0;
        UNLOCK(lk3);
        p->m100 = 0;
        p->m104 = 0;
        p->m108 = 1;
    }
    if (fB) {
        idH = p->m4;
        SoundStreamHandleResolve_1bfa50(&lkH, ctx, &idH);
        if ((s8)SoundStreamSlotFillFromRingBuf_1bdb80(p, SoundStreamLockAcquire_1bfb40(&lkH) + 4) == 2) {
            LOCK(lk4, p);
            if (p->qEmpty != 0 || p->qHead != p->qTail) {
                p->q[p->qTail] = 4;
                p->qTail = (p->qTail + 1) % 24;
                p->qEmpty = 0;
            }
            UNLOCK(lk4);
        } else {
            SoundStreamQueueFill_1bfdf0(SoundStreamLockAcquire_1bfb40(&lkH));
        }
        SoundStreamLockDtor_1bfab0(&lkH, -1);
        SoundStreamSlotSendToIopMaybe_1bd760(p);
    } else {
        p->mEC = 0;
    }
    if (fC) {
        p->mEC = 0;
    }
    return 0;
}
