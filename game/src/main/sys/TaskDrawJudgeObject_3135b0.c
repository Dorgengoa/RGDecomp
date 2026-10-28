/* rgp:protos */
#define RGP_SELF_TaskDrawJudgeObject_3135b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482A38;

void TaskDrawJudgeObject_3135b0(int rgp_a0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    HandleRegistryRefDrawAll_3147a0(&D_00482A38, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
}
