#include "types.h"

extern s32 ResGroupListCurElem_42a570(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FF0;
extern s16 D_00484008;

s32 ResGroupCmdListEnd_42ae20(void)
{
    s32 r;

    r = ResGroupListCurElem_42a570();
    D_00483FF0 = 0;
    D_00484008 = -1;
    return 1;
}
