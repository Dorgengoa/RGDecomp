/* rgp:protos */
#define RGP_SELF_HandleEntryRequest_3f2980 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s16 m04;
    s16 m06;
};

s32 HandleEntryRequest_3f2980(s32 p0, struct Obj0 *p1)
{
    s32 rv2;
    s32 t0;
    s32 rv1;
    s16 t1;
    s32 rv0;

    rv2 = rv1;
    if (p1 == 0) {
        rv2 = 0;
    } else {
        t0 = p1->m00;
        rv1 = rv0;
        if (t0 == 0) {
            rv1 = 0;
        } else {
            t1 = p1->m04;
            rv0 = 1;
            if (t1 == 2) {
                rv0 = 0;
            } else {
                p1->m06 = 1;
                p1->m04 = 2;
                rv0 = 1;
            }
            rv1 = rv0;
        }
        rv2 = rv1;
    }
    return rv2;
}
