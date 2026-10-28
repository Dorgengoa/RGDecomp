/* rgp:protos */
#define RGP_SELF_EvCmdLoaderIsIdle_248a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdLoaderIsIdle_248a70(s32 p0)
{
    s32 r0;
    s32 r2;
    s32 r3;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    LoaderTick_1ccc30(r0);
    r2 = LoaderIsIdle_1cd5b0(r0);
    r3 = (ScriptSetRefInt_249030(p0, (r2 & 0xFF)), (s32)0);
    return 1;
}
