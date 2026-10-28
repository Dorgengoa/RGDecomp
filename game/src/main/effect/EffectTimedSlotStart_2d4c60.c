/* rgp:protos */
#define RGP_SELF_EffectTimedSlotStart_2d4c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
    s32 m04;
};

s32 EffectTimedSlotStart_2d4c60(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s32 rv1;
    s32 rv0;

    t0 = p0->m02;
    rv1 = rv0;
    if (t0 != 0) {
        rv1 = 0;
    } else {
        rv0 = 1;
        if (p1 < 0) {
            rv0 = 0;
        } else {
            p0->m00 = p1;
            p0->m02 = 1;
            p0->m04 = 0;
            rv0 = 1;
        }
        rv1 = rv0;
    }
    return rv1;
}
