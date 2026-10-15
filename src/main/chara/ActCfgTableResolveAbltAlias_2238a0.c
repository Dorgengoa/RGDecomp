/* MATCH (s41m). Stale pre-match note follows -- PARKED s17b: 5x-unrolled recursive-descent helper. VERY close: 133 words,
   length 0x214 vs retail 0x210 (1 word over). Retail's *first* early-return
   block (`if (ActCfgTableFindAbltByName_222870(...)) return ActInfoAbltResolveAlias_22eb80(...)`) jumps to a label
   positioned AFTER the epilogue's `ld $31` (it restores $31 itself inline in
   a branch delay slot and skips straight to the `lq`s), while every other
   occurrence of the same shape later in the function jumps to the normal
   epilogue entry (which still has to `ld $31`). Only the outermost/first
   occurrence gets this tail-merge; a later session should try restructuring
   just the outermost if/return (e.g. without an explicit early `return`, or
   with the recursion-continuation written differently) to see if that shifts
   which occurrence mwcc merges. */
#include "types.h"

typedef struct {
    u8 pad12[0x12];
    s16 unk12;
} S1;

extern void * ActCfgTableFindAbltByName_222870(void *, s32);
extern s32 ActCfgTableGetScopeId_223d00(void *);
extern s32 ActInfoAbltResolveAlias_22eb80(void *, s32);
extern void *ActionMgrGetGlobalTable_234850(s32);
extern s32 GetActionMgr_1fdb50(void);

s32 ActCfgTableResolveAbltAlias_2238a0(S1 *arg0, s32 arg1, s32 arg2)
{
    void * r;
    S1 *next;

    r = ActCfgTableFindAbltByName_222870(arg0, arg1);
    if (r != 0) {
        return ActInfoAbltResolveAlias_22eb80(r, arg2);
    }
    if (arg0->unk12 == 0x7FFF) {
        return arg2;
    }
    next = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (next == NULL) {
        return 0;
    }

    r = ActCfgTableFindAbltByName_222870(next, arg1);
    if (r != 0) {
        return ActInfoAbltResolveAlias_22eb80(r, arg2);
    }
    if (next->unk12 == 0x7FFF) {
        return arg2;
    }
    next = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (next == NULL) {
        return 0;
    }

    r = ActCfgTableFindAbltByName_222870(next, arg1);
    if (r != 0) {
        return ActInfoAbltResolveAlias_22eb80(r, arg2);
    }
    if (next->unk12 == 0x7FFF) {
        return arg2;
    }
    next = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (next == NULL) {
        return 0;
    }

    r = ActCfgTableFindAbltByName_222870(next, arg1);
    if (r != 0) {
        return ActInfoAbltResolveAlias_22eb80(r, arg2);
    }
    if (next->unk12 == 0x7FFF) {
        return arg2;
    }
    next = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (next == NULL) {
        return 0;
    }

    r = ActCfgTableFindAbltByName_222870(next, arg1);
    if (r != 0) {
        return ActInfoAbltResolveAlias_22eb80(r, arg2);
    }
    if (ActCfgTableGetScopeId_223d00(next) == 0x7FFF) {
        return arg2;
    }
    next = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (next == NULL) {
        return 0;
    }
    return ActCfgTableResolveAbltAlias_2238a0(next, arg1, arg2);
    return 0;
}
