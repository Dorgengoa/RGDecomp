#pragma optimization_level 3
#include "types.h"
#include "vec.h"

class Unit {
public:
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5();
    virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9(); virtual void vf10(); virtual void vf11();
    virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15(); virtual void vf16(); virtual void vf17();
    virtual void vf18(); virtual void vf19(); virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
    virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27(); virtual void vf28(); virtual void vf29();
    virtual void vf30(); virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
    virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39(); virtual void vf40(); virtual void vf41();
    virtual void vf42(); virtual void vf43(); virtual void vf44(); virtual void vf45(); virtual void vf46(); virtual void vf47();
    virtual void vf48(); virtual void vf49(); virtual void vf50(); virtual void vf51(); virtual void vf52(); virtual void vf53();
    virtual void vf54(); virtual void vf55(); virtual void vf56(); virtual void vf57(); virtual void vf58(); virtual void vf59();
    virtual void vf60(); virtual void vf61(); virtual void vf62(); virtual void vf63(); virtual void vf64(); virtual void vf65();
    virtual void vf66(); virtual void vf67(); virtual void vf68(); virtual void vf69(); virtual void vf70(); virtual void vf71();
    virtual void vf72(); virtual void vf73(); virtual void vf74(); virtual void vf75(); virtual void vf76(); virtual void vf77();
    virtual void vf78(); virtual void vf79(); virtual void vf80(); virtual void vf81(); virtual void vf82(); virtual void vf83();
    virtual void vf84(); virtual void vf85(); virtual void vf86(); virtual void vf87(); virtual void vf88(); virtual void vf89();
    virtual void vf90(); virtual void vf91(); virtual void vf92(); virtual void vf93(); virtual void vf94(); virtual void vf95();
    virtual void vf96(); virtual void vf97(); virtual void vf98(); virtual void vf99(); virtual void vf100();
    virtual s32 Has(s32); /* 0x19C */
};

typedef struct Ent {
    u8 pad0[0xB8];
    u32 xB8;
    u8 padBC[0x148 - 0xBC];
    s16 x148;
} Ent;

typedef struct Mode {
    u8 pad0[0x24];
    s16 x24;
} Mode;

typedef struct Pty {
    u8 pad0[0x18E];
    s16 x18E;
} Pty;

typedef struct Gm {
    u8 pad0[0xC];
    Mode *xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
} Gm;

typedef struct Gm2 {
    u8 pad0[0x18];
    Pty *x18;
} Gm2;

extern "C" {
s32 GetCurrentScene_1f5be0(void);
Gm *GetGameData_1fede0(void);
s32 IsInBattle_288420(void);
s32 AiCollectAllIds_2cd4d0(s32 *, s32);
s32 PartyCollectLiveMemberIds_2cd6e0(s32 *, s32);
s32 AiCollectTargetIds_2cd530(s32 *, s32);
Ent *CharaGetAiById_2cedd0(s32);
s32 ArrayCopyExcept_1d7c50(s32 *, s32 *, s32, s32);
void BattleAiTargetRefreshMaybe_2cdd80(s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
void CharaCloneFadeStep_2cd060(s32);
s32 ActionMgrFindByIdGlobal_2cee10(s32);
s32 TargetMngHasTargetId_313bf0(void);
s32 CharaGetTargetRef_214a30(s32);
s32 TargetRefGetId_2e7120(s32);
s32 AiLinkTargetsMaybe_2ce660(s32, s32, s32);
s32 StateVarGet_3ccac0(s32, s32);
void StateVarSet_3cc9c0(s32, s32, s32, s32);
s32 CharaActiveSlotRecIdInRange_2cc9f0(s32, s32);
void AiSetTargetCharaId_2c0f10(Ent *, s32);
s32 PartyCountExcludingLeader_3c2610(s32, s32, s32);
s32 PartyGetNonLeaderId_3c2750(s32, s32);
Unit *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 AiGetTargetCharaId_2c0fd0(Ent *);
s32 ActorGetHpById_2cd870(s32, s32);
void BattleAiRequestTargetRefresh_2cedc0(void);
Unit *ObjFindById_3bb3a0(s32, s32);
void CharaGetPos_2388a0(s32, Vec4 *);
void CharaGetForwardVec_238830(s32, Vec4 *);
void CharaGetRot_2388b0(s32, Vec4 *);
void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
void VecNormalize_13bd90(Vec4 *, Vec4 *);
void AxisAngleBetweenVecs_1d7da0(Vec4 *, f32 *, Vec4 *, Vec4 *);
f32 WrapAngle_13c050(f32);
void CharaSetYaw_2138f0(s32, f32);
extern s32 D_004825D0;
extern u8 D_004DB920[];
extern s32 D_004DB924[];
extern s32 D_004DB97C[];
extern s32 D_004DB980[];
extern s32 D_004DBA40[];
extern s32 D_004DBA44[];
extern s32 D_004DBA84[];
extern s32 D_004DBA88[];
void BattleAiTargetUpdate_2ce790(void);
}

static inline s32 Copy(Ent *dst, Ent *src) { s32 t = src->x148; dst->x148 = t; AiSetTargetCharaId_2c0f10(dst, t); return t; }
extern "C" void BattleAiTargetUpdate_2ce790(void)
{
    f32 ang;
    Vec4 pos;
    Vec4 p2;
    Vec4 dir;
    Vec4 d;
    Vec4 out;
    Vec4 rot;
    s32 ctx;
    Gm *gm;
    Gm2 *gm2;
    s32 i;
    s32 *pp;
    Ent *e;
    s32 n;
    s32 id;
    s32 cur;
    s32 u;
    s32 w;
    s32 r;
    Ent *a;
    Ent *b;
    s32 v;
    s32 k;
    Unit *p;
    s32 u3;

    ctx = GetCurrentScene_1f5be0();
    gm = GetGameData_1fede0();
    if (IsInBattle_288420() == 0) {
        return;
    }
    gm2 = (Gm2 *)GetGameData_1fede0();
    D_004DB97C[0] = AiCollectAllIds_2cd4d0(D_004DB980, 0x30);
    D_004DBA40[0] = PartyCollectLiveMemberIds_2cd6e0(D_004DBA44, 0x10);
    D_004DBA84[0] = AiCollectTargetIds_2cd530(D_004DBA88, 0x20);
    D_004DB924[0] = gm2->x18->x18E;
    for (i = 0; i < D_004DBA84[0]; i++) {
        pp = (s32 *)(D_004DB920 + i * 4 + 0x168);
        e = CharaGetAiById_2cedd0(*pp);
        if (e == 0) {
            continue;
        }
        if (e->xB8 & 0x400) {
            D_004DBA84[0] = ArrayCopyExcept_1d7c50(D_004DBA88, D_004DBA88, D_004DBA84[0], *pp);
        }
    }
    if (D_004825D0 != 0) {
        BattleAiTargetRefreshMaybe_2cdd80(ctx);
        D_004825D0 = 0;
    } else {
        s32 *lst;
        n = D_004DB97C[0];
        lst = D_004DB980;
        for (i = 0; i < n; i++) {
            id = lst[i];
            if (id < 0) {
                continue;
            }
            if (!(id < 0xE0)) {
                continue;
            }
            e = CharaGetAiById_2cedd0(id);
            if (e == 0) {
                continue;
            }
            if (e->x148 >= 0 && ObjRecGetLiveObject_1c4a90(ctx, e->x148) != 0) {
                continue;
            }
            BattleAiTargetRefreshMaybe_2cdd80(ctx);
            break;
        }
    }
    CharaCloneFadeStep_2cd060(ctx);
    cur = D_004DB924[0];
    u = ActionMgrFindByIdGlobal_2cee10(cur);
    e = CharaGetAiById_2cedd0(cur);
    if (TargetMngHasTargetId_313bf0() && u != 0 && e != 0) {
        w = CharaGetTargetRef_214a30(u);
        r = -1;
        if (w != 0) {
            r = AiLinkTargetsMaybe_2ce660(cur, TargetRefGetId_2e7120(w), 0);
        }
        e->x148 = r;
    }
    r = StateVarGet_3ccac0(gm->x10, 0x60);
    if (D_004DB924[0] == r) {
        StateVarSet_3cc9c0(gm->x10, 0x60, -1, 1);
    }
    if (CharaActiveSlotRecIdInRange_2cc9f0(4, 0x371)) {
        a = CharaGetAiById_2cedd0(4);
        b = CharaGetAiById_2cedd0(7);
        if (a != 0 && b != 0) {
            if (D_004DB924[0] == 7) {
                v = Copy(a, b);
            } else {
                v = Copy(b, a);
            }
            e = CharaGetAiById_2cedd0(v);
            if (e != 0) {
                e->x148 = 4;
                AiSetTargetCharaId_2c0f10(e, 4);
            }
        }
    }
    if (gm->xC->x24 == 1) {
        n = PartyCountExcludingLeader_3c2610(gm->x18, 1, 1);
        if (n > 0) {
            id = -1;
            if (TargetMngHasTargetId_313bf0()) {
                w = CharaGetTargetRef_214a30(u);
                if (w != 0) {
                    id = TargetRefGetId_2e7120(w);
                }
            }
            if (id == -1 && !(n < 2)) {
                k = PartyGetNonLeaderId_3c2750(gm->x18, 0);
                p = CharaMgrPoolFindById_3a8c60(gm->x14, k);
                if (p != 0 && !p->Has(3)) {
                    e = CharaGetAiById_2cedd0(k);
                    if (e != 0) {
                        id = AiGetTargetCharaId_2c0fd0(e);
                    }
                }
            }
            if (id >= 0x80 && id < 0x9C && ActorGetHpById_2cd870(id, 0) > 0) {
                for (i = 0; i < n; i++) {
                    k = PartyGetNonLeaderId_3c2750(gm->x18, i);
                    p = CharaMgrPoolFindById_3a8c60(gm->x14, k);
                    if (p == 0) {
                        continue;
                    }
                    if (p->Has(3)) {
                        continue;
                    }
                    e = CharaGetAiById_2cedd0(k);
                    if (e == 0) {
                        continue;
                    }
                    e->x148 = id;
                    AiSetTargetCharaId_2c0f10(e, id);
                }
            } else if (D_004DBA84[0] > 0) {
                BattleAiRequestTargetRefresh_2cedc0();
            }
        }
    }
    p = CharaMgrPoolFindById_3a8c60(gm->x14, 3);
    u3 = ActionMgrFindByIdGlobal_2cee10(3);
    if (p == 0) {
        return;
    }
    if (u3 == 0) {
        return;
    }
    if (!p->Has(0x2B) && !p->Has(0x2D)) {
        return;
    }
    CharaGetPos_2388a0(u3, &pos);
    for (i = 0; i < 0x1C; i++) {
        Unit *q;
        k = i + 0x80;
        q = ObjFindById_3bb3a0(gm->x1C, k);
        if (q == 0) {
            continue;
        }
        if (!q->Has(7)) {
            continue;
        }
        w = ActionMgrFindByIdGlobal_2cee10(k);
        if (w == 0) {
            continue;
        }
        CharaGetPos_2388a0(w, &p2);
        CharaGetForwardVec_238830(w, &dir);
        VecSub_13be40(&d, &pos, &p2);
        VecNormalize_13bd90(&dir, &dir);
        VecNormalize_13bd90(&d, &d);
        AxisAngleBetweenVecs_1d7da0(&out, &ang, &dir, &d);
        if (ang == 0.0f) {
            continue;
        }
        ang = ang * 0.5f;
        if (out.y < 0.0f) {
            ang = ang * -1.0f;
        }
        CharaGetRot_2388b0(w, &rot);
        rot.y = WrapAngle_13c050(rot.y + ang);
        CharaSetYaw_2138f0(w, rot.y);
    }
}
