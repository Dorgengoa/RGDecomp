#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004832C4;
extern s16 D_004832C8;

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 InsectCageGetCollTris_389d70(struct Obj0 *p0)
{
    s32 t0;
    s32 rv0;
    s16 t1;
    s32 t2;

    t0 = D_004832C4;
    rv0 = t2;
    if (t0 == 0) {
        p0->m00 = 0;
        rv0 = 0;
    } else {
        t1 = D_004832C8;
        p0->m00 = t1;
        t2 = D_004832C4;
        rv0 = t2;
    }
    return rv0;
}
