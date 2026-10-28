/* rgp:protos */
#define RGP_SELF_AttackChainEntriesInit_382f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_00382f10 {
    s32 f0;
    u8 pad4[4];
    s16 f8;
    s16 fA;
    s32 fC;
    s32 f10;
    s32 f14;
    f32 f18;
    f32 f1C;
    u8 pad20[0x204];
} E_00382f10;

typedef struct S_00382f10 {
    E_00382f10 *f0;
    s16 f4;
    s16 f6;
} S_00382f10;

s32 AttackChainEntriesInit_382f10(S_00382f10 *self, E_00382f10 *p, s32 n)
{
    E_00382f10 *q;
    s32 j;
    if (p == 0) goto zero;
    if (n > 0) goto ok;
zero:
    return 0;
ok:
    self->f0 = p;
    self->f6 = n;
    q = self->f0;
    for (j = 0; j < self->f6; j++) {
        q->f0 = 0;
        q->fA = 0;
        q->f8 = 0x20;
        q->fC = 0;
        q->f10 = 0;
        q->f14 = 0;
        q->f18 = -1.0f;
        q->f1C = -1.0f;
        q++;
    }
    self->f4 = 0;
    return 1;
}
