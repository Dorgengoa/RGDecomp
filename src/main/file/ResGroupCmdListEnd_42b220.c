#include "types.h"

extern s32 ResGroupListCurElem_42a5d0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FE4;
extern s32 D_00483FE8;
extern s16 D_00484000;

s32 ResGroupCmdListEnd_42b220(void)
{
    s32 r;

    r = ResGroupListCurElem_42a5d0();
    D_00483FE4 = 0;
    D_00484000 = -1;
    D_00483FE8 = 0;
    return 1;
}
