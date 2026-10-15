#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

s32 WorldSubsysLoad_41ff30(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 rv1;
    s32 t0;
    s32 rv0;

    rv1 = rv0;
    if (p1 == 0) {
        rv1 = 0;
    } else {
        t0 = p0->m00;
        rv0 = 1;
        if (t0 == 0) {
            rv0 = 0;
        } else {
            p0->m04 = p3;
            rv0 = 1;
        }
        rv1 = rv0;
    }
    return rv1;
}
