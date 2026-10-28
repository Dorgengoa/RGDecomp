/* rgp:protos */
#define RGP_SELF_EffectRequestLoadChrChecked_2e1bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T13 { s16 f0; u8 pad002[2]; s32 f4; s32 f8; s32 fC; };
struct T13v { s16 f0; u8 pad002[2]; s32 f4; volatile s32 f8; s32 fC; };

extern void EffectRequestLoadChr_2dfa40(struct T13 *out, u8 *p, s32 a2, s32 a3, s32 a4, s32 g, s32 h, s32 a7);

void EffectRequestLoadChrChecked_2e1bf0(struct T13 *o, u8 *p, s32 a2, s32 a3, s32 a4, s32 g, s32 h, s32 a7)
{
    struct T13v u __attribute__((aligned(16)));
    struct T13 t __attribute__((aligned(16)));
    s32 v8;
    s32 v4;
    s32 vC;
    s16 v0;

    if (g == 0) {
        o->f0 = 2;
        o->f4 = -1;
        o->f8 = 0;
        o->fC = u.fC;
        return;
    }
    if (h == 0) {
        o->f0 = 2;
        o->f4 = -1;
        o->f8 = 0;
        o->fC = u.fC;
        return;
    }
    EffectRequestLoadChr_2dfa40(&t, p + 0x1674, a2, a3, a4, g, h, a7);
    v4 = t.f4;
    vC = t.fC;
    v0 = t.f0;
    o->f0 = v0;
    o->f4 = v4;
    v8 = t.f8;
    u.f8 = v8;
    o->f8 = v8;
    o->fC = vC;
}
