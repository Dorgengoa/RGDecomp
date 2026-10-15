#include "types.h"

typedef struct E_00157ca0 {
    u8 pad0[0xC];
    s32 fC;
} E_00157ca0;

typedef struct S_00157ca0 {
    u8 pad0[0xC];
    s32 fC;
    u8 pad10[0xC];
    E_00157ca0 *f1C;
    u8 f20[1];
} S_00157ca0;

extern void TexAnimSeqUpdate_163dd0(s32);

void TexGroupUpdateAnim_157ca0(S_00157ca0 *self, s32 i)
{
    E_00157ca0 *p;
    if (i != 0x7FFF) goto g1;
    p = (E_00157ca0 *)self->f20;
    goto out;
g1:
    if (i < 0) goto zero;
    if (i < self->fC) goto ok;
zero:
    p = 0;
    goto out;
ok:
    p = &self->f1C[i];
out:
    if (p == 0) return;
    if (p->fC != 0) {
        TexAnimSeqUpdate_163dd0(p->fC);
    }
}
