/* rgp:protos */
#define RGP_SELF_MesWinLoadText_273c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinLoadText_273c70(s32 p0, s32 p1, s32 p2)
{
    if (p1 != 0) {
        MesWinClearChars_2744b0(p0);
        MesWinSetFlush_2775f0(p0, 0);
        MesWinLayoutText_274e70(p0, p1);
        if (p2 != 0) {
            MesWinPushChar_2743c0(p0, 0xFF01);
        }
        MesWinCountPageLines_2726d0(p0);
    }
}
