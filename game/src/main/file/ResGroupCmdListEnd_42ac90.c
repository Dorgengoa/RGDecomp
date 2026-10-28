/* rgp:protos */
#define RGP_SELF_ResGroupCmdListEnd_42ac90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

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
