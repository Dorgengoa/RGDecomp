#include "types.h"

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct A {
    u8 pad0[0xC];
    f32 fC;
    f32 f10;
    u8 pad14[4];
    s8 m18;
    s8 m19;
    s16 m1A;
    f32 f1C;
} A;

typedef struct Part {
    u8 pad0[4];
    s8 m4;
} Part;

class Tbl {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual Part *v70(s32);
};

typedef struct Holder {
    u8 pad0[8];
    Tbl *m8;
} Holder;

typedef struct G2 {
    u8 pad0[0x58];
    Holder *m58;
} G2;

typedef struct G1 {
    u8 pad0[0x18];
    u8 *m18;
} G1;

class Chara {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual s32 v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBC();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCC();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDC();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEC();
    virtual s32 vF0();
    virtual void vF4();
    virtual void vF8();
    virtual void vFC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual void v19C();
    virtual void v1A0();
    virtual void v1A4();
    virtual void v1A8();
    virtual void v1AC();
    virtual void v1B0();
    virtual void v1B4();
    virtual void v1B8();
    virtual void v1BC();
    virtual void v1C0();
    virtual void v1C4();
    virtual void v1C8();
    virtual void v1CC();
    virtual void v1D0();
    virtual f32 v1D4(s32);
    virtual void v1D8();
    virtual void v1DC();
    virtual void v1E0();
    virtual void v1E4();
    virtual void v1E8();
    virtual void v1EC();
    virtual void v1F0();
    virtual void v1F4();
    virtual void v1F8();
    virtual void v1FC();
    virtual void v200();
    virtual void v204();
    virtual void v208();
    virtual s32 v20C();
    virtual void v210();
    virtual void v214();
    virtual void v218();
    virtual void v21C();
    virtual void v220();
    virtual void v224();
    virtual void v228();
    virtual void v22C();
    virtual void v230();
    virtual void v234();
    virtual void v238();
    virtual void v23C();
    virtual void v240();
    virtual void v244();
    virtual void v248();
    virtual void v24C();
    virtual void v250();
    virtual void v254();
    virtual void v258();
    virtual void v25C();
    virtual void v260();
    virtual void v264();
    virtual void v268();
    virtual void v26C();
    virtual void v270();
    virtual void v274();
    virtual void v278();
    virtual void v27C();
    virtual void v280();
    virtual void v284(void *);
};

typedef struct Buf130 {
    u8 pad[0x70];
} Buf130;

typedef struct BufA0 {
    u8 pad0[0x48];
    s64 m48;
    s64 m50;
    s64 m58;
    s64 m60;
    u8 pad68[0x90 - 0x68];
} BufA0;

typedef struct X4cc {
    u8 pad0[0x4CC];
    f32 m4CC;
} X4cc;

extern "C" {
s64 dpmul(s64, s64);
X4cc *ObjRecGetLiveObject_1c4a90(s32, s32);
f32 RandRangeFloat_1ca5d0(f32);
void VecCopy_1cbe30(Vec *, Vec *);
void ScreenFadeCaptureFrame_1cf550(s32);
void ScreenFadeDissolveIn_1cf720(s32, f32, s32);
void ScreenFadeReset_1cf760(s32);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
G1 *GetGameData_1fede0(void);
G2 *GetWorldDataMgr_1fedf0(void);
void CharaRequestTint_213fd0(s32, s32, s32, f32, f32, f32, f32, f32);
s32 CharaGetId_214a80(s32);
void CharaTintResetOverride_21f0b0(A *);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaGetPlacedPosMaybe_238280(s32, Vec *);
s32 CharaGetNthAttachPointPos_238580(s32, s32, s32, Vec *);
void CharaGetPos_2388a0(s32, Vec *);
void CharaGetRot_2388b0(s32, Vec *);
void GameFlowGetBattleCenter_283390(Vec *);
s32 IsInBattle_288420(void);
void DamagePopupSpawn_2d2da0(s32, s32, Vec *, Vec *, s32, s32, f32);
s32 GetDamagePopupList_2d9020(void);
void CharaPlaceAt_2f3a40(s32, Vec *, s32, f32);
void ActionResultSetupMaybe_3a6d70(BufA0 *, Buf130 *, s32, s32, s32, s32, f32);
void ActionResultClear_3a6e60(BufA0 *);
void ExecInfoInitFixedDamageMaybe_3a71d0(Buf130 *, s32, s32);
void ExecInfoInit_3a7940(Buf130 *);
void CharaUsePartySkillMaybe_3e08b0(s32, s32);
Chara *ActorFindById_3eb870(G1 *, s32);
f32 dptofp(s64);
s64 fptodp(f32);
extern s64 D_0047D190;
extern f32 D_0047E670;
extern f32 D_0047E674;
extern f32 D_0047E678;
extern f32 D_0047E67C;
extern f32 D_0045B080[];
void CharaTintUpdate_21ea90(A *a, s32 id, f32 dt);
}

void CharaTintUpdate_21ea90(A *a, s32 id, f32 dt)
{
    Vec pos;
    Vec v1A0;
    Buf130 b130;
    BufA0 bA0;
    Vec v90;
    Vec v80;
    Vec col;
    f32 old;
    f32 rr;
    Chara *o;
    Chara *o2;
    s32 k;
    Tbl *t;
    Part *p;
    f32 r;
    s32 c;
    f32 d;
    G1 *g;
    s32 s;
    s32 dd;
    X4cc *x;
    f32 h;

    old = a->fC;
    a->fC = old + dt;
    if (a->f10 <= 0.0f || a->f10 <= a->fC) {
        CharaTintResetOverride_21f0b0(a);
    }
    a->m1A = 0;
    if (a->m18 == 0) {
        o = ActorFindById_3eb870(GetGameData_1fede0(), id);
        if (o != 0) {
            k = o->v20C();
            t = GetWorldDataMgr_1fedf0()->m58->m8;
            if (t != 0) {
                p = t->v70((s16)k);
            } else {
                p = 0;
            }
            if (p != 0) {
                switch (p->m4) {
                case 4:
                    a->f1C = a->f1C + 9.0f * dt;
                case 0:
                case 1:
                case 2:
                case 3:
                case 5:
                case 6:
                case 7:
                    a->f1C = a->f1C + dt;
                    a->m1A = p->m4;
                    break;
                case 8:
                case 9:
                    r = o->v1D4(k);
                    a->f1C = a->f1C + dt * (r > 3.0f ? 1.0f : 6.0f);
                    a->m1A = p->m4;
                    break;
                }
                if (a->f1C >= 30.0f) {
                    a->f1C = a->f1C - 30.0f;
                }
            }
        }
    }
    if (a->m1A == 0) {
        a->f1C = 0.0f;
    }
    switch (a->m18) {
    case 1:
        if (old < 30.0f && 30.0f <= a->fC) {
            c = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
            if (c != 0) {
                if (IsInBattle_288420() != 0) {
                    GameFlowGetBattleCenter_283390(&pos);
                    d = D_0045B080[0];
                    rr = RandRangeFloat_1ca5d0(2.0f);
                    pos.x = pos.x + (rr - 1.0f) * d;
                    rr = RandRangeFloat_1ca5d0(2.0f);
                    pos.z = pos.z + (rr - 1.0f) * d;
                } else {
                    CharaGetPlacedPosMaybe_238280(c, &pos);
                }
                CharaGetRot_2388b0(c, &v1A0);
                CharaPlaceAt_2f3a40(CharaGetId_214a80(c), &pos, 0xF, v1A0.y);
                g = GetGameData_1fede0();
                s = GetCurrentScene_1f5be0();
                if (id == *(s16 *)(g->m18 + 0x18E)) {
                    ScreenFadeReset_1cf760(s);
                    ScreenFadeCaptureFrame_1cf550(s);
                    ScreenFadeDissolveIn_1cf720(s, 1.0f, 0xF);
                }
            }
        }
        break;
    case 2:
        if (old < 30.0f && 30.0f <= a->fC) {
            o2 = ActorFindById_3eb870(GetGameData_1fede0(), id);
            ExecInfoInit_3a7940(&b130);
            if (o2->vF0() >= 0x1E) {
                ExecInfoInitFixedDamageMaybe_3a71d0(&b130, 0x1E, 1);
                bA0.m48 = 0;
                bA0.m50 = 0;
                bA0.m58 = 0;
                bA0.m60 = 0;
                ActionResultClear_3a6e60(&bA0);
                ActionResultSetupMaybe_3a6d70(&bA0, &b130, id, -1, 0, 1, 0.0f);
                o2->v284(&bA0);
                dd = GetActionMgr_1fdb50();
                if (dd != 0) {
                    c = ActionMgrFindById_233b50(dd, id);
                    if (c != 0) {
                        CharaGetPos_2388a0(c, &v90);
                        h = 40.0f;
                        s = GetCurrentScene_1f5be0();
                        x = 0;
                        if (s != 0) {
                            x = ObjRecGetLiveObject_1c4a90(s, id);
                        }
                        if (x != 0) {
                            h = dptofp(dpmul(D_0047D190, fptodp(x->m4CC)));
                        }
                        v90.y = v90.y + h;
                        if (CharaGetNthAttachPointPos_238580(c, 0, 0, &v80) == 0) {
                            VecCopy_1cbe30(&v80, &v90);
                        }
                        col.x = D_0047E670;
                        col.y = D_0047E674;
                        col.z = D_0047E678;
                        col.w = D_0047E67C;
                        if (o2->v44() != 0) {
                            DamagePopupSpawn_2d2da0(GetDamagePopupList_2d9020(), 0x1E, &v80, &col, 0, 0, 1.25f);
                        } else {
                            DamagePopupSpawn_2d2da0(GetDamagePopupList_2d9020(), 0x1E, &v80, 0, 0, 0, 1.25f);
                        }
                    }
                    CharaRequestTint_213fd0(c, 3, 2, 250.0f, 118.0f, 80.0f, 5.0f, 1.0f);
                    CharaUsePartySkillMaybe_3e08b0(id, 0);
                }
            }
        }
        break;
    case 6:
        if (old < a->f10 / 2.0f && a->f10 / 2.0f <= a->fC) {
            a->m19 = 4;
            a->fC = 0.0f;
        }
        break;
    }
}
