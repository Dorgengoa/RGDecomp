/* rgp:protos */
#define RGP_SELF_FUN_00207a80_e1 1
#define RGP_SELF_TaskLoadSound_207a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* ONE symbol, TWO entries: a `j` TAIL CALL into the second entry with a null
   argument, then GameSceneSoundSlotsPoll_1d0a90(GetCurrentScene_1f5be0(p), p). */

/*rgp*/
/*rgp*/

void FUN_00207a80_e1(void *p);

void TaskLoadSound_207a80(void)
{
    FUN_00207a80_e1(0);
}

void FUN_00207a80_e1(void *p)
{
    GameSceneSoundSlotsPoll_1d0a90(GetCurrentScene_1f5be0(), p);
}
