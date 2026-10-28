/* rgp:protos */
#define RGP_SELF_InsectCageSoundLoad_38b230 1
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

void InsectCageSoundLoad_38b230(void)
{
    s32 r0;
    s32 r2;

    r0 = GetCurrentScene_1f5be0();
    GameSceneSoundEnvApplyPreset_1d0e30(r0, 0x208, 0, 0);
    r2 = GetCurrentScene_1f5be0();
    GameSceneSoundSlot6RequestLoad_1d0670(r2, 0x384, 0x64);
}
