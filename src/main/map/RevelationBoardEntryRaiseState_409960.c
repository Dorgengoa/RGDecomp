#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s16 m14;
};

s32 RevelationBoardEntryRaiseState_409960(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s32 rv0;

    t0 = p0->m14;
    rv0 = 1;
    if ((t0 < p1) == 0) {
        rv0 = 0;
    } else {
        p0->m14 = p1;
        rv0 = 1;
    }
    return rv0;
}
