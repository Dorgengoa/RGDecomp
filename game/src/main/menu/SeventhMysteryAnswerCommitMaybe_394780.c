/* rgp:protos */
#define RGP_SELF_SeventhMysteryAnswerCommitMaybe_394780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483470;
extern u8 D_004E9570[];

s32 SeventhMysteryAnswerCommitMaybe_394780(s32 p0, s32 p1)
{
    s32 r1;

    if (p1 != 0) {
        UiEntryListSelectByTag_28ea90(D_004E9570, 0x7533, 0);
    }
    r1 = StateMachineSetState_28ede0(&D_00483470, 0x7535, 0);
    return 1;
}
