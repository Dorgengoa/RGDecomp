/* rgp:protos */
#define RGP_SELF_ResGroupCmdElemNext_42b250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FE8;
extern s16 D_00484000;

s32 ResGroupCmdElemNext_42b250(void)
{
    s32 r;

    r = ResGroupListCurElem_42a5d0();
    D_00483FE8 = 0;
    D_00484000 = (D_00484000 + 1);
    return 1;
}
