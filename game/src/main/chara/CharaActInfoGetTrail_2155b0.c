/* rgp:protos */
#define RGP_SELF_CharaActInfoGetTrail_2155b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { u8 b[184]; } E;

typedef struct S {
    u8 pad0[4];
    E *p;
    s32 n;
} S;

E * CharaActInfoGetTrail_2155b0(S *self, s32 i)
{
    E *p = self->p;
    if (p == 0) goto zero;
    if (i < 0) goto zero;
    if (self->n > i) goto ok;
zero:
    return 0;
ok:
    return &p[i];
}
