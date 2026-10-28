/* rgp:protos */
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    f32 x, y, z, w;
} Vec;

typedef struct {
    u8 pad0[0x60];
    Vec f60;
    Vec f70;
    u8 pad80[0x350];
    u64 f3D0;
    u32 f3D8;
    u8 pad3DC[0x18];
    s32 f3F4;
    f32 f3F8;
    f32 f3FC;
    s32 f400;
    s32 f404;
    u8 pad408[0x1C];
    s16 f424;
    u8 pad426[2];
    s32 f428;
    u8 pad42C[0x54];
    Vec f480;
    u8 pad490[0x40];
    u8 f4D0[0x30];
    u8 f500[0x5A];
    s16 f55A;
    s16 f55C;
    u8 pad55E[0xA];
    u64 f568;
    u8 pad570[0x3B0];
    u8 f920;
    u8 pad921[0x3B];
    u8 f95C[0xB0];
    s32 fA0C;
    u8 padA10[0x1C];
    s16 fA2C;
    s16 fA2E;
    u8 padA30[2];
    s16 fA32;
    u8 padA34[2];
    s16 fA36;
    s16 fA38;
    u8 padA3A[0xA];
    u32 fA44;
    u8 padA48[0x20];
    char fA68[0x20];
    f32 fA88;
    u8 padA8C[0x40];
    f32 fACC;
    f32 fAD0;
    u8 padAD4[8];
    f32 fADC;
    u8 padAE0[0x6C];
    s16 fB4C;
    u8 padB4E[2];
    s16 fB50;
    u8 padB52[2];
    f32 fB54;
    f32 fB58;
    s32 fB5C;
    s16 fB60;
    s16 fB62;
} Chr;

typedef struct {
    u8 pad0[4];
    f32 f4;
} Step;

typedef struct {
    f32 x, y, z;
} Vec3;

typedef struct {
    u8 pad0[0x18];
    struct {
        u8 pad0[0x18E];
        s16 f18E;
    } *f18;
} Ctx;

typedef struct {
    s32 h;
    s32 j;
} Pair;

extern "C" {
char *strcpy(char *, const char *);
f32 Atan2f_1291a8(f32, f32);
void ModelSetRot_151080(s32, Vec *);
void ModelSetPos_151110(s32, Vec *);
s32 ModelGetFrame_1511f0(s32, s32);
s32 ModelFindFrameIndexByName_151220(s32, s32);
u32 ObjRecGetFlags_1c3d90(s32, s32, s32);
void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
s32 ObjRecHasFlags6_1c3eb0(s32, s32, s32);
void XformRecSetNameMaybe_1c6950(u8 *, const char *);
f32 VecDistSqXZ_1cb390(Vec *, Vec *);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
void VecSubAsPoint_1cbcc0(Vec *, Vec *, Vec *);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
s32 ObjIdResolveAlias_1ce490(s32, s32);
void ParamTableFadeToOne_1cf9e0(s32, s32, s32);
void ParamTableSetAlpha_1cfb10(s32, s32, f32);
void GameSceneSoundSlot5PlaySeVol_1d05d0(s32, s32, f32);
void CharaAimCtrlSetNode_1d8180(u8 *, s32);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
Ctx *GetGameData_1fede0(void);
s16 CharaSelectStateFromFlagsMaybe_20e9f0(Chr *, u64);
void CharaResetBattleStateMaybe_212f20(Chr *, s32);
void CharaActionUpdateMaybe_215ca0(Chr *, Step *);
void CharaStartActionByName_216d90(Chr *, char *, long long, f32);
void CharaActDeath_216f60(Chr *, Step *);
void CharaActBlownAway_217de0(Chr *, Step *, int, int);
void CharaActDamage_218880(Chr *, Step *, int, int);
void CharaActLadder_2198e0(Chr *, Step *);
void CharaActHang_21a890(Chr *, Step *);
void CharaActSwim_21aeb0(Chr *, Step *);
void CharaActMoveMotion_21b180(Chr *, Step *);
void CharaActBattleInOut_21bbf0(Chr *, Step *);
void CharaActAppear_21c1f0(Chr *, Step *);
void CharaActLoco_21cc10(Chr *, Step *);
void CharaResetToBaseMode_21e830(Chr *);
void CharaTintRequest_21f0e0(u8 *, s32, s32, f32, f32, f32, f32, f32);
void ActCfgTableRunEvntByName_21f680(s32, s32, const char *);
char *ActCfgTableFindCallNameByFlags_2207b0(s32, s32, u64);
s32 ActCfgTableGetNullNameById_223ab0(s32, s32, s32);
s32 ActionMgrFindById_233b50(s32, s32);
f32 CharaGetHeightAboveGround_238380(Chr *);
void CharaSetPlatformVelXYZMaybe_2384a0(Chr *, f32, f32, f32);
void CharaSetPlatformVelMaybe_2384c0(Chr *, Vec *);
void CharaGetPlatformVelMaybe_2384e0(Chr *, Vec *);
f32 CharaGetCollWidth_238640(s32);
void CharaSetPosVec_2387e0(Chr *, Vec *);
s32 CharaGetCollIgnoreMask_238950(Chr *);
void CharaGetPos_2388a0(s32, Vec *);
u32 IsInBattle_288420(void);
void EventObjMgrMovePosOutOfVolumesMaybe_2d0740(Vec *, f32);
s32 StrCmpNullSafe_42cbd0(s32, const char *);
void SrtSetPosFromVecThunk_1c7410(Chr *, Vec *);

extern char D_0045C740[];
extern char D_0045C750[];
extern char D_0045C758[];
extern char D_0045C768[];
extern char D_0045C778[];
extern char D_0045C780[];
extern char D_0045C788[];
extern char D_0045C790[];
extern char D_0045C798[];
extern char D_0045C7A8[];
extern char D_0045C7B8[];
extern char D_0045C7C8[];
extern f32 D_0045B078[];
extern f32 D_0045B080[];
extern f32 D_0047DB20;
}

static inline void Set4(Vec *v, f32 x, f32 y, f32 z, f32 w) {
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

static inline bool Alive(Chr *c) {
    return !(c->fA44 & 0x80000000);
}

static inline bool Pair23(s32 a) {
    return a == 2 || a == 3;
}

static inline bool CanMotion(Chr *c) {
    s32 a;
    bool b3;

    switch (c->fA36) {
    case 0xF:
    case 0x13:
    case 0x1E:
    case 0x1F:
        return false;
    }
    if (c->fA38 == 0) {
        switch (c->fA32) {
        case 0xA:
        case 0x12:
            return false;
        }
    }
    a = c->fA2E;
    b3 = true;
    if (a != 2 && a != 3) b3 = false;
    if (!b3) {
        switch (c->fB4C) {
        case 1:
        case 2:
            return false;
        }
    }
    if (Pair23(a)) {
        switch (c->fB50) {
        case 2:
        case 3:
            return false;
        }
    }
    return true;
}

static inline bool NoAnim(Chr *c) {
    return !(c->fA44 & 0x40);
}

static inline bool NoFlag(Chr *c) {
    return !(c->f3D0 & 0x0800000000000000ULL);
}

static inline bool HasTarget(Chr *c) {
    return c->fB60 >= 0 && c->fB5C != 0;
}

static inline void Load(Chr *c) {
    s32 m;
    s32 r;

    r = ActCfgTableGetNullNameById_223ab0(c->f428, 4, 0);
    m = c->f3F4;
    CharaAimCtrlSetNode_1d8180(c->f4D0, ModelGetFrame_1511f0(m, ModelFindFrameIndexByName_151220(m, r)));
    c->f55A = c->f424;
    c->f55C = -1;
    XformRecSetNameMaybe_1c6950(c->f500, D_0045C750);
    ModelSetPos_151110(c->f3F4, &c->f70);
    ModelSetRot_151080(c->f3F4, &c->f60);
}

static inline void Voice(Chr *c, const char *a, const char *b) {
    if (c->f428 != 0) {
        switch (c->fA2C) {
        case 1:
            ActCfgTableRunEvntByName_21f680(c->f428, c->f424, a);
            break;
        default:
            ActCfgTableRunEvntByName_21f680(c->f428, c->f424, b);
            break;
        }
    }
}

extern "C" void CharaActDispatch_20d190(Chr *c, Step *st) {
    Vec vD0 __attribute__((aligned(16)));
    Pair list[4] __attribute__((aligned(16)));
    s32 w;
    s32 id;
    s32 n;
    s32 k;
    s32 j;
    s32 h;
    s32 o;
    s32 w2;
    bool near;
    bool b16;
    char *nm;
    Ctx *ctx;
    f32 f20;

    if (!Alive(c)) return;
    w = GetCurrentScene_1f5be0();
    if (st == 0) return;
    c->fB54 -= st->f4;
    if (c->fB54 < 0.0f) c->fB54 = 0.0f;
    c->fB58 -= st->f4;
    if (c->fB58 < 0.0f) c->fB58 = 0.0f;
    if (c->fA36 == 0x15) c->fA68[0] = 0;
    if (c->fA36 == 0x16) c->fA68[0] = 0;
    if (c->fA36 == 0x17) c->fA68[0] = 0;
    if (c->f3F4 == 0) return;
    if (c->f428 == 0) return;
    if (c->fA44 & 0x10000000) {
        c->f568 = 0;
        return;
    }
    if (c->fA38 != 0) {
        if (StrCmpNullSafe_42cbd0(c->fA0C, D_0045C740) == 0) c->f568 &= 0xFFE83003FFFFFFFFULL;
    }
    c->f568 &= 0x9FFFFFFFFFFFF7FBULL;
    if (c->f568 & 0x0040000000000000ULL) {
        f20 = c->fADC;
        c->fADC = f20 + st->f4;
        if (!(c->fADC <= 300.0f)) c->fADC = 300.0f;
        if (!(c->fADC <= 8.0f)) c->f568 |= 0x2000000000000000ULL;
        if (c->fA36 == 11) {
            if ((c->f568 & 0x0040000000000000ULL) && !(c->fADC < 10.0f) && !(10.0f <= f20)) {
                CharaTintRequest_21f0e0(c->f95C, 5, 2, 250.0f, 250.0f, 250.0f, 30.0f, 1.0f);
                GameSceneSoundSlot5PlaySeVol_1d05d0(w, 0x4E, 1.0f);
            }
        }
    } else {
        if (!(c->fADC < 10.0f)) c->f568 |= 0x4000000000000000ULL;
        c->fADC = 0.0f;
    }
    if (c->f920) c->f568 |= 0x20000000;
    if (c->f568 & 0x10003) c->f568 |= 0x8000;
    if (!(c->f568 & 3)) c->f568 |= 4;
    CharaGetPlatformVelMaybe_2384e0(c, &vD0);
    if (!(c->f3D8 & 4) || !(CharaGetHeightAboveGround_238380(c) <= D_0047DB20 * (f32)D_0045B080[0])) {
        CharaSetPlatformVelXYZMaybe_2384a0(c, 0.0f, 0.0f, 0.0f);
    }
    c->fA32 = CharaSelectStateFromFlagsMaybe_20e9f0(c, c->f568);
    if (c->fA32 != 4) {
        Set4(&c->f480, c->f70.x, c->f70.y, c->f70.z, 1.0f);
    } else if (!(c->f480.y <= c->f70.y)) {
        c->f480.y = c->f70.y;
    }
    b16 = false;
    nm = 0;
    if (NoAnim(c)) nm = ActCfgTableFindCallNameByFlags_2207b0(c->f428, c->fA2E, c->f568);
    if (nm != 0) {
        c->fA68[0] = 0;
        c->fA88 = 1.0f;
        if (nm != 0) {
            strcpy(c->fA68, nm);
            c->fA88 = 1.0f;
        }
        b16 = true;
    } else if (c->fA68[0] != 0) {
        if (CanMotion(c)) {
            switch (c->fA32) {
            case 0xF:
            case 0x10:
                if (c->fA44 & 0x1000000) break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                b16 = true;
                break;
            }
        }
    }
    if (b16) {
        CharaStartActionByName_216d90(c, c->fA68, (long long)(0), c->fA88);
        c->fA68[0] = 0;
    }
    if (c->fA38 == 0) {
        switch (c->fA32) {
        case 0:
        case 1:
        case 2:
        case 3:
            CharaActLoco_21cc10(c, st);
            break;
        case 10:
            CharaActBattleInOut_21bbf0(c, st);
            break;
        case 4:
            CharaActMoveMotion_21b180(c, st);
            break;
        case 5:
            CharaActSwim_21aeb0(c, st);
            break;
        case 6:
            CharaActHang_21a890(c, st);
            break;
        case 7:
            CharaActLadder_2198e0(c, st);
            break;
        case 15:
            CharaActDamage_218880(c, st, 0, 0);
            break;
        case 16:
            CharaActBlownAway_217de0(c, st, 0, 0);
            break;
        case 18:
            CharaActAppear_21c1f0(c, st);
            break;
        case 17:
            CharaActDeath_216f60(c, st);
            c->f3D0 |= 0x4000000000000000ULL;
            break;
        default:
            c->fA2E = 0;
            CharaResetToBaseMode_21e830(c);
            CharaActLoco_21cc10(c, st);
            break;
        }
    } else {
        CharaActionUpdateMaybe_215ca0(c, st);
    }
    if (c->fACC < 1000000) c->fACC += st->f4;
    if (c->fAD0 < 1000000) c->fAD0 += st->f4;
    switch (c->fA32) {
    case 0:
    case 1:
    case 2:
    case 3:
        if (NoFlag(c) || !(c->f3D8 & 0x20)) {
            c->f3D0 |= 0x4000000000000000ULL;
        }
        break;
    case 7:
        c->f3D0 |= 0x0000002000000000ULL;
        c->f3D0 &= 0xBFFFFFFFFFFFFFFFULL;
        c->f3D0 |= 0x0000080000000000ULL;
        c->f3D0 |= 0x0000400000000000ULL;
        c->f3D0 |= 0x0000040000000000ULL;
        c->f3D0 |= 0x0000020000000000ULL;
        c->f3D0 |= 0x0000010000000000ULL;
        c->f3D0 |= 0x0000100000000000ULL;
        break;
    case 0xF:
    case 0x10:
    case 0x11:
        break;
    }
    if (c->fA44 & 0x20000) c->f3D0 |= 0x0000400000000000ULL;
    id = c->f424;
    if (id >= 0 && id < 12) {
        s32 arr[4] __attribute__((aligned(16))) = {-10, -11, -20, -21};

        n = 0;
        if (ObjRecGetFlags_1c3d90(w, 1, c->f424) & 0x800000) {
            for (k = 0; k < 4; k++) {
                j = *(s32 *)((u32)&arr[k]);
                h = ObjIdResolveAlias_1ce490(c->f424, j);
                if (((unsigned char)ObjRecHasFlags6_1c3eb0(w, 1, h)) == 0) continue;
                if (ObjRecGetFlags_1c3d90(w, 1, h) & 0x800000) continue;
                list[n].h = h;
                list[n].j = j;
                n++;
            }
        } else {
            ObjRecSetFlags_1c3e00(w, 1, c->f424, 0x800000);
            EventObjMgrMovePosOutOfVolumesMaybe_2d0740(((void)(((short)CharaGetCollIgnoreMask_238950(c))), &c->f70), 0.0f);
            CharaSetPosVec_2387e0(c, &c->f70);
            SrtSetPosFromVecThunk_1c7410(c, &c->f70);
            if (((unsigned char)IsInBattle_288420()) == 0 && c->f424 >= 0 && c->f424 < 12) {
                ctx = GetGameData_1fede0();
                if (ctx->f18->f18E != c->f424) {
                    s32 m_ = GetActionMgr_1fdb50();
                    o = ActionMgrFindById_233b50(m_, ctx->f18->f18E);
                    if (o != 0) {
                        Vec v90 __attribute__((aligned(16)));
                        Vec v80 __attribute__((aligned(16)));

                        CharaGetPos_2388a0(o, &v90);
                        near = false;
                        if (HasTarget(c) && (c->fB62 & 3)) {
                            near = true;
                        } else {
                            f20 = D_0045B080[0]; f20 = 10.0f * (volatile f32)f20;
                            if (!(VecDistSqXZ_1cb390(&v90, &c->f70) <= f20 * f20)) near = true;
                        }
                        if (near) {
                            VecSub_1cbd00(&v80, &v90, &c->f70);
                            VecScaleToLength_1cb510(&v80, &v80, 0.5f * CharaGetCollWidth_238640(o));
                            VecSubAsPoint_1cbcc0(&c->f70, &v90, &v80);
                            c->f60.y = Atan2f_1291a8(v80.x, v80.z);
                        }
                    }
                }
            }
            Load(c);
            CharaResetBattleStateMaybe_212f20(c, 1);
            Voice(c, D_0045C758, D_0045C768);
            w2 = GetCurrentScene_1f5be0();
            ParamTableSetAlpha_1cfb10(w2, c->f424, 0.0f);
            ParamTableFadeToOne_1cf9e0(w2, c->f424, (s32)(0.5f * D_0045B078[0]));
        }
        if (n > 0) {
            for (k = 0; k < n; k++) {
                h = *(s32 *)((u32)&list[k]);
                if (((unsigned char)ObjRecHasFlags6_1c3eb0(w, 1, h)) == 0) continue;
                k = (s32)k;
                Pair *p_ = &list[k];
                k = (s32)k;
                ObjRecSetFlags_1c3e00(w, 1, h, 0x800000);
                switch (p_->j) {
                case -0xA:
                    ActCfgTableRunEvntByName_21f680(c->f428, c->f424, D_0045C778);
                    break;
                case -0xB:
                    ActCfgTableRunEvntByName_21f680(c->f428, c->f424, D_0045C780);
                    break;
                case -0x14:
                    ActCfgTableRunEvntByName_21f680(c->f428, c->f424, D_0045C788);
                    break;
                case -0x15:
                    ActCfgTableRunEvntByName_21f680(c->f428, c->f424, D_0045C790);
                    break;
                }
            }
            switch (c->fA2E) {
            case 0:
                Voice(c, D_0045C758, D_0045C768);
                break;
            case 2:
                Voice(c, D_0045C798, D_0045C7A8);
                break;
            case 3:
                Voice(c, D_0045C7B8, D_0045C7C8);
                break;
            }
        }
    } else if (!(ObjRecGetFlags_1c3d90(w, 1, c->f424) & 0x800000)) {
        ObjRecSetFlags_1c3e00(w, 1, c->f424, 0x800000);
        Load(c);
        Voice(c, D_0045C758, D_0045C768);
    }
    if (c->f3D0 & 0x4000000000000000ULL) CharaSetPlatformVelMaybe_2384c0(c, &vD0);
    c->f3F8 = c->f3FC;
    c->f400 = c->f404;
}
