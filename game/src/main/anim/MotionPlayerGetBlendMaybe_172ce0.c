/* rgp:protos */
#define RGP_SELF_MotionPlayerGetBlendMaybe_172ce0 1
#define RGP_SELF_SeqFrame 1
#define RGP_SELF_SeqValid 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Frame { u8 pad0[0x24]; f32 t0; f32 t1; f32 rate; } Frame;
typedef struct Seq { s32 w0; s32 n; Frame *frames; } Seq;
typedef struct Clip { u8 pad0[0x10]; Seq seq; } Clip;
typedef struct Anim {
    Clip *req; s32 reqFrame; s32 reqFlags; Clip *cur; Clip *next; s32 frame; f32 time; f32 prev;
    s32 flags; s32 state; s32 blending; s32 nextFrame; f32 nextTime; f32 blend;
} Anim;
typedef struct State { s32 blending; f32 weight; Seq *cur; f32 curTime; Seq *next; f32 nextTime; } State;

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

void MotionPlayerGetBlendMaybe_172ce0(Anim *a, State *st)
{
    Frame *fr;
    Seq *s;
    f32 t;

    st->blending = a->blending;
    st->weight = 1.0f - (1.0f - a->blend) * (1.0f - a->blend);
    st->cur = 0;
    st->next = 0;
    if (a->cur != 0) {
        s = &a->cur->seq;
        st->cur = s;
        t = a->time;
        fr = SeqFrame(a->frame, s);
        t = fr != 0 ? t + fr->t0 : t;
        st->curTime = t;
    }
    if (a->next != 0) {
        s = &a->next->seq;
        st->next = s;
        t = a->nextTime;
        fr = SeqFrame(a->nextFrame, s);
        t = fr != 0 ? t + fr->t0 : t;
        st->nextTime = t;
    }
}
