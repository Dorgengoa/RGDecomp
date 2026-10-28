/* rgp:protos */
#define RGP_SELF_TaskStatePopAll_27c250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482278;
extern u8 D_004D7FA0[];

void TaskStatePopAll_27c250(void)
{
    TaskTableStatePop_1f5430(D_004D7FA0);
    D_00482278 = (D_00482278 + -1);
}
