/* rgp:protos */
#define RGP_SELF_RecStackHeapSlotRelease_201ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

void RecStackHeapSlotRelease_201ea0(s32 p0, struct Obj0 *p1)
{
    s32 t0;
    s32 r0;
    s32 t1;

    if (p1 != 0) {
        t0 = p1->m00;
        if (t0 >= 0) {
            r0 = GetCurrentScene_1f5be0();
            t1 = p1->m00;
            RecStackPop_1c4140(r0, t1);
        }
        p1->m00 = -1;
    }
    if (p0 != 0) {
        MemStackHeapReinit_14de90(p0);
        return;
    }
}
