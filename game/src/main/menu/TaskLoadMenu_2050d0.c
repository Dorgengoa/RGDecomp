/* rgp:protos */
#define RGP_SELF_TaskLoadMenu_2050d0 1
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

void TaskLoadMenu_2050d0(void)
{
    MenuIconAllTexLoadPoll_2056b0();
    BattleCmdResLoadPoll_204e90();
    ReturnTrue_204a10();
    MenuBattleEndOpenIfReady_204360();
    MenuBattleIconLoadPoll_204b60();
}
