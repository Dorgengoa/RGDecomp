/* rgp:protos */
#define RGP_SELF_UiGlowSpriteListUpdate_33bb30 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): m2c's draft has a `(bitwise s16)` cast
 * m2c couldn't resolve and calls RandRangeFloat_1ca5d0 (declared 6 params) with only
 * 1-2 explicit arguments at several call sites -- signs of dropped/garbage
 * register args needing a raw-asm read. Deferred to preserve lane
 * throughput. See asm/matchings/main/UiGlowSpriteListUpdate_33bb30.s. */
/* s49m: MATCH */
#include "types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 state;
    s16 pad6;
    f32 m8;
    f32 alpha;
    f32 fade;
    f32 m14;
} Particle;

typedef struct {
    u8 pad0[8];
    s16 active;
    s16 x;
    s16 y;
    s16 count;
    Particle p[32];
} Effect;

extern f32 D_0047D1FC __attribute__((section(".sdata")));
extern f32 D_0047D5D0 __attribute__((section(".sdata")));
extern f32 D_0047DA44 __attribute__((section(".sdata")));
extern f32 D_0047DA8C __attribute__((section(".sdata")));
/*rgp*/

void UiGlowSpriteListUpdate_33bb30(Effect *e, s16 x, s16 y)
{
    s16 live;
    Particle *p;
    s32 i;

    if (e->active == 0) {
        return;
    }
    e->x = x;
    e->y = y;
    live = 0;
    p = e->p;
    for (i = 0; i < e->count; i++, p++) {
        if (p->state <= 0) {
            continue;
        }
        live++;
        p->y -= 3;
        p->m8 += D_0047DA8C;
        if (p->m8 > D_0047D1FC) {
            p->m8 = 0.0f;
        }
        if (p->state == 1) {
            p->alpha += D_0047DA44;
            if (p->alpha > 1.0f) {
                p->alpha = 1.0f;
                p->state++;
            }
        }
        if (p->state == 2) {
            p->alpha -= p->fade;
            if (p->alpha < 0.0f) {
                p->state = 0;
                live--;
            }
        }
    }
    if (e->count < 0x20) {
        p = &e->p[e->count];
        p->x = RandRangeFloat_1ca5d0(100.0f);
        p->y = (s16)RandRangeFloat_1ca5d0(10.0f) + 0x1E;
        p->m8 = RandRangeFloat_1ca5d0(*(f32 *)&D_0047D1FC);
        p->alpha = 0.0f;
        p->fade = 0.125f;
        p->m14 = D_0047D5D0 + RandRangeFloat_1ca5d0(1.5f);
        p->state = 1;
        live++;
        e->count++;
    }
    if (live <= 0) {
        e->active = 0;
    }
}
