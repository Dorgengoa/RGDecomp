#include "types.h"
#pragma opt_propagation off
#ifdef __cplusplus
#define BOOL bool
#else
#define BOOL s32
#endif

typedef struct {
    s16 delta;
    u8 status;
    u8 _3;
    s8 d1;
    s8 d2;
} SeqEvent;

typedef struct {
    s8 _0[4];
    s16 tempo;
    s8 _6[2];
    SeqEvent *first;
} SeqTrack;

typedef struct {
    s8 on;
    s8 key;
    s8 vel;
    s8 x;
} SeqNote;

typedef struct {
    s8 _0;
    s8 _1;
    s8 prog;
    s8 _3;
    s8 b4;
    s8 b5;
    s8 b6;
    s8 b7;
    SeqNote notes[1];
} SeqChan;

typedef struct {
    s32 a;
    s32 b;
    SeqTrack *trk;
    SeqEvent *cur;
    s32 time;
    s32 acc;
    s32 _18;
    s32 loopTime;
    SeqEvent *loopPtr;
    s32 loopFlag;
    s32 paused;
    s32 nch;
    SeqChan ch[1];
} Seq;

#ifdef __cplusplus
extern "C" {
#endif
s32 SoundSeqUpdate_1b5540(Seq *s, f32 f);
extern s32 SoundSeqControlChange_1b4fb0(Seq *, s32, s32, s32);
extern s32 SoundSeqNoteOnOff_1b5160(Seq *, s32, s32, s32);
extern s32 SoundSendPitchBend_1b7fc0(s32, s32, s32, s32, s32, s32);
extern s32 SoundSendKeyOff_1b8090(s32, s32, s32, s32, s32);
#ifdef __cplusplus
}
#endif

static inline BOOL chValid(Seq *s, s32 c) {
    if (c < 0 || c >= s->nch) return 0;
    return 1;
}

s32 SoundSeqUpdate_1b5540(Seq *s, f32 f) {
    s32 ch;
    SeqEvent *ev;
    s32 i;

    SeqTrack *t = s->trk;

    if (t == 0) {
        return 1;
    }
    if (s->paused != 0) {
        return 0;
    }
    if (t != 0) {
        s32 d = (s32)((f32)t->tempo * f / 60.0f);
        s->time += d;
        s->acc += d;
    }
    if (s->cur == 0) {
        if ((s->cur = s->trk->first) == 0) {
            return 1;
        }
    }
    s->loopFlag = 0;
    for (;;) {
        ev = s->cur;
        if (ev->status == 0) {
            if (s->loopFlag == 0) {
                for (i = 0; i < s->nch; i++) {
                    if (chValid(s, i)) {
                        SeqNote *n = (SeqNote *)((s8 *)s + i * 12 + 0x38);
                        SoundSendKeyOff_1b8090(s->a, s->b, n->key, n->vel, n->x);
                        n->on = 0;
                    }
                }
                s->acc = 0;
                s->time = 0;
                s->trk = 0;
                s->cur = 0;
                return 1;
            }
            break;
        }
        if (ev->delta > s->acc) {
            break;
        }
        s->acc -= ev->delta;
        ch = s->cur->status & 0xF;
        {
            s32 ok = ch < s->nch;
            if (ok) {
                s->ch[ch].b7 = 1;
            }
        }
        ev = s->cur;
        switch (ev->status & 0xF0) {
        case 0x90:
            SoundSeqNoteOnOff_1b5160(s, ch, ev->d1, ev->d2);
            break;
        case 0x80: {
            s32 key = ev->d1;
            if (chValid(s, ch)) {
                s32 c2 = ch;
                s8 *pp = &s->ch[c2].prog;
                SeqNote *n;
                SeqNote *res;
                s32 r;
                s8 prog = *pp;
                n = s->ch[c2].notes;
                for (i = 0; i < 1; i++, n++) {
                    if (n->on == 0 || n->key != prog || n->vel != key) continue;
                    {
                        res = n;
                        goto found;
                    }
                }
                res = 0;
            found:
                n = res;
                if (n == 0) {
                    r = 0;
                } else {
                    n->on = 0;
                    r = 1;
                }
                if (r) {
                    SoundSendKeyOff_1b8090(s->a, s->b, *pp, key, s->ch[ch].b6);
                }
            }
            break;
        }
        case 0xB0:
            SoundSeqControlChange_1b4fb0(s, ch, ev->d1, ev->d2);
            ev = s->cur;
            if (ev->d1 == 0x6E) {
                if (ev->d2 == 0) {
                    s->loopTime = s->time;
                    s->loopPtr = s->cur;
                }
                if (s->cur->d2 == 0x7F) {
                    s->loopFlag = 1;
                }
            }
            break;
        case 0xC0: {
            s8 p = ev->d1;
            if (chValid(s, ch)) {
                s->ch[ch].prog = p;
            }
            break;
        }
        case 0xE0: {
            u8 lo = ev->d1;
            u8 hi = ev->d2;
            if (chValid(s, ch)) {
                SeqChan *c = &s->ch[ch];
                c->b4 = lo;
                c->b5 = hi;
                if (chValid(s, ch) && c->b7 != 0) {
                    SoundSendPitchBend_1b7fc0(s->a, s->b, c->notes[0].key, c->notes[0].vel,
                                 ((c->b5 & 0x7F) << 7) + (c->b4 & 0x7F), c->b6);
                }
            }
            break;
        }
        }
        s->cur++;
    }
    if (s->loopFlag != 0) {
        s->cur = s->loopPtr;
    }
    return 0;
}
