/* rgp:protos */
#define RGP_SELF_EventPathRecGetPath_2e40e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { u8 b[16]; } E;

typedef struct S {
    u8 pad0[20];
    E *p;
    u8 pad1[2];
    s16 n;
} S;

E * EventPathRecGetPath_2e40e0(S *self, s32 i)
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
