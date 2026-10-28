/* rgp:protos */
#define RGP_SELF_TexGroupClearAnim_157d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_00157d10 {
    u8 pad0[0xC];
    s32 fC;
} E_00157d10;

typedef struct S_00157d10 {
    u8 pad0[0xC];
    s32 fC;
    u8 pad10[0xC];
    E_00157d10 *f1C;
    u8 f20[1];
} S_00157d10;

void TexGroupClearAnim_157d10(S_00157d10 *self, s32 i)
{
    E_00157d10 *p;
    if (i != 0x7FFF) goto g1;
    p = (E_00157d10 *)self->f20;
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
    p->fC = 0;
}
