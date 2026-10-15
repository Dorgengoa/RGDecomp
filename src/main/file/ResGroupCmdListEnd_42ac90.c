#include "types.h"

extern s32 ResGroupListCurElem_42a540(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FF4;
extern s16 D_0048400C;

s32 ResGroupCmdListEnd_42ac90(void)
{
    s32 r;

    r = ResGroupListCurElem_42a540();
    D_00483FF4 = 0;
    D_0048400C = -1;
    return 1;
}
