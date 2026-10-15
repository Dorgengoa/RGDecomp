#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004810A4;

struct Obj0;

struct Obj0 {
    u8 pad000[0xF20];
    s32 mF20;
};

s32 GetDrawCtxCamera_15de60(void)
{
    struct Obj0 * t0;
    s32 t1;

    t0 = D_004810A4;
    if (t0 != 0) {
        t1 = D_004810A4->mF20;
        return t1;
    }
    return 0;
}
