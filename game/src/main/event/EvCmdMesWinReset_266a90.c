/* rgp:protos */
#define RGP_SELF_EvCmdMesWinReset_266a90 1
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

s32 EvCmdMesWinReset_266a90(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = MesMgrGetSlotWin_266af0(r0);
    if (r1 == 0) {
        return 0;
    }
    r2 = (MesWinReset_276eb0(r1), (s32)0);
    r3 = (MesWinInit_276f20(r1), (s32)0);
    r4 = (MesWinSetMode_276e00(r1, 0), (s32)0);
    return 1;
}
