/* rgp:protos */
#define RGP_SELF_StatusEntryClearIfActive_3a14d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 m00;
};

s32 StatusEntryClearIfActive_3a14d0(s32 p0, struct Obj0 *p1)
{
    s32 rv2;
    u8 t0;
    s32 rv1;
    s32 r0;

    rv2 = rv1;
    if (p1 == 0) {
        rv2 = 0;
    } else {
        t0 = p1->m00;
        rv1 = 1;
        if (t0 == 0) {
            rv1 = 0;
        } else {
            r0 = StatusEntryClear_3a5f10(p1, 1);
            rv1 = 1;
        }
        rv2 = rv1;
    }
    return rv2;
}
