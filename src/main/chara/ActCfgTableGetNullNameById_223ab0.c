#include "types.h"

/* Lookup, else walk to the parent unless the s16 at +0x12 is the 0x7FFF
   sentinel.  `bne $3,$2` branches PAST the `return arg2`, so the
   fall-through IS the if body. */

extern s32 ActCfgTableFindNullById_222e90(s32, s32, s32);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrGetGlobalTable_234850(s32);
extern s32 ActCfgTableGetNullNameById_223ab0(s32, s32, s32);

s32 ActCfgTableGetNullNameById_223ab0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 r;

    r = ActCfgTableFindNullById_222e90(arg0, arg1, arg2);
    if (r != 0) {
        return *(s32 *)(r + 4);
    }
    if (*(s16 *)(arg0 + 0x12) == 0x7FFF) {
        return arg2;
    }
    r = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (r != 0) {
        return ActCfgTableGetNullNameById_223ab0(r, arg1, arg2);
    }
    return 0;
}
