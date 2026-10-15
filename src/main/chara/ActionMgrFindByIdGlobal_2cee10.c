#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern void ActionMgrFindById_233b50(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ActionMgrFindByIdGlobal_2cee10(s32 p0)
{
    s32 r0;

    r0 = GetActionMgr_1fdb50();
    ActionMgrFindById_233b50(r0, p0);
}
