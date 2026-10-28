/* rgp:protos */
#define RGP_SELF_TaskStepDoorGlare_2f6e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskStepDoorGlare_2f6e30(void)
{
    s32 r0;

    r0 = GetCurrentScene_1f5be0();
    GameSceneDoorGlareStep_1cf780(r0);
}
