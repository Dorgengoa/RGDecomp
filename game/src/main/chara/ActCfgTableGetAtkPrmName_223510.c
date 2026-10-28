/* rgp:protos */
#define RGP_SELF_ActCfgTableGetAtkPrmName_223510 1
#define RGP_SELF_Find 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad[8];
} Entry;

typedef struct {
    u8 pad0[0x12];
    s16 x12;
    u8 pad14[0x3C];
    Entry *entries;
    u8 pad54[0x20];
    s16 count;
} Scope;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 ActCfgTableGetAtkPrmName_223510(Scope *s, s32 a, s32 b, s32 def);

static inline Entry *Find(Scope *s, s32 a, s32 b)
{
    Entry *e;
    s32 i;

    e = s->entries;
    if (e == NULL) {
        return NULL;
    }
    for (i = 0; i < s->count; i++, e++) {
        if (a == ((short)ActInfoAtkPrmGetSlot_22ea80(e)) && b == ((short)ActInfoAtkPrmGetId_22ea70(e))) {
            return e;
        }
    }
    return NULL;
}

s32 ActCfgTableGetAtkPrmName_223510(Scope *s, s32 a, s32 b, s32 def)
{
    Entry *e;
    Scope *p;

    e = Find(s, a, b);
    if (e != NULL) {
        return ActInfoAtkPrmGetName_22ea60(e);
    }
    if (s->x12 == 0x7FFF) {
        return def;
    }
    p = ((Scope *)ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50())));
    if (p == NULL) {
        return 0;
    }
    e = Find(p, a, b);
    if (e != NULL) {
        return ActInfoAtkPrmGetName_22ea60(e);
    }
    if (p->x12 == 0x7FFF) {
        return def;
    }
    p = ((Scope *)ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50())));
    if (p == NULL) {
        return 0;
    }
    e = ((Entry *)ActCfgTableFindAtkPrm_2227c0(p, a, b));
    if (e != NULL) {
        return ActInfoAtkPrmGetName_22ea60(e);
    }
    if (((short)ActCfgTableGetScopeId_223d00(p)) == 0x7FFF) {
        return def;
    }
    p = ((Scope *)ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50())));
    if (p == NULL) {
        return 0;
    }
    return ActCfgTableGetAtkPrmName_223510(p, a, b, def);
}
