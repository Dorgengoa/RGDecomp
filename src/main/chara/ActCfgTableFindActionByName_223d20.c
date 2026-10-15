#include "types.h"

extern s32 GetActionMgr_1fdb50();
extern void *SortedNodeGetData_21ff00(s32);
extern s32 SortedListFindByName_21ff10(void *, s8 *);
extern void *SortedListFindDataByName_21ffd0(void *, s8 *);
extern s32 ActCfgTableGetScopeId_223d00(void *);
extern void *ActionMgrGetGlobalTable_234850(s32);
extern s32 StrCmpNullSafe_42ca40(s8 *, s32);
extern void *DListGetHead_42ea60(void *);
extern s32 DListGetCountPow2_42ea70(void *);
extern void *DListNodeAdvance_42eb00(void *, s32);

typedef struct O223d20 {
    u8 pad0[0x12];
    s16 m12;
    u8 pad14[0x78];
    u8 m8C[4];
} O223d20;

void *ActCfgTableFindActionByName_223d20(O223d20 *arg0, s8 *arg1);

static inline void *lookup3(void *q, s8 *name)
{
    void *r;

    if (ActCfgTableGetScopeId_223d00(q) != 0x7FFF && name != NULL && *name == '#') {
        r = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (r == NULL) {
            return NULL;
        }
        return ActCfgTableFindActionByName_223d20(r, name);
    }
    return SortedListFindDataByName_21ffd0((u8 *)q + 0x8C, name);
}

static inline void *findLocal(void *tbl, s8 *name)
{
    s32 r;

    r = SortedListFindByName_21ff10(tbl, name);
    if (r != 0) {
        return SortedNodeGetData_21ff00(r);
    }
    return NULL;
}

static inline void *lookup2(void *p, s8 *name)
{
    void *q;
    s32 r;

    if (*(s16 *)((u8 *)p + 0x12) != 0x7FFF && name != NULL && *name == '#') {
        q = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (q == NULL) {
            return NULL;
        }
        return lookup3(q, name);
    }
    return findLocal((u8 *)p + 0x8C, name);
}

void *ActCfgTableFindActionByName_223d20(O223d20 *arg0, s8 *arg1)
{
    void *p;
    void *hit;
    void *lo;
    s32 n;
    void *e;
    s32 c;

    if (arg0->m12 != 0x7FFF && arg1 != NULL && *arg1 == '#') {
        p = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (p == NULL) {
            return NULL;
        }
        return lookup2(p, arg1);
    }
    if ((lo = DListGetHead_42ea60(arg0->m8C)) == NULL) {
        hit = NULL;
    } else {
        hit = NULL;
        n = DListGetCountPow2_42ea70(arg0->m8C);
        while (n > 0) {
            n >>= 1;
            e = DListNodeAdvance_42eb00(lo, n);
            if (e == NULL) {
                continue;
            }
            c = StrCmpNullSafe_42ca40(arg1, *(s32 *)((u8 *)e + 0x38));
            if (c == 0) {
                hit = e;
                break;
            }
            if (c > 0) {
                lo = e;
            }
        }
    }
    if (hit == NULL) {
        return NULL;
    }
    return (u8 *)hit + 0x10;
}
