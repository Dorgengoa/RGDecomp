#include "types.h"

extern s32 DListGetHead_42ea60(u8 *);
extern s32 DListGetCountPow2_42ea70(u8 *);
extern s32 DListNodeAdvance_42eb00(s32, s32);
extern s32 IntCompare_42ca30(s32, s32);
extern s32 ActCfgTableGetScopeId_223d00(s32);
extern s32 ActCfgTableGetHeapBlock_223d10(s32);
extern void ActCfgTableFreeActions_223f20(s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern void DListRemove_42e4e0(u8 *, s32);

static inline s32 find(u8 *list, s32 key) {
    s32 found;
    s32 node;
    s32 n;
    s32 cur;
    s32 r;

    node = DListGetHead_42ea60(list);
    if (node == 0) {
        found = 0;
    } else {
        found = 0;
        n = DListGetCountPow2_42ea70(list);
        while (n > 0) {
            n >>= 1;
            cur = DListNodeAdvance_42eb00(node, n);
            if (cur != 0) {
                r = IntCompare_42ca30(key, ActCfgTableGetScopeId_223d00(cur + 0x10));
                if (r == 0) {
                    found = cur;
                    break;
                }
                if (r > 0) {
                    node = cur;
                }
            }
        }
    }
    return found;
}

void ActionMgrRemoveActionTable_233f80(u8 *arg0, s32 arg1) {
    s32 found;
    s32 t;

    found = find(arg0 + 0x10, arg1);
    if (found != 0) {
        if (ActCfgTableGetScopeId_223d00(found + 0x10) == 0x7FFF) {
            *(s32 *)(arg0 + 0x34) = 0;
        }
        ActCfgTableFreeActions_223f20(found + 0x10, *(s32 *)(arg0 + 0x3C));
        t = *(s32 *)(arg0 + 0x3C);
        if (found != 0) {
            if (t != 0) {
                MemStackHeapFree_14dcb0(t, ActCfgTableGetHeapBlock_223d10(found + 0x10));
            }
            DListRemove_42e4e0(arg0 + 0x10, found);
        }
    }
}
