/* rgp:protos */
#define RGP_SELF_ClipDur 1
#define RGP_SELF_DurDiv 1
#define RGP_SELF_DurMul 1
#define RGP_SELF_MotionPlayerUpdate_172e00 1
#define RGP_SELF_SeqFrame 1
#define RGP_SELF_SeqValid 1
#include "port/game_protos.h"
#line 1
#pragma inline_depth(16)
#include "types.h"

typedef struct Frame {
    u8 pad0[0x24];
    f32 t0;
    f32 t1;
    f32 rate;
} Frame;

typedef struct Seq {
    s32 w0;
    s32 n;
    Frame *frames;
} Seq;

typedef struct Clip {
    u8 pad0[0x10];
    Seq seq;
} Clip;

typedef struct Anim {
    Clip *req;
    s32 reqFrame;
    s32 reqFlags;
    Clip *cur;
    Clip *next;
    s32 frame;
    f32 time;
    f32 prev;
    s32 flags;
    s32 state;
    s32 blending;
    s32 nextFrame;
    f32 nextTime;
    f32 blend;
    f32 blendRate;
    s32 mode;
    f32 speed;
    f32 delta;
} Anim;

static inline s32 SeqValid(s32 f, Seq *s)
{
    if (s->frames == 0) {
        return 0;
    }
    if (f < 0 || f >= s->n) {
        return 0;
    }
    return 1;
}

static inline Frame *SeqFrame(s32 f, Seq *s)
{
    return SeqValid(f, s) ? &s->frames[f] : 0;
}

static inline f32 ClipDur(Clip *c, s32 f)
{
    Seq *s;
    Frame *fr;

    if (c == 0) {
        return 0.0f;
    }
    s = &c->seq;
    if (s == 0) {
        return 0.0f;
    }
    fr = SeqFrame(f, s);
    if (fr != 0) {
        return fr->t1 - fr->t0;
    }
    return 0.0f;
}

static inline f32 DurMul(Clip *c, s32 f, f32 k)
{
    Seq *s;
    Frame *fr;

    if (c == 0) {
        return 0.0f;
    }
    s = &c->seq;
    if (s == 0) {
        return 0.0f;
    }
    fr = SeqFrame(f, s);
    if (fr != 0) {
        return k * (fr->t1 - fr->t0);
    }
    return 0.0f;
}

static inline f32 DurDiv(Clip *c, s32 f, f32 k)
{
    Seq *s;
    Frame *fr;

    if (c == 0) {
        return 0.0f;
    }
    s = &c->seq;
    if (s == 0) {
        return 0.0f;
    }
    fr = SeqFrame(f, s);
    if (fr != 0) {
        return k / (fr->t1 - fr->t0);
    }
    return 0.0f;
}

void MotionPlayerUpdate_172e00(Anim *a, f32 dt)
{
    s32 fl;
    f32 sc;
    s32 rev;
    s32 f;
    Clip *c;
    s32 blend;
    s32 changed;
    s32 keep;
    f32 t;
    f32 rate;
    f32 dur;
    Frame *fr;

    fl = a->reqFlags;
    sc = 0.0f;
    rev = 0;
    if (fl & 0x1000) {
        rev = 1;
        sc = 1.0f;
    }
    f = a->reqFrame;
    c = a->req;
    a->req = 0;
    a->reqFrame = -1;
    a->reqFlags = 0;
    if (c != 0 && SeqValid(f, (Seq *)((u32)c + 0x10))) {
        if (a->cur == 0) {
            a->cur = c;
        }
        changed = 0;
        keep = 1;
        blend = (fl & 8) != 0;
        if (a->blending != 0) {
            if (a->next == c) {
                if (a->nextFrame != f) {
                    changed = keep;
                }
            } else {
                changed = keep;
            }
        } else {
            if (a->cur == c) {
                if (a->frame != f) {
                    changed = keep;
                }
            } else {
                changed = keep;
            }
        }
        if (fl & 4) {
            keep = 0;
        }
        if (!SeqValid(a->frame, &a->cur->seq)) {
            keep = 0;
            blend = 0;
        }
        if (changed) {
            a->mode = 0;
            if (!keep) {
                a->cur = c;
                a->frame = f;
                a->time = DurMul(a->cur, f, sc);
                a->prev = a->time;
                a->next = 0;
                a->blending = 0;
                a->nextFrame = -1;
                a->nextTime = 0.0f;
                a->blend = 0.0f;
                a->blending = 0;
            } else {
                a->nextFrame = f;
                a->next = c;
                a->blending = 1;
                a->blend = 0.0f;
            }
            if (blend) {
                t = DurDiv(a->cur, a->frame, a->time);
                a->nextTime = DurDiv(a->next, a->nextFrame, t);
            } else {
                a->nextTime = DurMul(a->next, a->nextFrame, sc);
            }
        }
        a->flags = fl;
    }
    if (a->cur == 0) {
        return;
    }
    if (a->blending != 0) {
        a->blend = a->blend + a->blendRate * dt;
        a->state = 3;
        if (!(a->blend < 1.0f)) {
            a->frame = a->nextFrame;
            a->cur = a->next;
            a->prev = a->time = a->nextTime;
            a->next = 0;
            a->blending = 0;
            a->nextFrame = -1;
            a->nextTime = 0.0f;
            a->blend = 0.0f;
        }
        return;
    }
    fr = SeqFrame(a->frame, &a->cur->seq);
    rate = fr ? fr->rate : 0.0f;
    switch (a->mode) {
    case 1:
        rate = a->speed;
        break;
    case 2:
        t = a->speed;
        fr = SeqFrame(a->frame, &a->cur->seq);
        rate = fr ? t * (fr->t1 - fr->t0) : 0.0f;
        break;
    case 3:
        rate *= a->speed;
        break;
    case 0:
        break;
    }
    if (rev) {
        rate = -rate;
    }
    rate *= dt;
    if (a->flags & 1) {
        rate = 0.0f;
    }
    a->delta = rate;
    a->prev = a->time;
    a->time = a->time + rate;
    dur = ClipDur(a->cur, a->frame);
    if (rate == 0.0f) {
        if (dur == 0.0f) {
            a->state = 4;
        } else {
            a->state = 5;
        }
        return;
    }
    if (!(a->time < dur)) {
        if (a->flags & 2) {
            a->time = dur;
            a->state = 4;
            return;
        }
        a->time = a->time - dur;
        if (!(a->time < dur)) {
            a->time = 0.0f;
        }
        a->state = 4;
        return;
    }
    if (a->time <= 0.0f) {
        if (a->flags & 2) {
            a->time = 0.0f;
            a->state = 4;
            return;
        }
        a->time = a->time + dur;
        if (a->time <= 0.0f) {
            a->time = dur;
        }
        a->state = 4;
        return;
    }
    a->state = 2;
}
