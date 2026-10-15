#include "types.h"

typedef struct Pair {
    char *name;
    s32 val;
} Pair;

typedef struct Ent {
    char *name;
    Pair *list;
    u8 *p8;
    u8 padC[0x24 - 0xC];
    s16 n24;
    s16 n26;
    u8 pad28[0x44 - 0x28];
} Ent;

typedef struct Found {
    u8 pad0[0x2C];
    Ent *ents;
    s16 n30;
} Found;

typedef struct Obj {
    u8 pad0[0x12];
    s16 x12;
    u8 pad14[0x8C - 0x14];
    u8 x8C[4];
} Obj;

extern s32 StrNotEqual_1f5300(char *, char *);
extern s32 GetActionMgr_1fdb50(void);
extern Found *SortedNodeGetData_21ff00(s32);
extern s32 SortedListFindByName_21ff10(u8 *, char *);
extern Found *SortedListFindDataByName_21ffd0(u8 *, char *);
extern s32 ActCfgTableGetScopeId_223d00(Obj *);
extern Found *ActCfgTableFindActionByName_223d20(Obj *, char *);
extern Ent *CharaTableFindStepByName_225320(Found *, s32);
extern s32 CharaTableDataGetReferenceCount_226950(Ent *);
extern Pair *CharaTableDataGetReferenceList_2269d0(Ent *);
extern void ActTimeEvntRunInRange_2281d0(u8 *, s32, f32, f32);
extern Obj *ActionMgrGetGlobalTable_234850(s32);

void ActCfgTableRunTimeEvnts_221f40(Obj *arg0, s32 arg1, char *arg2, char *arg3, f32 f0, f32 f1);

static inline Found *G(Obj *p, char *name) {
    Obj *q;
    if (ActCfgTableGetScopeId_223d00(p) != 0x7FFF && name != 0 && *name == '#') {
        q = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (q == 0) {
            return 0;
        }
        return ActCfgTableFindActionByName_223d20(q, name);
    }
    return SortedListFindDataByName_21ffd0(p->x8C, name);
}

static inline Found *F(Obj *obj, char *name) {
    Obj *p;
    s32 t;
    if (obj->x12 != 0x7FFF && name != 0 && *name == '#') {
        p = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (p == 0) {
            return 0;
        }
        return G(p, name);
    }
    t = SortedListFindByName_21ff10(obj->x8C, name);
    return t ? SortedNodeGetData_21ff00(t) : 0;
}

static inline Ent *Find(Found *f, char *name) {
    s32 i;
    Ent *e;
    if (f == 0) {
        return 0;
    }
    if (name == 0) {
        return 0;
    }
    e = f->ents;
    if (e == 0) {
        return 0;
    }
    for (i = 0; i < f->n30; i++, e++) {
        if (*name == *e->name && StrNotEqual_1f5300(e->name + 1, name + 1) == 0) {
            return e;
        }
    }
    return 0;
}

static inline void Apply(Ent *e, s32 a, f32 f0, f32 f1) {
    u8 *p;
    s32 i;
    p = e->p8;
    if (p != 0) {
        for (i = 0; i < e->n26; i++, p += 0x10) {
            ActTimeEvntRunInRange_2281d0(p, a, f0, f1);
        }
    }
}

static inline Ent *Look(Obj *o, char *name, s32 v) {
    Found *t;
    t = ActCfgTableFindActionByName_223d20(o, name);
    if (t != 0) {
        return CharaTableFindStepByName_225320(t, v);
    }
    return 0;
}

void ActCfgTableRunTimeEvnts_221f40(Obj *arg0, s32 arg1, char *arg2, char *arg3, f32 f0, f32 f1) {
    Ent *e;
    Pair *list;
    s32 n;
    s32 j;
    Ent *r;
    s32 cnt;
    Pair *lst;
    s32 m;

    e = Find(F(arg0, arg2), arg3);
    if (e == 0) {
        return;
    }
    Apply(e, arg1, f0, f1);
    list = e->list;
    n = e->n24;
    if (list != 0) {
        for (j = 0; j < n; j++, list++) {
            r = Look(arg0, list->name, list->val);
            if (r != 0) {
                Apply(r, arg1, f0, f1);
                cnt = CharaTableDataGetReferenceCount_226950(r);
                lst = CharaTableDataGetReferenceList_2269d0(r);
                if (lst != 0) {
                    for (m = 0; m < cnt; m++, lst++) {
                        ActCfgTableRunTimeEvnts_221f40(arg0, arg1, lst->name, (char *)lst->val, f0, f1);
                    }
                }
            }
        }
    }
}
