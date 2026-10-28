/* rgp:protos */
#define RGP_SELF_EvSubNodeRotateTo_252920 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef f32 VEC[4] __attribute__((aligned(16)));

typedef struct {
    u8 pad0[0x10];
    VEC pos;
    s32 frames;
    s32 mode;
    f32 scale;
} Src;

typedef struct {
    u8 pad0[0x44];
    s32 count;
    u8 pad48[0x80 - 0x48];
    VEC cur;
    VEC pad90;
    VEC step;
    VEC padB0;
    VEC vel;
    VEC padD0;
    VEC acc;
    u8 padF0[4];
    s32 n;
} Dst;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1FC;
extern f32 D_0047DB90;
extern f32 D_0047DB94;
extern f32 D_0047DB98;
extern f32 D_0047DB9C;
extern f32 D_0047DBA0;
extern f32 D_0047DBA4;

s32 EvSubNodeRotateTo_252920(Src *a, Dst *b)
{
    VEC v __attribute__((aligned(16)));
    s32 h;
    s32 done;
    f32 f;

    if (a->mode == 0) {
        h = b->n;
    } else {
        h = b->n / 2;
    }
    if (b->count >= a->frames + h) {
        b->count = 0;
        return 0;
    }
    if (b->count <= 0) {
        VecSub_13be40(v, a->pos, b->cur);
        v[0] = WrapAngle_13c050(v[0]);
        v[1] = WrapAngle_13c050(v[1]);
        v[2] = WrapAngle_13c050(v[2]);
        sceVu0DivVector(b->step, v, (f32)a->frames);
        b->step[3] = 1.0f;
        b->n = (f32)a->frames * a->scale;
        sceVu0CopyVector(b->acc, b->step);
        sceVu0DivVector(b->acc, b->acc, (f32)b->n);
        if (a->mode != 2) {
            sceVu0CopyVector(b->vel, b->acc);
        } else {
            sceVu0CopyVector(b->vel, b->step);
        }
    } else {
        done = 0;
        if (b->count < b->n && (a->mode == 0 || a->mode == 1)) {
            VecAdd_13be20(b->vel, b->vel, b->acc);
            VecAdd_13be20(b->cur, b->cur, b->vel);
            f = b->cur[1];
            if (f > D_0047D1FC) {
                b->cur[1] = f - D_0047DB94;
            } else if (f <= D_0047DB90) {
                b->cur[1] = f + D_0047DB94;
            }
            done = 1;
            b->cur[3] = 1.0f;
        }
        if ((a->mode == 2 && b->count >= a->frames - b->n / 2) ||
            (a->mode == 0 && b->count >= a->frames)) {
            VecSub_13be40(b->vel, b->vel, b->acc);
            VecAdd_13be20(b->cur, b->cur, b->vel);
            f = b->cur[1];
            if (f > D_0047D1FC) {
                b->cur[1] = f - D_0047DB9C;
            } else if (f <= D_0047DB98) {
                b->cur[1] = f + D_0047DB9C;
            }
            done = 1;
            b->cur[3] = 1.0f;
        }
        if (done == 0) {
            VecAdd_13be20(b->cur, b->cur, b->step);
            f = b->cur[1];
            if (f > D_0047D1FC) {
                b->cur[1] = f - D_0047DBA4;
            } else if (f <= D_0047DBA0) {
                b->cur[1] = f + D_0047DBA4;
            }
            b->cur[3] = 1.0f;
        }
    }
    b->count++;
    return 1;
}
