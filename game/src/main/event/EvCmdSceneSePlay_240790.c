/* rgp:protos */
#define RGP_SELF_EvCmdSceneSePlay_240790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdSceneSePlay_240790(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetCurrentScene_1f5be0();
    r1 = ScriptGetInt_2490f0(p0);
    r2 = GameSceneSoundSlot0PlaySe_1d05b0(r0, r1);
    return 1;
}
