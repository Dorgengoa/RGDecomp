#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrStopSwordTrails_231680(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdStopSwordTrailsAll_2592a0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetActionMgr_1fdb50();
    r1 = ActionMgrStopSwordTrails_231680(r0);
    return 1;
}
