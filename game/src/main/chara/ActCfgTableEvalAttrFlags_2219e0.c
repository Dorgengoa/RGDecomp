/* rgp:protos */
#define RGP_SELF_ActCfgTableEvalAttrFlags_2219e0 1
#define RGP_SELF_Find002219E0 1
#define RGP_SELF_LookA002219E0 1
#define RGP_SELF_LookB002219E0 1
#define RGP_SELF_Upd1_002219E0 1
#define RGP_SELF_Upd2_002219E0 1
#define RGP_SELF_Upd3_002219E0 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct Ent002219E0 Ent002219E0;
typedef struct {
    u64 flags;
    u8 pad8[0x24];
    Ent002219E0 *ents;
    s16 count;
} Res002219E0;

struct Ent002219E0 {
    char *name;
    u8 *unk4;
    u8 pad8[0x10];
    u8 *unk18;
    u8 pad1C[8];
    s16 unk24;
    u8 pad26[8];
    s16 unk2E;
    u8 pad30[0x14];
};

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
/*rgp*/
/*rgp*/
/*rgp*/

#pragma inline_depth(10)
static inline Res002219E0 *LookB002219E0(u8 *o, char *name) {
    u8 *o2;
    if (((short)ActCfgTableGetScopeId_223d00(o)) != 0x7FFF && name != NULL && *name == '#') {
        o2 = ((u8 *)ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50())));
        if (o2 == NULL) {
            return NULL;
        }
        return ((Res002219E0 *)ActCfgTableFindActionByName_223d20(o2, name));
    }
    return ((Res002219E0 *)SortedListFindDataByName_21ffd0(o + 0x8C, name));
}

static inline Res002219E0 *LookA002219E0(u8 *self, char *name) {
    s32 t;
    u8 *o;
    if (*(s16 *)(self + 0x12) != 0x7FFF && name != NULL && *name == '#') {
        o = ((u8 *)ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50())));
        if (o == NULL) {
            return NULL;
        }
        return LookB002219E0(o, name);
    }
    t = SortedListFindByName_21ff10(self + 0x8C, name);
    return t ? ((Res002219E0 *)SortedNodeGetData_21ff00(t)) : NULL;
}

static inline Ent002219E0 *Find002219E0(Res002219E0 *r, char *name, s32 *ip) {
    Ent002219E0 *e;
    if (name == NULL) {
        return NULL;
    }
    e = r->ents;
    if (e == NULL) {
        return NULL;
    }
    for (*ip = 0; *ip < r->count; (*ip)++, e++) {
        if (*name == *e->name && StrNotEqual_1f5300(e->name + 1, name + 1) == 0) {
            return e;
        }
    }
    return NULL;
}

static inline u64 Upd3_002219E0(u8 *self, char *name, s32 arg, f32 f) {
    u64 acc;
    s32 a;
    s32 h;
    acc = 0;
    h = (s32)((Res002219E0 *)ActCfgTableFindActionByName_223d20(self, name));
    if (h != 0) {
        acc |= ActDataGetAttrFlags_225b60(h);
        h = CharaTableFindStepByName_225320(h, arg);
        if (h != 0) {
            acc |= CharaTableDataCollectAttrFlags_226490(h, f);
            a = CharaTableDataGetReferenceList_2269d0(h);
            acc |= ActCfgTableEvalAttrFlagsRefs_221940(self, a, ((short)CharaTableDataGetReferenceCount_226950(h)), f);
        }
    }
    return acc;
}

static inline u64 Upd1_002219E0(Ent002219E0 *e, f32 f) {
    u64 acc;
    u8 *p;
    s32 i;
    p = e->unk18;
    acc = 0;
    if (p != NULL) {
        for (i = 0; i < e->unk2E; i++, p += 0x10) {
            if (ActTimeAttrIsActive_2284d0(p, f) != 0) {
                acc |= ActTimeAttrGetFlags_227740(p + 8);
            }
        }
    }
    return acc;
}

static inline u64 Upd2_002219E0(u8 *self, Ent002219E0 *e, f32 f) {
    s32 n;
    u8 *p;
    s32 i;
    u64 acc;
    p = e->unk4;
    n = e->unk24;
    if (p == NULL) {
        return 0;
    }
    acc = 0;
    for (i = 0; i < n; i++, p += 8) {
        acc |= Upd3_002219E0(self, *(char **)p, *(s32 *)(p + 4), f);
    }
    return acc;
}

u64 ActCfgTableEvalAttrFlags_2219e0(u8 *self, char *name, char *name2, f32 f) {
    s32 i;
    Ent002219E0 *e;
    u64 result;
    Res002219E0 *r;

    result = 0;
    r = LookA002219E0(self, name);
    if (r != NULL) {
        result |= r->flags;
        e = Find002219E0(r, name2, &i);
        if (e != NULL) {
            result |= Upd1_002219E0(e, f);
            result |= Upd2_002219E0(self, e, f);
        }
    }
    return result;
}
