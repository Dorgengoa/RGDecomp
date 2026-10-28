/* rgp:protos */
#define RGP_SELF_AmixerTrackSampleKey_170bb0 1
#define RGP_SELF_fcmp 1
#define RGP_SELF_snap 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

typedef struct {
    u8 pad0[0xC];
    f32 start;
    f32 end;
    f32 time;
    f32 step;
    f32 scale;
    f32 mult;
} Key;

typedef struct {
    s32 count;
    Key *keys;
    u8 pad8[8];
    f32 f10;
} Track;

typedef struct {
    Key *key;
    f32 pos;
    f32 val;
} Out;

extern f32 D_0047D24C;
extern f32 D_0047D250;

static inline f32 snap(f32 x0) {
    f32 x = x0;
    f32 r = (f32)(s32)(0.5f + x);
    f32 d = x - r;
    d = (d < 0.0f) ? -d : d;
    if (d <= D_0047D24C) {
        return r;
    }
    return x;
}

static inline s32 fcmp(f32 d0) {
    f32 d = d0;
    if (!(d <= D_0047D24C)) {
        return 1;
    }
    if (d < D_0047D250) {
        return -1;
    }
    return 0;
}

s32 AmixerTrackSampleKey_170bb0(Track *tr, Out *out, f32 t) {
    f32 start;
    f32 count;
    f32 q1;
    f32 time;
    f32 r;
    f32 step;
    f32 end;
    f32 pos;
    f32 len;
    f32 dur;
    f32 frac;
    f32 dur2;
    s32 i;
    Key *k = tr->keys;
    Key *found = 0;

    for (i = 0; i < tr->count; i++, k++) {
        if (!(k->time <= t)) {
            break;
        }
        found = k;
    }
    if (found == 0) {
        return 0;
    }
    start = found->start;
    end = found->end;
    len = 1.0f + (end - start);
    step = found->step;
    q1 = len / step;
    count = snap(q1);
    dur = snap(len / step);
    dur2 = snap(dur * found->mult);
    time = found->time;
    if (fcmp(t - (time + dur2)) >= 0) {
        return 0;
    }
    if (start == end) {
        pos = start;
    } else {
        frac = (t - time) / count;
        frac = frac - (f32)(s32)frac;
        pos = found->start;
        pos = pos + frac * len;
    }
    r = snap(pos);
    out->key = found;
    out->pos = r;
    out->val = tr->f10 * (f32)found->scale;
    return 1;
}
