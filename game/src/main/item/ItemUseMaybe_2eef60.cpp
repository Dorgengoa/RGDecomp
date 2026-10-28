/* rgp:protos */
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct Obj {
    s16 m0;
    s16 pad2;
    s16 m4;
    s16 pad6;
    s16 m8;
    s16 mA;
    s16 *mC;
} Obj;

typedef struct Game {
    u8 pad0[0x18];
    s32 m18;
    s32 m1C;
    u8 *m20;
} Game;

class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vBC() { return VCM0(s32, 0xBC); }
    s32 vC0() { return VCM0(s32, 0xC0); }
    u8 pad4[0x8];
    s32 mC;
    u8 pad10[0x234 - 0x10];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
};

class Lv {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void vBC() { VCM0(void, 0xBC); }
    void vC0() { VCM0(void, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v268() { return VCM0(s32, 0x268); }
    void v26C(f32 a0) { VCM(void, (void *, f32), 0x26C, a0); }
};

typedef struct Ev {
    u8 pad0[0x10];
    s16 *m10;
} Ev;

typedef struct Chr {
    s16 m0;
    u8 pad2[0x71 - 2];
    u8 m71;
} Chr;


extern "C" {
extern s32 GetActionMgr_1fdb50(void);
extern Game *GetGameData_1fede0(void);
extern void FieldHudLogOpen_203fb0(void);
extern Chr *CharaGetExecInfo_2149f0(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaEventLogAddItemUse_2ccc40(s32, s32);
extern void PartyAllySuggestCancel_2eea00(s32);
extern void ItemUseApplyToCharaMaybe_2eeb20(s32, Obj *, s32, u8, u8 *);
extern void CharaSysSetStealthTimer_3a1ca0(u8 *, f32);
extern void CharaSysEventLogKeyRemove_3a3380(u8 *, s32, int);
extern void CharaSysEventLogKeyAdd_3a33b0(u8 *, s32, s32);
extern Ent *ObjMgrFindFiltered_3bb190(s32, s32, s32, s32, s32, s32 *, s32, s32);
extern s32 PartyAllIncapacitated_3c07c0(s32, s32);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern Ent *PartyGetReserveChara_3c1d20(s32, s32);
extern s32 PartyCountExcludingLeader_3c2610(s32, s32, s32);
extern Ent *PartyGetNonLeaderChara_3c2700(s32, s32);
extern Ent *PartyGetLeaderChara_3c2820(s32);
extern Ev *InvFindByUniqueId_3c85d0(s32, s32, s32, s32);
extern void ItemConsume_3d41b0(Ev *, s32, s32, int);
extern s32 ItemGetUseEffectTargetModeMaybe_3d4f00(Ev *);
extern s32 ItemGetUseEffectTargetKind_3d4f30(Ev *);
extern Lv *ActorFindById_3eb870(Game *, s32);
s32 ItemUseMaybe_2eef60(s16 id, Obj *arg1, s32 arg2, u8 arg3, u8 *out);
}


s32 ItemUseMaybe_2eef60(s16 id, Obj *arg1, s32 arg2, u8 arg3, u8 *out)
{
    u8 fF0;
    u8 fl;
    s32 k;
    s16 ids[32] __attribute__((aligned(16)));
    Game *g;
    Ev *p;
    s32 kind;
    s32 idx;
    s32 mode;
    s32 sub;
    s32 n;
    u8 f7;
    u8 f17;
    u8 fEF;
    u8 f16;
    u8 f30;
    u8 fD0;
    u8 on;
    u8 r;
    u8 t;
    s32 i;
    s32 cnt;
    s32 cnt2;
    s32 next;
    Ent *o;
    Chr *q;
    s32 h;
    s32 id8;
    s16 id8b;
    s32 lv;
    u8 fC0;

    if (out != NULL) {
        *out = 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    g = GetGameData_1fede0();
    if (PartyAllIncapacitated_3c07c0(g->m18, 1) != 0) {
        return 0;
    }
    idx = arg1->mA;
    n = 0;
    if (arg1->m4 != 4) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if (g == NULL) {
        return 0;
    }
    p = InvFindByUniqueId_3c85d0(g->m18, idx, -1, 0);
    if (p == NULL) {
        return 0;
    }
    kind = *p->m10;
    mode = ItemGetUseEffectTargetKind_3d4f30(p);
    sub = ItemGetUseEffectTargetModeMaybe_3d4f00(p);
    if (kind == 0x40D9) {
        CharaSysSetStealthTimer_3a1ca0(g->m20, 0.0f);
        ItemConsume_3d41b0(p, 1, 0, 0);
        if (out != NULL) {
            *out = 1;
        }
        return 1;
    }
    fF0 = 0;
    if (sub == 0) {
        ids[n++] = id;
    } else {
        f7 = 0;
        f17 = 0;
        fEF = 0;
        f16 = 0;
        f30 = 0;
        fD0 = 0;
        if (mode == 1) {
            fD0 = 1;
        } else if (mode == 2) {
            f7 = 1;
            f16 = f7;
        } else if (mode == 3) {
            f7 = 1;
            f17 = f7;
            f16 = f7;
            if (sub == 3) {
                fEF = f7;
            }
        } else if (mode == 4) {
            f17 = 1;
            f16 = f17;
        } else if (mode == 5) {
            f7 = 1;
            f17 = f7;
            f30 = f7;
            if (sub == 2) {
                f16 = f7;
            }
            if (sub == 3) {
                f16 = 1;
                fEF = f16;
            }
        } else if (mode == 6) {
            f7 = 1;
            f17 = f7;
            f16 = f7;
            f30 = f7;
            fD0 = f7;
            if (sub == 3) {
                fEF = f7;
            }
        }
        if (f7) {
            o = PartyGetLeaderChara_3c2820(g->m18);
            if ((o->vBC() && f16) || (o->vC0() && f30)) {
                ids[n++] = o->mC;
            }
        }
        if (f17) {
            { s32 t_bt = PartyCountExcludingLeader_3c2610(g->m18, 1, 1); cnt = t_bt; }
            for (i = 0; i < cnt; i++) {
                o = PartyGetNonLeaderChara_3c2700(g->m18, i);
                if (o != NULL && ((o->vBC() && f16) || (o->vC0() && f30))) {
                    ids[n++] = o->mC;
                }
            }
        }
        if (fEF) {
            { s32 t_bt2 = PartyCountReserve_3c1c20(g->m18, 1, 1); cnt2 = t_bt2; }
            for (i = 0; i < cnt2; i++) {
                o = PartyGetReserveChara_3c1d20(g->m18, i);
                if (o != NULL && !o->b2 && ((o->vBC() && f16) || (o->vC0() && f30))) {
                    ids[n++] = o->mC;
                }
            }
        }
        if (fD0) {
            next = -1;
            for (;;) {
                k = -1;
                o = ObjMgrFindFiltered_3bb190(g->m1C, -1, 1, 0, next, &k, 0, 0);
                if (!o || k < 0 || n >= 0x1F) {
                    break;
                }
                next = k + 1;
                ids[n++] = o->mC;
                fF0 = 1;
            }
        }
    }
    if (n <= 0) {
        return 0;
    }
    on = 0;
    if ((u32)(kind - 0x40DE) < 2) {
        on = 1;
        arg3 = on;
    }
    id8 = arg1->m8;
    h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id8);
    q = 0;
    if (h != 0) {
        q = CharaGetExecInfo_2149f0(h);
    }
    fC0 = 0;
    if (q != NULL && q->m71 != 0 && arg1->m0 > 0 && q->m0 == arg1->m0) {
        on = 0;
        fC0 = 1;
    }
    if (on) {
        if (arg1->m0 < 0) {
            arg1->m0 = 0x7FFD;
        }
        CharaSysEventLogKeyAdd_3a33b0(g->m20, arg1->m0, 0);
    } else {
        arg1->m0 = -1;
    }
    r = 0;
    for (i = 0; i < n; i++) {
        fl = 0;
        ItemUseApplyToCharaMaybe_2eeb20(ids[i], arg1, arg2, arg3, &fl);
        if (fl != 0) {
            r = 1;
            fF0 = r;
        }
    }
    if (out != NULL) {
        *out = r;
    }
    if (on) {
        CharaSysEventLogKeyRemove_3a3380(g->m20, arg1->m0, 0);
        FieldHudLogOpen_203fb0();
    }
    t = 0;
    if (fC0) {
        fF0 = 1;
        t = fF0;
    }
    if (fF0) {
        if (t) {
            if (arg1->mC != NULL) {
                CharaEventLogAddItemUse_2ccc40(id8, *arg1->mC);
            }
        }
        ItemConsume_3d41b0(p, 1, 0, 0);
        if (g->m20[0x24C] & 1) {
            id8b = arg1->m8;
            o = (Ent *)ActorFindById_3eb870(g, id8b);
            if (o != NULL) {
                lv = ((Lv *)o)->v268() / 100;
                if (lv == 10) {
                    ((Lv *)o)->v26C(799);
                } else {
                    lv--;
                    if (lv <= 0) {
                        ((Lv *)o)->v26C(0.0f);
                    } else {
                        ((Lv *)o)->v26C(lv * 100 - 1);
                    }
                }
                PartyAllySuggestCancel_2eea00(id8b);
            }
        }
    }
    return 1;
}
