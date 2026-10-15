#include "types.h"

extern s32 ResGroupListCurElem_42a510(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FFC;
extern s16 D_00484010;

s32 ResGroupCmdElemNext_42a8c0(void)
{
    s32 r;

    r = ResGroupListCurElem_42a510();
    D_00483FFC = 0;
    D_00484010 = (D_00484010 + 1);
    return 1;
}
