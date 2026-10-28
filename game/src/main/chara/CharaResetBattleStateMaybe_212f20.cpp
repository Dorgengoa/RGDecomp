/* rgp:protos */
#line 1
#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

class Obj3F4 {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;     
         
      
    void Scale(f32 a0) { VCM(void, (void *, f32), 0x44, a0); } /* 0x44 */
    u8 pad1B4[0x464 - 0x1B4];
    s32 x464;
    u8 x468;
};

class Unit {
public:
    VC_VPTR_MEMBER;     
         
         
         
         
      void f32() { VCM0(void, 0x88); }   
         
       
    s32 IsAlive() { return VCM0(s32, 0xC0); } /* 0xC0 */
};

typedef struct Act {
    u8 pad0[0x60];
    f32 v60[4]; /* 0x60 */
    f32 v70[4]; /* 0x70 */
    u8 pad80[0x350];
    u64 x3D0; /* 0x3D0 */
    u32 x3D8; /* 0x3D8 */
    s32 x3DC; /* 0x3DC */
    u8 pad3E0[0x14];
    Obj3F4 *x3F4; /* 0x3F4 */
    u8 pad3F8[0x1A];
    s16 x412; /* 0x412 */
    u8 pad414[0x10];
    s16 x424; /* 0x424 */
    u8 pad426[0x2];
    s32 x428; /* 0x428 */
    u8 pad42C[0x44];
    f32 x470; /* 0x470 */
    f32 x474; /* 0x474 */
    f32 x478; /* 0x478 */
    f32 x47C; /* 0x47C */
    u8 pad480[0x2C];
    f32 x4AC; /* 0x4AC */
    f32 x4B0; /* 0x4B0 */
    f32 x4B4; /* 0x4B4 */
    f32 x4B8; /* 0x4B8 */
    f32 x4BC; /* 0x4BC */
    f32 x4C0; /* 0x4C0 */
    u8 pad4C4[0xC];
    u8 x4D0[0x30]; /* 0x4D0 */
    u8 x500[0x50]; /* 0x500 */
    s16 x550; /* 0x550 */
    s16 x552; /* 0x552 */
    u8 pad554[0x30];
    u8 *x584; /* 0x584 */
    s32 x588; /* 0x588 */
    u8 pad58C[0x4];
    u8 x590[0xAE]; /* 0x590 */
    s16 x63E; /* 0x63E */
    u8 pad640[0x230];
    u8 x870[0x40]; /* 0x870 */
    u8 x8B0[0x80]; /* 0x8B0 */
    u8 x930[0x20]; /* 0x930 */
    u8 x950[0x2C]; /* 0x950 */
    u8 x97C[0x30]; /* 0x97C */
    u8 x9AC[0x60]; /* 0x9AC */
    s32 xA0C; /* 0xA0C */
    u8 padA10[0x1C];
    s16 xA2C; /* 0xA2C */
    s16 xA2E; /* 0xA2E */
    u8 padA30[0x2];
    s16 xA32; /* 0xA32 */
    s16 xA34; /* 0xA34 */
    s16 xA36; /* 0xA36 */
    s16 xA38; /* 0xA38 */
    s16 xA3A; /* 0xA3A */
    s16 xA3C; /* 0xA3C */
    s16 xA3E; /* 0xA3E */
    u8 padA40[0x4];
    u32 xA44; /* 0xA44 */
    u8 padA48[0x10];
    s16 xA58; /* 0xA58 */
    s16 xA5A; /* 0xA5A */
    s16 xA5C; /* 0xA5C */
    s16 xA5E; /* 0xA5E */
    u8 padA60[0x8];
    u8 xA68; /* 0xA68 */
    u8 padA69[0x1F];
    f32 xA88; /* 0xA88 */
    u8 padA8C[0x58];
    u8 xAE4; /* 0xAE4 */
    u8 padAE5[0x1F];
    s32 xB04; /* 0xB04 */
    s32 xB08; /* 0xB08 */
    u8 padB0C[0x14];
    s32 xB20; /* 0xB20 */
    u8 padB24[0x2C];
    s16 xB50; /* 0xB50 */
    u8 padB52[0xA];
    s32 xB5C; /* 0xB5C */
    s16 xB60; /* 0xB60 */
    s16 xB62; /* 0xB62 */
} Act;


extern "C" {
void CharaSetModelObj_238700(Act *, s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GetCurrentScene_1f5be0(void);
s32 GetGameMode_1f59c0(void);
s32 StrCmpNullSafe_42cbd0(s32, char *);
void TargetRefClear_2e71d0(u8 *);
void CharaAimCtrlSetEnabled_1d8150(u8 *, s32);
void XformRecUpdateMaybe_1c5ee0(u8 *, s32);
void CharaAimCtrlUpdate_1d81b0(u8 *);
void CharaMoveReqResetThunk_2194d0(u8 *);
void CharaSquashResetThunk_219300(u8 *);
void CharaMoveReqReset_2194d0(u8 *);
void CharaSquashReset_219300(u8 *);
void CharaHitInfoInit_219140(u8 *);
void CharaExecInfoInit_219100(u8 *);
void ModelSetPos_151110(s32, f32 *);
void ModelSetRot_151080(s32, f32 *);
void AiSetState_2bbc40(u8 *, s16);
s32 AiGetScriptVm_2bb4f0(u8 *, s32);
void AiScriptRunEntry_2c1550(s32, s32, s32);
void CharaReleaseHeldTarget_2116b0(Act *, s32, f32, f32, f32);
void ActCfgTableRunEvntByName_21f680(s32, s32, char *);
long long ActCfgTableGetFlags64_223ce0(s32);
s32 ActCfgTableGetCollIgnoreMask_223cd0(s32);
void CharaSetFlags3D0_238970(Act *, long long);
void CharaSetCollIgnoreMask_238940(Act *, s32);
s32 GetCharaResMgr_1fdb60(void);
s32 CharaResSptLoadDoneMaybe_1f08f0(s32, s32);
void ModelSetScale_150ff0(Obj3F4 *, f32 *);
void ParamTableSetAlpha_1cfb10(s32, s32, f32);
void CharaResetActionState_21ea00(Act *);
void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
s32 GetGameData_1fede0(void);
Unit *ActorFindById_3eb870(s32, s32);
s32 IsInBattle_288420(void);
void CharaEnterDeathStateMaybe_217a00(Act *);
s32 GetEffectMgr_2d9040(void);
void EffectReleaseByKey_2e1260(s32, s32);
void EffectReleaseNodesByKey_2e1250(s32, s32, s32);
void CharaResetToBaseMode_21e830(Act *);
void SwordTrailStop_2d7620(u8 *);
void CharaSetVelocity_238770(Act *, f32, f32, f32);
void CharaSetSrtVec40_238760(Act *, f32, f32, f32);
void CharaPlayMotion_212590(Act *, Obj3F4 *, char *, s32, f32);
void ActCfgTableRunNormalEvntsById_2224d0(s32, s32, s32);
extern char D_0045C740[];
extern char D_0045C798[];
extern char D_0045C7A8[];
extern char D_0045CA28[];
extern char D_0045CA30[];
void CharaResetBattleStateMaybe_212f20(Act *a, s32 full);
}

extern "C" void CharaResetBattleStateMaybe_212f20(Act *a, s32 full)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 c1;
    s32 c0;
    s32 i;
    s32 p;
    Unit *u;
    u8 *q;
    Obj3F4 *o;

    CharaSetModelObj_238700(a, ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a->x424));
    a->xAE4 = 0;
    a->xB04 = 0;
    a->xB08 = 4;
    if (!(a->xA44 & 0x80000)) {
        a->xA44 &= ~0x40;
        a->xB20 = -1;
    }
    if (GetGameMode_1f59c0() == 10 && a->xA38 != 0 && StrCmpNullSafe_42cbd0(a->xA0C, D_0045C740) == 0) {
        a->v70[0] = a->x4AC;
        a->v70[1] = a->x4B0;
        a->v70[2] = a->x4B4;
        a->v70[3] = 1.0f;
        {
            f32 z = a->v70[2];
            f32 y = a->v70[1];
            f32 x = a->v70[0];
            a->x4B8 = x;
            a->x4BC = y;
            a->x4C0 = z;
        }
    }
    c1 = GetCurrentScene_1f5be0();
    c0 = GetCurrentScene_1f5be0();
    TargetRefClear_2e71d0(a->x97C);
    a->x470 = 0.0f;
    a->x474 = 0.0f;
    a->x478 = 0.0f;
    a->x47C = 1.0f;
    a->x550 = 0;
    a->x552 = 0;
    CharaAimCtrlSetEnabled_1d8150(a->x4D0, 0);
    a->xA44 &= ~0x8000;
    a->x3D0 &= 0x7FFFFFFF;
    if (full) {
        for (i = 0; i < 30; i++) {
            XformRecUpdateMaybe_1c5ee0(a->x500, c0);
            CharaAimCtrlUpdate_1d81b0(a->x4D0);
        }
    }
    CharaMoveReqResetThunk_2194d0(a->x930);
    CharaSquashResetThunk_219300(a->x950);
    p = ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a->x424);
    if (p != 0) {
        ModelSetPos_151110(p, a->v70);
        ModelSetRot_151080(p, a->v60);
    }
    if (!(a->xA44 & 0x80000) && ((a->xA44 & 0x4000000) != 0) ^ 1 && a->x63E == 200) {
        AiSetState_2bbc40(a->x590, 200);
        AiScriptRunEntry_2c1550(AiGetScriptVm_2bb4f0(a->x590, 0), 200, a->x424);
    }
    CharaReleaseHeldTarget_2116b0(a, 0, 0.0f, 0.0f, 0.0f);
    TargetRefClear_2e71d0(a->x9AC);
    a->xB5C = 0;
    a->xB60 = -1;
    a->xB62 = 0;
    if (a->x428 == 0) {
        return;
    }
    if (a->x3F4 == 0) {
        return;
    }
    a->xA2C = 0;
    ActCfgTableRunEvntByName_21f680(a->x428, a->x424, D_0045CA30);
    if (a->x428 != 0) {
        CharaSetFlags3D0_238970(a, (long long)(ActCfgTableGetFlags64_223ce0(a->x428)));
        CharaSetCollIgnoreMask_238940(a, ((short)ActCfgTableGetCollIgnoreMask_223cd0(a->x428)));
    }
    a->x3DC = 0;
    a->xA68 = 0;
    a->xA88 = 1.0f;
    if (((unsigned char)CharaResSptLoadDoneMaybe_1f08f0(GetCharaResMgr_1fdb60(), a->x424)) == 0) {
        bool b = a->xA2E == 2 || a->xA2E == 3;
        if (b) {
            a->xA2E = 0;
        }
        a->xB50 = 0;
    }
    if (a->x3F4 != 0) {
        a->xA58 = -1;
        a->xA5A = -1;
    }
    GetCurrentScene_1f5be0();
    a->xA5C = -1;
    a->xA5E = -1;
    CharaMoveReqReset_2194d0(a->x930);
    CharaSquashReset_219300(a->x950);
    CharaHitInfoInit_219140(a->x870);
    CharaExecInfoInit_219100(a->x8B0);
    o = a->x3F4;
    {
        u8 *p_ = (u8 *)v;
        u32 n_ = 0x10;
        if (p_) {
            while (n_) {
                *p_ = 0;
                n_--;
                p_++;
            }
        }
    }
    v[0] = 1.0f;
    v[1] = 1.0f;
    v[2] = 1.0f;
    ModelSetScale_150ff0(o, v);
    switch (a->xA36) {
    case 0x1E:
    case 0x1F:
        ParamTableSetAlpha_1cfb10(c1, a->x424, 1.0f);
        a->xA44 &= ~0x800000;
        CharaResetActionState_21ea00(a);
        break;
    }
    switch (a->xA32) {
    case 0:
    case 1:
    case 2:
    case 3:
        switch (a->xA34) {
        case 0:
        case 2:
        case 1:
            a->xA34 = -1;
            break;
        }
        break;
    case 5:
        a->xA34 = -1;
        break;
    case 0x12:
        ParamTableSetAlpha_1cfb10(c1, a->x424, 1.0f);
        ObjRecClearFlags_1c3dc0(c1, 1, a->x424, 0xA0030);
        a->xA44 &= ~0x800000;
        break;
    }
    a->xA3A = -1;
    a->xA3E = -1;
    a->xA3C = 0;
    a->x412 = 0;
    a->x3D8 &= ~0x10;
    a->x3D8 &= ~0x20;
    a->x3D8 &= ~0x40;
    a->x3D8 &= ~0x80;
    a->xA44 &= ~0x800000;
    u = ActorFindById_3eb870(GetGameData_1fede0(), a->x424);
    if (((unsigned char)IsInBattle_288420()) != 0 && a->xA32 == 0x11 && a->xA34 != 0x14 && u != 0 && u->IsAlive()) {
        CharaEnterDeathStateMaybe_217a00(a);
    } else {
        if (a->xA32 == 0x11) {
            EffectReleaseByKey_2e1260(GetEffectMgr_2d9040(), a->x424);
            if (a->x428 != 0) {
                switch (a->xA2C) {
                case 1:
                    ActCfgTableRunEvntByName_21f680(a->x428, a->x424, D_0045C798);
                    break;
                default:
                    ActCfgTableRunEvntByName_21f680(a->x428, a->x424, D_0045C7A8);
                    break;
                }
            }
        }
        CharaResetToBaseMode_21e830(a);
        EffectReleaseNodesByKey_2e1250(GetEffectMgr_2d9040(), a->x424, 3000);
        if (a->x3F4 != 0) {
            a->xA58 = -1;
            a->xA5A = -1;
        }
        q = a->x584;
        if (q != 0) {
            for (i = 0; i < a->x588; i++, q += 0xB8) {
                TargetRefClear_2e71d0(q + 0x30);
                TargetRefClear_2e71d0(q + 0x60);
                SwordTrailStop_2d7620(q);
            }
        }
        CharaSetVelocity_238770(a, 0.0f, 0.0f, 0.0f);
        CharaSetSrtVec40_238760(a, 0.0f, 0.0f, 0.0f);
        if (a->x424 >= 0 && a->x424 < 12) {
            CharaPlayMotion_212590(a, a->x3F4, D_0045CA28, 4, 1.0f);
            a->x3F4->Scale(1.0f);
        }
        if (a->x428 != 0) {
            ActCfgTableRunNormalEvntsById_2224d0(a->x428, a->x424, a->xA32);
        }
    }
    o = a->x3F4;
    o->x464 = 0x1F;
    o->x468 = 1;
    if (!full) {
        c0 = GetCurrentScene_1f5be0();
        XformRecUpdateMaybe_1c5ee0(a->x500, c0);
        CharaAimCtrlUpdate_1d81b0(a->x4D0);
    }
}
