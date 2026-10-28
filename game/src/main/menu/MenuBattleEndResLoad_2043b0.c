/* rgp:protos */
#define RGP_SELF_MenuBattleEndResLoad_2043b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004BBB54;

void MenuBattleEndResLoad_2043b0(s32 p0)
{
    s32 r0;

    r0 = MenuBattleEndStackInit_2065e0();
    *(u8 *)&D_004BBB54 = p0;
    MenuBattleEndResRequest_2045e0();
}
