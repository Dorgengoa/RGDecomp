#include "types.h"
#pragma always_inline on

typedef struct {
    u8 pad0[0xC];
    s32 flags;
    u8 pad10[0x14 - 0x10];
} Item;

typedef struct {
    char *name;
    void *ref;
} Link;

typedef struct {
    s32 flags;
    s32 unk4;
} MItem;

typedef struct {
    char *name;
    Link *links;
    u8 pad8[0x20 - 0x8];
    Item *items;
    s16 nlinks;
    u8 pad26[0x32 - 0x26];
    s16 nitems;
    u8 pad34[0x44 - 0x34];
} Group;

typedef struct {
    u8 pad0[0x1C];
    MItem *items;
    u8 pad20[0x24 - 0x20];
    s16 nitems;
    u8 pad26[0x2C - 0x26];
    Group *groups;
    s16 ngroups;
} Model;

typedef struct {
    u8 pad0[0x12];
    s16 id;
    u8 pad14[0x8C - 0x14];
    u8 list[4];
} Obj;

extern s32 GetActionMgr_1fdb50();
extern void *ActionMgrGetGlobalTable_234850(s32);
extern s32 ActCfgTableGetScopeId_223d00(void *);
extern Model *ActCfgTableFindActionByName_223d20(void *, char *);
extern Model *SortedListFindDataByName_21ffd0(void *, char *);
extern void *SortedListFindByName_21ff10(void *, char *);
extern Model *SortedNodeGetData_21ff00(void *);
extern s32 StrNotEqual_1f5300(char *, char *);
extern s32 ActDataCnctGetCmndMask_2274c0(void *);
extern s32 ActionEntryTimeMatch_228310(Item *, f32);
extern void *ActTimeCnctGetCnct_227540(void *);
extern void *CharaTableFindStepByName_225320(void *, void *);
extern void *CharaTableDataFindTimeCnctByMask_226640(void *, s32, f32);
extern void *ActDataFindCnctByMask_225c00(void *, s32);
extern s32 CharaTableDataGetReferenceList_2269d0(void *);
extern s32 CharaTableDataGetReferenceCount_226950(void *);
extern void *ActCfgTableFindCnctByMaskRefs_2208a0(Obj *, s32, s32, s32, f32);

static inline Model *find_model2(void *o, char *name) {
    void *v;
    if (ActCfgTableGetScopeId_223d00(o) != 0x7FFF && name != NULL && name[0] == '#') {
        v = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (v == NULL) {
            return NULL;
        }
        return ActCfgTableFindActionByName_223d20(v, name);
    }
    return SortedListFindDataByName_21ffd0((u8 *)o + 0x8C, name);
}

static inline Model *find_model(Obj *obj, char *name) {
    void *o;
    void *r;
    if (obj->id != 0x7FFF && name != NULL && name[0] == '#') {
        o = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (o == NULL) {
            return NULL;
        }
        return find_model2(o, name);
    }
    r = SortedListFindByName_21ff10(obj->list, name);
    return r != NULL ? SortedNodeGetData_21ff00(r) : NULL;
}

static inline Group *find_group(Model *m, char *sub) {
    Group *g;
    s32 i;
    if (sub == NULL) {
        return NULL;
    }
    g = m->groups;
    if (g == NULL) {
        return NULL;
    }
    for (i = 0; i < m->ngroups; i++, g++) {
        if (sub[0] == g->name[0] && StrNotEqual_1f5300(g->name + 1, sub + 1) == 0) {
            return g;
        }
    }
    return NULL;
}

static inline void *find_item(Group *g, s32 mask, f32 f) {
    Item *it;
    s32 i;
    it = g->items;
    if (it == NULL) {
        return NULL;
    }
    for (i = 0; i < g->nitems; i++, it++) {
        if ((mask & ActDataCnctGetCmndMask_2274c0(&it->flags)) == ActDataCnctGetCmndMask_2274c0(&it->flags) && ActionEntryTimeMatch_228310(it, f) != 0) {
            return ActTimeCnctGetCnct_227540(&it->flags);
        }
    }
    return NULL;
}

static inline MItem *find_mitem(Model *m, s32 mask) {
    MItem *it;
    s32 i;
    it = m->items;
    if (it == NULL) {
        return NULL;
    }
    for (i = 0; i < m->nitems; i++, it++) {
        if ((mask & ActDataCnctGetCmndMask_2274c0(it)) == ActDataCnctGetCmndMask_2274c0(it)) {
            return it;
        }
    }
    return NULL;
}

static inline void *try_link(Obj *obj, Link *l, s32 mask, f32 f) {
    void *ref;
    Model *sc;
    void *a;
    void *r;
    ref = l->ref;
    sc = ActCfgTableFindActionByName_223d20(obj, l->name);
    if (sc == NULL) {
        return NULL;
    }
    a = CharaTableFindStepByName_225320(sc, ref);
    if (a != NULL && (r = CharaTableDataFindTimeCnctByMask_226640(a, mask, f)) != NULL) {
        return r;
    }
    if ((r = ActDataFindCnctByMask_225c00(sc, mask)) != NULL) {
        return r;
    }
    if (a != NULL && (r = ActCfgTableFindCnctByMaskRefs_2208a0(obj, CharaTableDataGetReferenceList_2269d0(a), CharaTableDataGetReferenceCount_226950(a), mask, f)) != NULL) {
        return r;
    }
    return NULL;
}

static inline void *find_link(Obj *obj, Group *g, s32 mask, f32 f) {
    Link *l;
    s32 n;
    s32 i;
    void *r;
    l = g->links;
    n = g->nlinks;
    if (l == NULL) {
        return NULL;
    }
    for (i = 0; i < n; i++, l++) {
        r = try_link(obj, l, mask, f);
        if (r != NULL) {
            return r;
        }
    }
    return NULL;
}

void *ActCfgTableFindCnctByMask_220950(Obj *obj, char *name, char *sub, s32 mask, f32 f) {
    Model *m;
    Group *g;
    void *r;

    if (obj->id != 0x7FFF && name != NULL && name[0] == '#') {
        m = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (m == NULL) {
            m = NULL;
        } else {
            m = find_model2(m, name);
        }
    } else {
        m = SortedListFindByName_21ff10(obj->list, name);
        m = m != NULL ? SortedNodeGetData_21ff00(m) : NULL;
    }
    if (m == NULL) {
        return NULL;
    }
    g = find_group(m, sub);
    if (g != NULL) {
        r = find_item(g, mask, f);
        if (r != NULL) {
            return r;
        }
    }
    r = find_mitem(m, mask);
    if (r != NULL) {
        return r;
    }
    if (g != NULL) {
        r = find_link(obj, g, mask, f);
        if (r != NULL) {
            return r;
        }
    }
    return NULL;
}
