#include "types.h"
typedef unsigned __int128 u128;

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Emt {
    u8 pad0[4];
    s32 idx;
    u8 pad8[8];
    s32 m10;
    s32 m14;
    u8 pad18[8];
    V4 m20;
    f32 m30[4];
    s32 m40;
    s32 m44;
    u8 pad48[8];
    V4 m50;
    f32 m60[4];
    f32 m70;
} Emt;
typedef struct Sys { u8 pad0[4]; u8 rng[0xB0]; V4 *vecs; } Sys;

extern void CopyQword_18bb60(V4 *, V4 *);
extern f32 RandGaussian_197d70(void *);
extern f32 RandFloat_1980f0(void *);
extern void VecAddThunk_13be20(V4 *, V4 *, V4 *);
extern f32 D_0047D420;
extern f32 D_0047D428;

void EffAttachInitRandomized_197a80(Emt *e, Sys *sys)
{
    V4 t0;
    V4 t1;
    V4 *p;
    s32 i;

    p = &sys->vecs[e->idx];
    if (e->m10 <= 0) {
        CopyQword_18bb60(p, &e->m20);
    } else {
        *(u128 *)&t0 = 0;
        if (e->m10 == 1) {
            for (i = 0; i < 4; i++) {
                ((f32 *)&t0)[i] = e->m30[i] * (2.0f * (RandFloat_1980f0(sys->rng) - 0.5f));
            }
        } else if (e->m10 == 2) {
            for (i = 0; i < 4; i++) {
                ((f32 *)&t0)[i] = e->m30[i] * (D_0047D420 * RandGaussian_197d70(sys->rng));
            }
        }
        switch (e->m14) {
        case 1:
            t0.y = t0.x;
            t0.z = t0.x;
            break;
        case 2:
            t0.y = t0.x;
            break;
        case 3:
            t0.z = t0.x;
            break;
        case 4:
            t0.z = t0.y;
            break;
        case 0:
            break;
        }
        VecAddThunk_13be20(p, &e->m20, &t0);
    }
    if (e->m40 <= 0) {
        CopyQword_18bb60(p + 1, &e->m50);
    } else {
        *(u128 *)&t1 = 0;
        if (e->m40 == 1) {
            for (i = 0; i < 4; i++) {
                ((f32 *)&t1)[i] = e->m60[i] * (2.0f * (RandFloat_1980f0(sys->rng) - 0.5f));
            }
        } else if (e->m40 == 2) {
            for (i = 0; i < 4; i++) {
                ((f32 *)&t1)[i] = e->m60[i] * (D_0047D420 * RandGaussian_197d70(sys->rng));
            }
        }
        switch (e->m44) {
        case 1:
            t1.y = t1.x;
            t1.z = t1.x;
            break;
        case 2:
            t1.y = t1.x;
            break;
        case 3:
            t1.z = t1.x;
            break;
        case 4:
            t1.z = t1.y;
            break;
        case 0:
            break;
        }
        VecAddThunk_13be20(p + 1, &e->m50, &t1);
    }
    p[1].y = p[1].y + D_0047D428 * e->m70;
}
