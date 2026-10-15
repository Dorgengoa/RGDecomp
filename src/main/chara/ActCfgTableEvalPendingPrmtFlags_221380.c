#include "types.h"

typedef struct Sub {
    void *key;
    s32 arg;
} Sub;

typedef struct Ent {
    s8 *name;
    Sub *sub;
    u8 pad08[0x1C];
    s16 nsub;
    u8 pad26[0x1E];
} Ent;

typedef struct Tbl {
    u8 pad00[0x2C];
    Ent *ents;
    s16 nents;
} Tbl;

typedef struct Obj {
    u8 pad00[0x12];
    s16 x12;
    u8 pad14[0x78];
    u8 x8C[4];
} Obj;

s32 StrNotEqual_1f5300(s8 *, s8 *);
s32 GetActionMgr_1fdb50();
Tbl *SortedNodeGetData_21ff00(s32);
s32 SortedListFindByName_21ff10(void *, s8 *);
Tbl *SortedListFindDataByName_21ffd0(void *, s8 *);
s32 ActCfgTableEvalPendingPrmtFlagsRefs_221040(Obj *, s32, s32, f32);
s32 ActCfgTableGetScopeId_223d00(Obj *);
Tbl *ActCfgTableFindActionByName_223d20(Obj *, s8 *);
void *CharaTableFindStepByName_225320(Tbl *, s32);
s32 CharaTableDataCollectPendingPrmtFlags_2267f0(void *, f32);
s32 CharaTableDataGetReferenceCount_226950(void *);
s32 CharaTableDataGetReferenceList_2269d0(void *);
Obj *ActionMgrGetGlobalTable_234850(s32);

static inline Tbl *lookC(void *p, s8 *name) {
    s32 v;
    v = SortedListFindByName_21ff10(p, name);
    if (v != 0) {
        return SortedNodeGetData_21ff00(v);
    }
    return 0;
}

static inline Tbl *lookB(Obj *o0, s8 *name) {
    Obj *o1;
    if (ActCfgTableGetScopeId_223d00(o0) != 0x7FFF && name != 0 && *name == '#') {
        o1 = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (o1 == 0) {
            return 0;
        }
        return ActCfgTableFindActionByName_223d20(o1, name);
    }
    return SortedListFindDataByName_21ffd0(o0->x8C, name);
}

static inline Tbl *lookA(Obj *obj, s8 *name) {
    Obj *o0;
    if (obj->x12 != 0x7FFF && name != 0 && *name == '#') {
        o0 = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (o0 == 0) {
            return 0;
        }
        return lookB(o0, name);
    }
    return lookC(obj->x8C, name);
}

static inline Ent *find(Tbl *o, s8 *name2, s32 *i_p, Ent **e_p) {
    if (name2 == 0) {
        return 0;
    }
    (*e_p) = o->ents;
    if ((*e_p) == 0) {
        return 0;
    }
    for ((*i_p) = 0; (*i_p) < o->nents; (*i_p)++, (*e_p)++) {
        if (*name2 == *(*e_p)->name && StrNotEqual_1f5300((*e_p)->name + 1, name2 + 1) == 0) {
            return (*e_p);
        }
    }
    return 0;
}

static inline s32 applySubs(Obj *obj, Ent *e, f32 f) {
    s32 acc;
    s32 a;
    Sub *sub;
    s32 n;
    s32 arg;
    Tbl *p;
    s32 b;
    s32 i;
    s32 r;
    void *q;

    sub = e->sub;
    n = e->nsub;
    if (sub == 0) {
        return 0;
    }
    acc = 0;
    for (i = 0; i < n; i++, sub++) {
        arg = sub->arg;
        r = 0;
        p = ActCfgTableFindActionByName_223d20(obj, sub->key);
        if (p != 0) {
            q = CharaTableFindStepByName_225320(p, arg);
            if (q != 0) {
                r |= CharaTableDataCollectPendingPrmtFlags_2267f0(q, f);
                r |= ActCfgTableEvalPendingPrmtFlagsRefs_221040(obj, CharaTableDataGetReferenceList_2269d0(q), CharaTableDataGetReferenceCount_226950(q), f);
            }
        }
        acc |= r;
    }
    return acc;
}

s32 ActCfgTableEvalPendingPrmtFlags_221380(Obj *obj, s8 *name, s8 *name2, f32 f) {
    Ent *find_e;
    Tbl *o;
    Ent *e;
    s32 ret;
    s32 find_i;
    ret = 0;
    o = lookA(obj, name);
    if (o != 0) {
        e = find(o, name2, &find_i, &find_e);
        if (e != 0) {
            ret |= CharaTableDataCollectPendingPrmtFlags_2267f0(e, f);
            ret |= applySubs(obj, e, f);
        }
    }
    return ret;
}
