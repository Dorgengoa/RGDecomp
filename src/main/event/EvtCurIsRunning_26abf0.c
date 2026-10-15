#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00482040;

struct Obj0;

struct Obj0 {
    u8 pad000[0x46C];
    s32 m46C;
};

s32 EvtCurIsRunning_26abf0(void)
{
    struct Obj0 * t0;
    s32 rv0;
    s32 t1;

    t0 = D_00482040;
    rv0 = t1;
    if (t0 == 0) {
        rv0 = 0;
    } else {
        t1 = D_00482040->m46C;
        rv0 = t1;
    }
    return rv0;
}
