#include "types.h"

extern s32 HatenaMarkListReset_345060(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
};

struct Obj0 *HatenaMarkListCtor_3450d0(struct Obj0 *p0)
{
    s32 r0;

    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    r0 = HatenaMarkListReset_345060(p0);
    return p0;
}
