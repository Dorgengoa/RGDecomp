/* rgp:protos */
#define RGP_SELF_ActCfgTableGetInfoNameById_223b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Lookup, else walk to the parent unless the s16 at +0x12 is the 0x7FFF
   sentinel.  `bne $3,$2` branches PAST the `return arg2`, so the
   fall-through IS the if body. */

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 ActCfgTableGetInfoNameById_223b40(s32, s32, s32);

s32 ActCfgTableGetInfoNameById_223b40(s32 arg0, s32 arg1, s32 arg2)
{
    s32 r;

    r = ((s32)ActCfgTableFindNameById_223270(arg0, arg1));
    if (r != 0) {
        return *(s32 *)(r + 4);
    }
    if (*(s16 *)(arg0 + 0x12) == 0x7FFF) {
        return arg2;
    }
    r = ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50()));
    if (r != 0) {
        return ActCfgTableGetInfoNameById_223b40(r, arg1, arg2);
    }
    return 0;
}
