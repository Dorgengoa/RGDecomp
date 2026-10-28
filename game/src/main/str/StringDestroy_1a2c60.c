/* rgp:protos */
#define RGP_SELF_StringDestroy_1a2c60 1
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
    u8 pad004[0x4];
    s32 m08;
};

void StringDestroy_1a2c60(s32 p0, struct Obj0 *p1)
{
    s32 t0;
    s32 t1;

    if (p1 != 0) {
        if (p1 == 0) {
            return;
        }
        t0 = p1->m00;
        if ((t0 & 1) != 0) {
            t1 = p1->m08;
            OperatorDelete_100840(t1);
        }
        return;
    }
}
