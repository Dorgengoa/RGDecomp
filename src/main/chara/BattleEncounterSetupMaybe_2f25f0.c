#include "types.h"

typedef struct Rec { s16 flag; u8 pad2[0x12]; } Rec;
typedef struct Pty {
    u8 pad0[0x24];
    s16 n;
    s16 ids[13];
    Rec recs[1];
} Pty;
typedef struct Mem { u8 pad0[0xC]; s32 id; } Mem;
typedef struct MEnt { Mem *m; u8 pad4[4]; } MEnt;
typedef struct Grp {
    u8 pad0[0x18];
    Pty *pty;
    u8 pad1C[0x28];
    s16 n;
    u8 pad46[6];
    MEnt ents[1];
} Grp;
typedef struct Sys { u8 pad0[0x238]; Grp *grp; } Sys;
typedef struct Wld { u8 pad0[0x14]; s32 m14; s32 m18; u8 pad1C[4]; Sys *sys; } Wld;
typedef struct Ent { u8 pad0[0xA44]; s32 flags; } Ent;
typedef struct Obj { u8 pad0[0xC]; s32 id; } Obj;

extern void CharaPartyResRequestMaybe_1f00e0(s32, s32);
extern void CharaResLoadListMaybe_1f02d0(s32, s32, s32 *, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern s32 GetCharaResMgr_1fdb60(void);
extern Wld *GetGameData_1fede0(void);
extern void CharaRequestBattleEnter_213ec0(Ent *, s32);
extern void CharaSetAppearMode_213fb0(Ent *, s32, s32);
extern Ent *ActionMgrFindById_233b50(s32, s32);
extern void BattleEncounterUnitsSetupMaybe_2f2b60(void);
extern void FieldViewModeActivateEncounterMaybe_2f3400(void);
extern s32 FieldViewModeGet_2f35a0(void);
extern s32 CharaSysGetEncounterIdMaybe_3a36d0(Sys *);
extern s32 CharaSysStateFlag24Bit2Related_3a3880(Sys *);
extern Obj *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyGetMemberId_3c2490(s32, s32);
extern void GameDataBattleBegin_3e6930(Wld *);

s32 BattleEncounterSetupMaybe_2f25f0(void)
{
    s32 ids[12];
    Wld *w;
    Grp *g;
    Pty *p;
    s32 tbl;
    s32 n;
    s32 i;
    s32 hud;
    Obj *o;
    Ent *e;

    w = GetGameData_1fede0();
    g = w->sys->grp;
    if (g != 0) {
        p = g->pty;
    } else {
        p = 0;
    }
    if (p == 0) {
        return 0;
    }
    FieldViewModeActivateEncounterMaybe_2f3400();
    if (FieldViewModeGet_2f35a0() != 2) {
        return 0;
    }
    tbl = GetCharaResMgr_1fdb60();
    n = PartyCountMembers_3c2010(w->m18, 1, 1);
    for (i = 0; i < n; i++) {
        ids[i] = PartyGetMemberId_3c2490(w->m18, i);
    }
    if (n < p->n) {
        for (i = n; i < p->n; i++) {
            o = CharaMgrPoolFindByDataId_3a8a70(w->m14, p->ids[i], 1, 1, 0, 0, 0);
            if (o != 0) {
                ids[n++] = o->id;
            }
        }
    }
    hud = GetCurrentScene_1f5be0();
    if (CharaSysGetEncounterIdMaybe_3a36d0(w->sys) == 0x271B) {
        CharaPartyResRequestMaybe_1f00e0(tbl, hud);
    } else {
        CharaResLoadListMaybe_1f02d0(tbl, hud, ids, n);
    }
    GameDataBattleBegin_3e6930(w);
    BattleEncounterUnitsSetupMaybe_2f2b60();
    tbl = GetActionMgr_1fdb50();
    for (i = 0; i < n; i++) {
        e = ActionMgrFindById_233b50(tbl, ids[i]);
        if (e != 0) {
            CharaRequestBattleEnter_213ec0(e, p->recs[i].flag == 0);
        }
    }
    g = w->sys->grp;
    for (i = 0; i < g->n; i++) {
        e = ActionMgrFindById_233b50(tbl, g->ents[i].m->id);
        if (e != 0) {
            e->flags |= 0x1000000;
            if (CharaSysStateFlag24Bit2Related_3a3880(w->sys) != 0) {
                CharaSetAppearMode_213fb0(e, 2, 0);
            } else {
                CharaSetAppearMode_213fb0(e, 0, 0);
            }
        }
    }
    return 1;
}
