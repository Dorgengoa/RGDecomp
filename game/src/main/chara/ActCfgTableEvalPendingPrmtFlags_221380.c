/* rgp:protos */
#define RGP_SELF_ActCfgTableEvalPendingPrmtFlags_221380 1
#define RGP_SELF_applySubs 1
#define RGP_SELF_find 1
#define RGP_SELF_lookA 1
#define RGP_SELF_lookB 1
#define RGP_SELF_lookC 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline Tbl *lookC(void *p, s8 *name) {
    s32 v;
    v = SortedListFindByName_21ff10(p, name);
    if (v != 0) {
        return ((Tbl *)SortedNodeGetData_21ff00(v));
    }
    return 0;
}

static inline Tbl *lookB(Obj *o0, s8 *name) {
    Obj *o1;
    if (((short)ActCfgTableGetScopeId_223d00(o0)) != 0x7FFF && name != 0 && *name == '#') {
        o1 = ((Obj *)ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50())));
        if (o1 == 0) {
            return 0;
        }
        return ((Tbl *)ActCfgTableFindActionByName_223d20(o1, name));
    }
    return ((Tbl *)SortedListFindDataByName_21ffd0(o0->x8C, name));
}

static inline Tbl *lookA(Obj *obj, s8 *name) {
    Obj *o0;
    if (obj->x12 != 0x7FFF && name != 0 && *name == '#') {
        o0 = ((Obj *)ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50())));
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

static inline long long applySubs(Obj *obj, Ent *e, f32 f) {
    long long acc;
    s32 a;
    Sub *sub;
    s32 n;
    s32 arg;
    Tbl *p;
    s32 b;
    s32 i;
    long long r;
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
        p = ((Tbl *)ActCfgTableFindActionByName_223d20(obj, sub->key));
        if (p != 0) {
            q = CharaTableFindStepByName_225320(p, arg);
            if (q != 0) {
                r |= CharaTableDataCollectPendingPrmtFlags_2267f0(q, f);
                r |= ActCfgTableEvalPendingPrmtFlagsRefs_221040(obj, CharaTableDataGetReferenceList_2269d0(q), ((short)CharaTableDataGetReferenceCount_226950(q)), f);
            }
        }
        acc |= r;
    }
    return acc;
}

long long ActCfgTableEvalPendingPrmtFlags_221380(Obj *obj, s8 *name, s8 *name2, f32 f) {
    Ent *find_e;
    Tbl *o;
    Ent *e;
    long long ret;
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
