#include "types.h"

typedef struct Pair {
    s32 id;
    char *name;
} Pair;

typedef struct Ent {
    char *name;
    Pair *pairs;
    u8 pad08[0x8];
    u8 *list14;
    u8 pad14[0x10];
    s16 pairCount;
    u8 pad26[4];
    s16 list14Count;
    u8 pad2C[0x18];
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
extern Found *ActCfgTableFindActionByName_223d20(Obj *, s32);
extern Ent *CharaTableFindStepByName_225320(Found *, char *);
extern s32 CharaTableDataGetReferenceCount_226950(Ent *);
extern s32 CharaTableDataGetReferenceList_2269d0(Ent *);
extern void ActTimeAcclAddInRange_227990(u8 *, void *, f32, f32);
extern void CharaTableDataAddTimeAccl_2265b0(Ent *, void *, f32, f32);
extern void ActCfgTableAddTimeAcclRefs_2202a0(Obj *, void *, s32, s32, f32, f32);
extern Obj *ActionMgrGetGlobalTable_234850(s32);

static inline Found *G(Obj *p, char *name) {
    Obj *q;
    if (ActCfgTableGetScopeId_223d00(p) != 0x7FFF && name != 0 && *name == '#') {
        q = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (q == 0) {
            return 0;
        }
        return ActCfgTableFindActionByName_223d20(q, (s32)name);
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

static inline Ent *Find(Found *f, char *name, s32 *i_p, Ent **e_p) {
    if (name == 0) {
        return 0;
    }
    (*e_p) = f->ents;
    if ((*e_p) == 0) {
        return 0;
    }
    for ((*i_p) = 0; (*i_p) < f->n30; (*i_p)++, (*e_p)++) {
        if (*name == *(*e_p)->name && StrNotEqual_1f5300((*e_p)->name + 1, name + 1) == 0) {
            return (*e_p);
        }
    }
    return 0;
}

static inline void Apply(Ent *e, void *a, f32 f0, f32 f1) {
    u8 *p;
    s32 i;
    p = e->list14;
    if (p != 0) {
        for (i = 0; i < e->list14Count; i++, p += 0x10) {
            ActTimeAcclAddInRange_227990(p, a, f0, f1);
        }
    }
}

void ActCfgTableAddTimeAccl_220340(Obj *arg0, void *arg1, char *arg2, char *arg3, f32 f0, f32 f1) {
    Ent *find_e;
    s32 find_i;
    Ent *e;
    Pair *list;
    s32 n;
    s32 j;
    Ent *r;
    Found *t;
    char *nm;

    {
        Found *fd = F(arg0, arg2);
        if (fd == 0) return;
        e = Find(fd, arg3, &find_i, &find_e);
    }
    if (e == 0) {
        return;
    }
    Apply(e, arg1, f0, f1);
    n = e->pairCount;
    list = e->pairs;
    if (list != 0) {
        for (j = 0; j < n; j++, list++) {
            nm = list->name;
            t = ActCfgTableFindActionByName_223d20(arg0, list->id);
            if (t != 0) { r = CharaTableFindStepByName_225320(t, nm);
            if (r != 0) {
                CharaTableDataAddTimeAccl_2265b0(r, arg1, f0, f1);
                ActCfgTableAddTimeAcclRefs_2202a0(arg0, arg1, CharaTableDataGetReferenceList_2269d0(r), CharaTableDataGetReferenceCount_226950(r), f0, f1);
            }}
        }
    }
}
