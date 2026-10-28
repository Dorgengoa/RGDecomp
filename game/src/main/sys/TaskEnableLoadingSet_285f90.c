/* rgp:protos */
#define RGP_SELF_TaskEnableLoadingSet_285f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00460230[];
extern u8 D_00460588[];
extern u8 D_00460598[];
extern u8 D_00460C48[];

void TaskEnableLoadingSet_285f90(void)
{
    TaskSetUpdateTasksPaused_287dd0(1);
    TaskSetEnabled_27c2a0(1, D_00460588);
    TaskSetEnabled_27c2a0(1, D_00460C48);
    TaskSetEnabled_27c2a0(0, D_00460230);
    TaskSetEnabled_27c2a0(1, D_00460598);
}
