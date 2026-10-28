/* rgp:protos */
#define RGP_SELF_IdTableInitMaybe_1a9fd0 1
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
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
};

void IdTableInitMaybe_1a9fd0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 rv2;
    s32 l1;
    s32 t0;

    r0 = ((s32)OperatorNewArray_100900((p1 << 2)));
    p0->m08 = r0;
    rv2 = 0;
    if (r0 != 0) {
        p0->m00 = p1;
        l1 = 0;
        while (l1 < p1) {
            t0 = p0->m08;
            *(s32 *)((u8 *)t0 + (l1 << 2)) = 0;
            l1 = (l1 + 1);
        }
        rv2 = r0;
    }
    p0->m04 = p2;
    p0->m0C = (p2 + p1);
    p0->m10 = 0;
}
