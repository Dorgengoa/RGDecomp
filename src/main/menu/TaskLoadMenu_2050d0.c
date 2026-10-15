#include "types.h"

extern void MenuIconAllTexLoadPoll_2056b0(void);
extern void BattleCmdResLoadPoll_204e90(void);
extern void ReturnTrue_204a10(void);
extern void MenuBattleEndOpenIfReady_204360(void);
extern void MenuBattleIconLoadPoll_204b60(void);

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
