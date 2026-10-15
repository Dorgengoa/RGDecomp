#include "types.h"

extern s32 ResGroupListGetElem_42a140(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FEC;
extern s16 D_00484004;

s32 ResGroupListCurElem_42a5a0(void)
{
    s32 t0;
    s16 t1;
    s32 r0;

    t0 = D_00483FEC;
    if (t0 != 0) {
        t1 = D_00484004;
        r0 = ResGroupListGetElem_42a140(t0, t1);
        return r0;
    }
    return 0;
}
