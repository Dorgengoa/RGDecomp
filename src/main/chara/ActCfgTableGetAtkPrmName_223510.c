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

extern s32 GetActionMgr_1fdb50(void);
extern Entry *ActCfgTableFindAtkPrm_2227c0(Scope *, s32, s32);
extern s32 ActCfgTableGetScopeId_223d00(Scope *);
extern s32 ActInfoAtkPrmGetName_22ea60(Entry *);
extern s32 ActInfoAtkPrmGetId_22ea70(Entry *);
extern s32 ActInfoAtkPrmGetSlot_22ea80(Entry *);
extern Scope *ActionMgrGetGlobalTable_234850(s32);
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
        if (a == ActInfoAtkPrmGetSlot_22ea80(e) && b == ActInfoAtkPrmGetId_22ea70(e)) {
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
    p = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
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
    p = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (p == NULL) {
        return 0;
    }
    e = ActCfgTableFindAtkPrm_2227c0(p, a, b);
    if (e != NULL) {
        return ActInfoAtkPrmGetName_22ea60(e);
    }
    if (ActCfgTableGetScopeId_223d00(p) == 0x7FFF) {
        return def;
    }
    p = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (p == NULL) {
        return 0;
    }
    return ActCfgTableGetAtkPrmName_223510(p, a, b, def);
}
