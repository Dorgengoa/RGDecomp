#include "types.h"

extern s32 ResGroupListGetElem_42a330(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FE4;
extern s16 D_00484000;

s32 ResGroupListCurElem_42a5d0(void)
{
    s32 t0;
    s16 t1;
    s32 r0;

    t0 = D_00483FE4;
    if (t0 != 0) {
        t1 = D_00484000;
        r0 = ResGroupListGetElem_42a330(t0, t1);
        return r0;
    }
    return 0;
}
