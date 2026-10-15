#pragma opt_propagation off
#pragma opt_pulloutconstants off
#include "types.h"

typedef struct Ent {
    u8 type;
    u8 pad1[3];
    s32 mode;
    f32 base;
    f32 range;
    u16 lo;
    u16 hi;
} Ent;

typedef struct Res {
    s32 a;
    f32 v;
    s32 idx;
    s32 rem;
} Res;

typedef struct Tbl {
    u8 pad0[4];
    s32 slot;
    u8 pad8[0x15];
    u8 on;
    u8 pad1E[2];
    s32 n;
    Ent **ents;
} Tbl;

typedef struct Ctx {
    u8 pad0[4];
    s32 seed;
    u8 pad8[0xAC];
    Res *res;
} Ctx;

f32 RandGaussian_197d70(s32 *);
f32 RandFloat_1980f0(s32 *);
extern f32 D_0047D420;

static inline s32 weight(Ent *e) {
    switch (e->type) {
    case 1:
        if (e->lo > e->hi) {
            return e->lo - e->hi + 1;
        }
        return e->hi - e->lo + 1;
    case 2:
        return e->lo;
    }
    return 0;
}

void EffTexAnimeParamRandomize_198670(Tbl *tbl, Ctx *ctx) {
    Ent *e;
    s32 w;
    s32 total;
    f32 r;
    f32 v;
    s32 pick;
    Res *res;
    s32 j;
    s32 i;

    res = &ctx->res[tbl->slot];
    res->a = 0;
    res->v = 1.0f;
    res->idx = 0;
    res->rem = 0;
    if (tbl->on == 0) {
        return;
    }
    total = 0;
    for (i = 0; i < tbl->n; i++) {
        total += weight(tbl->ents[i]);
    }
    {
        f32 fn;
        f32 k;
        f32 r2;
        ctx->seed = ctx->seed * 0x5D588B65 + 1;
        fn = (f32)total;
        k = 2.3283064e-10f;
        r2 = fn * (k * (f32)(u32)ctx->seed);
        if (r2 >= (f32)(total - 1)) {
            pick = total - 1;
        } else {
            pick = (s32)r2;
        }
    }
    for (j = 0; j < tbl->n; j++) {
        e = tbl->ents[j];
        w = weight(e);
        if (*(u8 *)e == 3) {
            if (e->mode <= 0) {
                v = e->base;
            } else if (e->mode == 1) {
                v = e->base + e->range * (2.0f * (RandFloat_1980f0(&ctx->seed) - 0.5f));
            } else if (e->mode == 2) {
                v = e->base + D_0047D420 * (e->range * RandGaussian_197d70(&ctx->seed));
            } else {
                v = e->base;
            }
            res->v = v;
        }
        if (w > 0 && pick < w) {
            res->idx = j;
            res->rem = pick;
            return;
        }
        pick -= w;
    }
}
