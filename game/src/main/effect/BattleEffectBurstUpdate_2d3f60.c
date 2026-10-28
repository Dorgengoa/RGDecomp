/* rgp:protos */
#define RGP_SELF_BattleEffectBurstUpdate_2d3f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec __attribute__((aligned(16)));

typedef struct {
    Vec pos;
    Vec vel;
    f32 speed;
    f32 t;
    f32 pad28;
    f32 pad2c;
    f32 alpha;
    s8 state;
    s32 type;
} Part;

typedef struct {
    s32 active;
    u8 pad4[0x1C];
    Part parts[64];
} Mgr;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5D0;
extern f32 D_0047D7A4;
extern f32 D_0047DA74;
extern f32 D_0047DAA0;
extern f32 D_0047DAC0;
extern f32 D_0047DAC4;
extern f32 D_0047DAC8;

void BattleEffectBurstUpdate_2d3f60(Mgr *mgr) {
    Vec tmp __attribute__((aligned(16)));
    f32 rate;
    f32 d0;
    f32 d2;
    f32 d1;
    f32 d3;
    f32 d4;
    f32 d6;
    f32 d5;

    s32 live;
    Part *p;
    s32 i;

    rate = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    live = 0;
    p = mgr->parts;
    d0 = D_0047DAC0 * rate;
    d2 = D_0047DAA0 * rate;
    d1 = D_0047D5D0 * rate;
    d3 = D_0047DA74 * rate;
    d4 = D_0047DAC4 * rate;
    d6 = D_0047D7A4 * rate;
    d5 = D_0047DAC8 * rate;
    for (i = 0; i < 64; i++) {
        if (p->state == 0) {
            p++;
            continue;
        }
        live++;
        if (p->type == 0) {
            if (p->t < 1.0f) {
                p->t += d0;
            } else {
                p->state = 2;
                p->t += d0;
            }
            if (p->state == 1) {
                p->alpha += d2;
            }
            if (p->state == 2) {
                p->alpha -= d2;
                if (p->alpha <= 0.0f) {
                    p->state = 0;
                }
            }
        }
        if (p->type == 1 && p->state == 1) {
            p->t += d0;
            p->alpha -= d1;
            if (p->alpha <= 0.0f) {
                p->state = 0;
            }
        }
        if (p->type == 2 && p->state == 1) {
            p->t += d2;
            p->alpha -= d3;
            if (p->alpha <= 0.0f) {
                p->state = 0;
            }
        }
        if (p->type == 3) {
            if (p->state == 1) {
                p->t += d2;
                if (!(p->t < 1.0f)) {
                    p->state = 2;
                }
            }
            if (p->state == 2) {
                p->alpha -= d4;
                if (p->alpha <= 0.0f) {
                    p->state = 0;
                }
            }
            VecScale_13be00(&tmp, &p->vel, p->speed);
            VecAdd_13be20(&p->pos, &p->pos, &tmp);
            p->pos.w = 1.0f;
        }
        if (p->type == 4 && p->state == 1) {
            p->t += d6;
            p->alpha -= d5;
            if (p->alpha <= 0.0f) {
                p->state = 0;
            }
        }
        p++;
    }
    if (live == 0) {
        mgr->active = 0;
    }
}
