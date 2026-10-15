#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x32C];
    s32 m32C;
    s32 m330;
    s32 m334;
};

void GuardEffectReset_2d5070(struct Obj0 *p0)
{
    s32 l0;

    l0 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l0 * 0x30) + 0x40) = 0;
        l0 = (l0 + 1);
    } while (l0 < 0x10);
    p0->m330 = 0;
    p0->m334 = 0;
    p0->m32C = 0x3F800000;
}
