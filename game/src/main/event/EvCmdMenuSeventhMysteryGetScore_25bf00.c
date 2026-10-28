/* rgp:protos */
#define RGP_SELF_EvCmdMenuSeventhMysteryGetScore_25bf00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMenuSeventhMysteryGetScore_25bf00(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = SeventhMysteryGetScore_3956c0();
    r1 = (ScriptSetRefInt_26a1e0(p0, r0), (s32)0);
    return 1;
}
