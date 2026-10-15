#include "types.h"

extern s32 GetGameData_1fede0(void);
extern void GameDataRefreshWorld_3e6580(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GameDataRefreshWorldFwd_1fec10(void)
{
    s32 r0;

    r0 = GetGameData_1fede0();
    GameDataRefreshWorld_3e6580(r0);
}
