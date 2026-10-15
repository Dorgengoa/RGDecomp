#include "types.h"

extern s32 GetCharaResMgr_1fdb60(void);
extern s32 MonSoundBanksReload_1efd50(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMonSoundBanksReload_25acf0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetCharaResMgr_1fdb60();
    r1 = MonSoundBanksReload_1efd50(r0);
    return 1;
}
