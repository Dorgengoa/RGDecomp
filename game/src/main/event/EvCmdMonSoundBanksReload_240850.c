/* rgp:protos */
#define RGP_SELF_EvCmdMonSoundBanksReload_240850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMonSoundBanksReload_240850(void)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)GetCharaResMgr_1fdb60());
    r1 = (MonSoundBanksReload_1efd50(r0), (s32)0);
    return 1;
}
