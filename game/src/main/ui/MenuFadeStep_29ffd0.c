/* rgp:protos */
#define RGP_SELF_MenuFadeStep_29ffd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S29F {
    u8  pad000[0x48];
    f32 f48;
    f32 f4C;
} S29F;

s32 MenuFadeStep_29ffd0(S29F *p, f32 v)
{
    f32 t;
    s32 r;

    t = (0.0f + p->f4C) + p->f48 * v;
    p->f4C = t;
    if (t > 0.0f) {
        if (t < 1.0f) goto zero;
    }
    p->f48 = 0.0f;
    return 1;
zero:
    return 0;
}
