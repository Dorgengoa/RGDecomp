#include "types.h"
#pragma divbyzerocheck on

typedef struct Pt {
    u8 pad0[0xC];
    f32 mC;
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    u8 pad20[0x204];
} Pt;

typedef struct Obj {
    Pt *m0;
    s16 m4;
    s16 pad6;
    s16 m8;
    s16 mA;
    s16 mC;
    s16 mE;
    s32 m10;
    f32 m14;
    s32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    s8 m2C;
} Obj;

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);
extern s32 IsWidescreen_1c6ab0(void);
extern void ParamTableSetAlpha_1cfb10(s32, s32, f32);
extern f32 ParamTableGetAlpha_1cfb40(s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern void GetGameData_1fede0(void);
extern void CharaInvokeInitBt1_212ad0(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 GameFlowGetChainTargetId_285f40(void);
extern s32 GameFlowGetChainCharaId_285f50(void);
extern void AttackChainMarkersShow_382c40(Obj *);
extern s32 AttackChainGetPhase_382eb0(Obj *);
extern void func_4F6BF0(void *, s32);
extern u8 D_00527020[];

void AttackChainStartMaybe_382910(Obj *o, s32 kind, f32 t)
{
    f32 ang[12];
    s16 idx[16];
    Pt *p;
    s32 i;
    s32 n;
    s32 h;
    s32 e;
    s32 half;
    f32 cx;
    f32 cy;
    f32 sc;

    if (o->m0 == 0) return;
    if (AttackChainGetPhase_382eb0(o) != 1) return;
    o->mA = 0;
    o->mC = 0;
    o->mE = 0;
    o->m10 = 0;
    o->m2C = kind;
    o->m14 = t;
    o->m18 = 0;
    o->m1C = -1.0f;
    o->m20 = -1.0f;
    o->m24 = -1.0f;
    GetGameData_1fede0();
    func_4F6BF0(D_00527020, o->m4);
    AttackChainMarkersShow_382c40(o);
    h = GetDrawCtx_15de80();
    cx = 0.5f * DrawEnvGetWidth_1451e0(h);
    cy = 0.5f * DrawEnvGetHeight_1451d0(h);
    if (IsWidescreen_1c6ab0() != 0) {
        sc = 0.75f;
    } else {
        sc = 1.0f;
    }
    n = o->m4;
    half = (s16)((n - 1) >> 1);
    for (i = 0; i < n; i++) {
        ang[i] = 6.2831855f * i / *(volatile s16 *)&o->m4 - 3.1415927f;
        idx[i] = i * half % n;
    }
    p = o->m0;
    for (i = 0; i < o->m4; i++, p++) {
        p->m18 = -1.0f;
        p->m1C = -1.0f;
        if (p->mC < 0.0f || p->m10 < 0.0f) {
            p->m14 = ang[idx[i]];
            p->mC = cx + sc * (64.0f * Cosf_128d30(p->m14));
            p->m10 = cy + 1.1666666f * (64.0f * Sinf_128fd0(p->m14));
        }
    }
    e = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), GameFlowGetChainCharaId_285f50());
    if (e != 0) CharaInvokeInitBt1_212ad0(e);
    h = GetCurrentScene_1f5be0();
    o->m28 = ParamTableGetAlpha_1cfb40(h, GameFlowGetChainTargetId_285f40());
    ParamTableSetAlpha_1cfb10(h, GameFlowGetChainTargetId_285f40(), 1.0f);
    o->m8 = 2;
}
