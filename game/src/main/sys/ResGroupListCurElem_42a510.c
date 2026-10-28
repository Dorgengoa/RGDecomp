/* rgp:protos */
#define RGP_SELF_ResGroupListCurElem_42a510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FF8;
extern s16 D_00484010;

s32 ResGroupListCurElem_42a510(void)
{
    s32 t0;
    s16 t1;
    s32 r0;

    t0 = D_00483FF8;
    if (t0 != 0) {
        t1 = D_00484010;
        r0 = ((s32)ResGroupListGetElem_429c70(t0, t1));
        return r0;
    }
    return 0;
}
