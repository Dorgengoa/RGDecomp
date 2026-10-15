#include "types.h"

extern s32 GetMesMgr_277e90(void);
extern void MesMgrUpdateAll_277ac0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskStepMessage_27a900(void)
{
    s32 r0;

    r0 = GetMesMgr_277e90();
    MesMgrUpdateAll_277ac0(r0);
}
