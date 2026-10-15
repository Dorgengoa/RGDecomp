#include "types.h"

extern s32 GetActionMgr_1fdb50(s32);
extern void ActionMgrScopeTableFindOrAdd_234340(s32, void *);
extern s32 ActionMgrFindTableByScopeId_233c20(s32, s32);
extern void ActCfgTablesReset_23fdd0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481EEC;
extern s32 D_00481EF8;
extern u8 D_004BCE20[];

s32 ActInfoEnd_23f4c0(s32 p0, s32 p1)
{
    s32 r0;
    s32 t0;
    s32 r2;

    if (p1 != 0) {
        return 0;
    }
    r0 = GetActionMgr_1fdb50(p0);
    ActionMgrScopeTableFindOrAdd_234340(r0, D_004BCE20);
    t0 = D_00481EF8;
    r2 = ActionMgrFindTableByScopeId_233c20(r0, t0);
    D_00481EEC = r2;
    ActCfgTablesReset_23fdd0();
    return 1;
}
