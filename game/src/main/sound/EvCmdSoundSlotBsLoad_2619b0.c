/* rgp:protos */
#define RGP_SELF_EvCmdSoundSlotBsLoad_2619b0 1
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

extern s32 D_00481F78;

s32 EvCmdSoundSlotBsLoad_2619b0(s32 p0)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 t1;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    t0 = D_00481F78;
    r1 = GameSceneSoundSlot1HasLoadedId_1d0810(t0, r0);
    if (r1 != 0) {
        t1 = D_00481F78;
        r2 = GameSceneSoundSlot1RequestLoad_1d06b0(t1, r0);
        return (r2 & 0xFF);
    }
    return 0;
}
