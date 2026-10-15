#include "types.h"

typedef struct Arg {
    s32 type;
    union {
        f32 f;
        s32 i;
    } v;
} Arg;

extern s32 D_0047E4C0;

s32 AttackChainCfgCmbStrCmd_1f9690(Arg *a, s32 n)
{
    s32 v;

    if (n <= 0) return 0;
    if (a->type == 2) goto arm2;
    if (a->type != 1) { v = 0; goto store; }
    v = a->v.i;
    goto store;
arm2:
    v = (s32)a->v.f;
store:
    D_0047E4C0 = v;
    return 1;
}
