#include "types.h"

struct T3849A0 { s32 f00; s32 f04; };

s32 MenuObjSlotMatchesKey_3849a0(struct T3849A0 *p, s32 k)
{
    s32 r;

    if (p->f00 == k) goto one;
    if (p->f04 != k) goto zero;
one:
    r = 1;
    goto out;
zero:
    r = 0;
out:
    return r;
}
