/* rgp:protos */
#define RGP_SELF_BattleEncounterSetupMaybe_2f25f0 1
#include "port/game_protos.h"
#line 1
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
/*rgp*/
/*rgp*/

s32 BattleEncounterSetupMaybe_2f25f0(void)
{
    s32 ids[12] __attribute__((aligned(16)));
    Wld *w;
    Grp *g;
    Pty *p;
    s32 tbl;
    s32 n;
    s32 i;
    s32 hud;
    Obj *o;
    Ent *e;

    w = ((Wld *)GetGameData_1fede0());
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
    tbl = ((s32)GetCharaResMgr_1fdb60());
    n = PartyCountMembers_3c2010(w->m18, 1, 1);
    for (i = 0; i < n; i++) {
        ids[i] = ((short)PartyGetMemberId_3c2490(w->m18, i));
    }
    if (n < p->n) {
        for (i = n; i < p->n; i++) {
            o = ((Obj *)CharaMgrPoolFindByDataId_3a8a70(w->m14, p->ids[i], 1, 1, 0, 0, 0));
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
    tbl = ((s32)GetActionMgr_1fdb50());
    for (i = 0; i < n; i++) {
        e = ((Ent *)ActionMgrFindById_233b50(tbl, ids[i]));
        if (e != 0) {
            CharaRequestBattleEnter_213ec0(e, p->recs[i].flag == 0);
        }
    }
    g = w->sys->grp;
    for (i = 0; i < g->n; i++) {
        e = ((Ent *)ActionMgrFindById_233b50(tbl, g->ents[i].m->id));
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
