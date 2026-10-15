#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_00479FB0[];
extern u8 D_0047A7D0[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
    s16 m08;
};

struct Obj0 *ZonePhaseSetQueryCtor_414aa0(struct Obj0 *p0)
{
    p0->m00 = D_00472250;
    p0->m00 = D_00479FB0;
    p0->m00 = D_0047A7D0;
    p0->m04 = 0;
    p0->m08 = -1;
    return p0;
}
