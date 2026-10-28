/* rgp:protos */
#line 1
#include "types.h"

class Fp216 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vE8() { return VCM0(s32, 0xE8); }
};

class Mgr216 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v274(s32 a0) { return VCM(s32, (void *, s32), 0x274, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Fp216 * v384(s32 a0) { return VCM(Fp216 *, (void *, s32), 0x384, a0); }
    
    
    
    
    
    
    
    
    
    s32 v3AC() { return VCM0(s32, 0x3AC); }
};

typedef struct Obj216 {
    u8 pad0[0x3D8];
    s32 m3D8;
    u8 pad3DC[0x428 - 0x3DC];
    s32 m428;
    s32 m42C;
    u8 pad430[0x570 - 0x430];
    s64 m570;
    u8 pad578[0xA0C - 0x578];
    s32 mA0C;
    u8 padA10[0xA32 - 0xA10];
    s16 mA32;
    s16 mA34;
    s16 mA36;
    s16 mA38;
    u8 padA3A[0xAAC - 0xA3A];
    u8 mAAC[0xB44 - 0xAAC];
    s16 mB44;
    s16 mB46;
} Obj216;

typedef struct Pair216 {
    u32 a;
    u32 b;
} Pair216;

typedef struct Ent216 {
    u8 pad0[4];
    Pair216 m4;
} Ent216;

typedef struct Res216 {
    Ent216 *m0;
    f32 m4;
} Res216;

typedef struct Bits216 {
    u8 pad0[0x24C];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 5;
} Bits216;

typedef struct Sub216 {
    u8 pad0[0x18E];
    s16 m18E;
} Sub216;

typedef struct Sys216 {
    u8 pad0[0x14];
    s32 m14;
    Sub216 *m18;
    u8 pad1C[4];
    Bits216 *m20;
} Sys216;

extern "C" {
void GameSceneSoundSlot5PlaySeVol_1d05d0(s32, s32, f32);
void GameSceneSoundSlot0PlaySeVol_1d05f0(s32, s32, f32);
s32 GetCurrentScene_1f5be0(void);
Sys216 *GetGameData_1fede0(void);
s32 FieldHudWidget86IsOpen_203fd0(void);
void FieldHudWidget86Open_203fe0(void);
void FieldHudWidget83Close_203ff0(void);
s32 FieldHudWidget83IsOpen_204000(void);
void FieldHudWidget83Open_204010(void);
void FieldHudPartyPanelShakeStart_204060(s32);
s32 GetHpGauge_206210(void);
s32 CharaCanStartAction_210300(void *);
s32 CharaIsGroundReadyMaybe_210850(Obj216 *);
s32 CharaHasMotion_212510(Obj216 *, s32);
s32 CharaGetId_214a80(Obj216 *);
void CharaActionUpdateMaybe_215ca0(Obj216 *, s32 *);
s32 CharaStartActionByName_216d90(Obj216 *, s32, u64, f32);
Res216 *ActCfgTableFindCnctByMask_220950(s32, s32, s32, s64, f32);
Res216 *ActCfgTableFindNormalCnctByMask_220d10(s32, s32, s32, s64, f32);
s32 ActCfgTableResolveActionAlias_223730(s32, s32, s32, u8 *, s32);
s32 ActCfgTableFindActionByName_223d20(s32, s32);
s32 CharaTableGetStepArray_225470(s32);
s32 CharaTableGetName_225480(s32);
s32 CharaTableGetActionKind_225d30(s32);
s32 CharaTableDataGetMotionName_2269e0(s32);
s32 ActDataCnctGetCmndName_227490(Res216 *);
f32 CharaGetHeightAboveGround_238380(Obj216 *);
s32 CharaGetCurMotionName_238560(Obj216 *);
f32 CharaGetMotionFrame_238570(Obj216 *);
void HpGaugeSetHop_31d290(s32, s32, s32);
Mgr216 *CharaMgrPoolFindById_3a8c60(s32, s32);
void CharaActFailCountReset_3b6450(s32);
void CharaActFailCountInc_3b6460(s32);
s32 CharaActFailCountGet_3b6480(s32);
void LeaderHudWeaponShakeStartThunk_507400(void);
extern f32 D_0045B080[];
s32 CharaTryStartAction_216700(Obj216 *arg0, s32 *arg1);
}

s32 CharaTryStartAction_216700(Obj216 *arg0, s32 *arg1)
{
    s32 st;
    s32 snd;
    Ent216 *e;
    f32 f;
    Fp216 *fp;
    s32 sel;
    s32 v;
    Res216 *res;
    bool b;
    s32 k;
    Mgr216 *m;
    Sys216 *sys;
    s32 n;
    s32 id;

    if (CharaCanStartAction_210300((void *)arg0) == 0) {
        return 0;
    }
    arg0->m42C = 0;
    if (arg0->mA38 != 0) {
        k = CharaGetCurMotionName_238560(arg0);
        f = CharaGetMotionFrame_238570(arg0);
        res = ActCfgTableFindCnctByMask_220950(arg0->m428, arg0->mA0C, k, arg0->m570, f);
    } else {
        k = CharaGetCurMotionName_238560(arg0);
        f = CharaGetMotionFrame_238570(arg0);
        res = ActCfgTableFindNormalCnctByMask_220d10(arg0->m428, arg0->mA32, k, arg0->m570, f);
    }
    if (res == 0) {
        return 0;
    }
    st = ActCfgTableFindActionByName_223d20(arg0->m428, ActCfgTableResolveActionAlias_223730(arg0->m428, arg0->mB44, arg0->mB46, arg0->mAAC, ActDataCnctGetCmndName_227490(res)));
    if (st == 0) {
        return 0;
    }
    if (((short)CharaTableGetActionKind_225d30(st)) == 9 || ((short)CharaTableGetActionKind_225d30(st)) == 10) {
        if (arg0->mA36 != 2 && arg0->mA36 != 9 && arg0->mA36 != 10) {
            return 0;
        }
        if (CharaIsGroundReadyMaybe_210850(arg0) != 0) {
            return 0;
        }
        if (((short)CharaTableGetActionKind_225d30(st)) != 9 && ((short)CharaTableGetActionKind_225d30(st)) != 10) {
            return 0;
        }
        if (arg0->mA38 == 0) {
            switch (arg0->mA34) {
            case 1:
                if ((arg0->m3D8 & 4) && CharaGetHeightAboveGround_238380(arg0) <= D_0045B080[0]) {
                    return 0;
                }
                break;
            case 0:
                break;
            default:
                return 0;
            }
        } else {
            if ((arg0->m3D8 & 4) && CharaGetHeightAboveGround_238380(arg0) <= D_0045B080[0]) {
                return 0;
            }
        }
    }
    v = CharaTableGetStepArray_225470(st);
    if (v == 0) {
        return 0;
    }
    if (CharaHasMotion_212510(arg0, CharaTableDataGetMotionName_2269e0(v)) == 0) {
        return 0;
    }
    sys = GetGameData_1fede0();
    id = sys->m18->m18E;
    if (id == ((short)CharaGetId_214a80(arg0))) {
        m = CharaMgrPoolFindById_3a8c60(sys->m14, ((short)CharaGetId_214a80(arg0)));
        if (m != 0) {
        sel = -1;
        switch (((short)CharaTableGetActionKind_225d30(st))) {
        case 7:
        case 9:
        case 12:
            sel = 0;
            break;
        case 8:
        case 10:
            sel = 1;
            break;
        case 13:
        case 14:
            if (((short)CharaGetId_214a80(arg0)) != 6) {
                sel = 0;
            } else {
                sel = 1;
            }
            break;
        case 11:
            sel = 0;
            if (m->v274(0) == 0) {
                return 0;
            }
            if (*arg1 != 0) {
                CharaActFailCountReset_3b6450(*arg1);
                FieldHudWidget83Close_203ff0();
            }
            break;
        }
        if (sel >= 0) {
            fp = m->v384(sel);
            snd = -1;
            b = (((short)CharaGetId_214a80(arg0)) != 6 && sel == 1) || (((short)CharaGetId_214a80(arg0)) == 6 && sel != 1);
            if (b && (fp->vE8() == 0 || m->v274(sel) == 0)) {
                if (m->v3AC() == 0 && FieldHudWidget86IsOpen_203fd0() == 0) {
                    FieldHudWidget86Open_203fe0();
                }
                LeaderHudWeaponShakeStartThunk_507400();
                snd = 0x52;
                if (((short)CharaGetId_214a80(arg0)) == 1 && sel == 1) {
                    snd = 0x53;
                }
                GameSceneSoundSlot5PlaySeVol_1d05d0(GetCurrentScene_1f5be0(), snd, 1.0f);
                switch (((short)CharaGetId_214a80(arg0))) {
                case 2:
                case 1:
                case 7:
                case 6:
                    return 0;
                }
            }
            if (m->v274(sel) == 0) {
                if (snd < 0) {
                    GameSceneSoundSlot0PlaySeVol_1d05f0(GetCurrentScene_1f5be0(), 0x2B, 1.0f);
                }
                FieldHudPartyPanelShakeStart_204060(((short)CharaGetId_214a80(arg0)));
                n = GetHpGauge_206210();
                HpGaugeSetHop_31d290(n, ((short)CharaGetId_214a80(arg0)), 5);
                if (sys->m20->b2 != 0 && *arg1 != 0) {
                    if (FieldHudWidget83IsOpen_204000() != 0) {
                        CharaActFailCountReset_3b6450(*arg1);
                    } else {
                        CharaActFailCountInc_3b6460(*arg1);
                        if (((short)CharaActFailCountGet_3b6480(*arg1)) >= 3) {
                            CharaActFailCountReset_3b6450(*arg1);
                            FieldHudWidget83Open_204010();
                            sys->m20->b2 = 0;
                        }
                    }
                }
                return 0;
            }
            if (*arg1 != 0) {
                CharaActFailCountReset_3b6450(*arg1);
                FieldHudWidget83Close_203ff0();
            }
        }
        }
    }
    e = res->m0;
    if (CharaStartActionByName_216d90(arg0, CharaTableGetName_225480(st), ((u64)e->m4.b << 32) | e->m4.a, res->m4) == 0) {
        return 0;
    }
    CharaActionUpdateMaybe_215ca0(arg0, arg1);
    return 1;
}
