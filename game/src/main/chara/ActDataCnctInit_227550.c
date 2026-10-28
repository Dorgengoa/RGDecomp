/* rgp:protos */
#define RGP_SELF_ActDataCnctInit_227550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; f32 b; } T_00227550;

void ActDataCnctInit_227550(T_00227550 *p, s32 s, f32 v)
{
    p->a = 0;
    p->b = 1.0f;
    if (s == 0) return;
    p->a = s;
    if (0.0f < v && v <= 1.0f) {
        p->b = v;
    }
}
