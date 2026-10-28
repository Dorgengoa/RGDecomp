/* rgp:protos */
#define RGP_SELF_EvCmdCharaPcResQueue_243f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdCharaPcResQueue_243f90(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_2490f0(p0);
    r1 = (CharaPcResNamesQueue_1f17d0(r0), (s32)0);
    return 1;
}
