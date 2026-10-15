#include "types.h"

struct T40E400 { u8 pad000[0x2]; s8 f02; };

s32 ItemDefIsWeapon_40e400(struct T40E400 *p)
{
    s8 v;
    s32 r;

    v = p->f02;
    if (v == 0) goto one;
    if (v != 1) goto zero;
one:
    r = 1;
    goto out;
zero:
    r = 0;
out:
    return r;
}
