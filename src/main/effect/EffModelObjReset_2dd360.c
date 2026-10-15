#include "types.h"

extern void EffectInstanceReset_2dd410(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 pad002[0x9BA];
    s32 m9BC;
    s32 m9C0;
    s32 m9C4;
    s16 m9C8;
    s16 m9CA;
};

void EffModelObjReset_2dd360(struct Obj0 *p0)
{
    EffectInstanceReset_2dd410(p0);
    p0->m00 = 1;
    p0->m9C8 = -1;
    p0->m9CA = -1;
    p0->m9BC = -1;
    p0->m9C0 = -1;
    p0->m9C4 = -1;
}
