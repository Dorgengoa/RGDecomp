/* rgp:protos */
#define RGP_SELF_AiCmdIsInBattle_2c7be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AiCmdIsInBattle_2c7be0(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 r2;

    rv3 = 1;
    if (p1 != 1) {
        rv3 = 0;
    } else {
        r0 = ((unsigned char)IsInBattle_288420());
        if (r0 != 0) {
            r1 = (ScriptSlotStoreIntRef_2cc900(p0, 1), (s32)0);
        } else {
            r2 = (ScriptSlotStoreIntRef_2cc900(p0, 0), (s32)0);
        }
        rv3 = 1;
    }
    return rv3;
}
