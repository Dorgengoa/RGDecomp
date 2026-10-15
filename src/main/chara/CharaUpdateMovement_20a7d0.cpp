#include "types.h"
#pragma divbyzerocheck on

typedef unsigned __int128 u128;

typedef struct Vec {
    f32 x, y, z, w;
} __attribute__((aligned(16))) Vec;

typedef struct Mat {
    Vec a, b, c, d;
} Mat;

typedef struct {
    f32 a, b;
} Seg;

typedef struct {
    s8 on;
} Trig;

typedef struct {
    u8 pad0[0x4F0];
    s32 f4F0;
    s32 f4F4;
    u8 pad4F8[4];
    s32 f4FC;
    u8 pad500[0x10];
    s32 f510;
} Obj;

typedef struct {
    u8 pad0[4];
    f32 f4;
    f32 f8;
    f32 fC;
} Mo;

typedef struct {
    u8 pad0[0x42];
    s16 f42;
} Anm;

typedef struct {
    u8 pad0[0x32];
    s16 f32;
} Tgt;

typedef struct {
    u8 pad0[0x46];
    s16 f46;
    u8 pad48[0x18];
} Col;

typedef struct {
    u8 pad0[8];
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[4];
    s32 f20;
    Col *f24;
    s32 f28;
    u8 pad2C[8];
    s32 f34;
    s32 f38;
} St;

typedef struct {
    u8 pad0[0x18];
    struct {
        u8 pad0[0x18E];
        s16 f18E;
    } *f18;
} Ctx;

typedef struct Chr {
    u8 pad0[0x24];
    f32 f24;
    u8 pad28[0x48];
    Vec f70;
    Vec f80;
    u8 pad90[4];
    f32 f94;
    u8 pad98[0x338];
    u64 f3D0;
    u32 f3D8;
    f32 f3DC;
    u8 pad3E0[0x14];
    Obj *f3F4;
    f32 f3F8;
    u8 pad3FC[4];
    s32 f400;
    u8 pad404[0x20];
    s16 f424;
    s16 f426;
    s32 f428;
    Mo *f42C;
    u8 pad430[0x10];
    Vec f440;
    Vec f450;
    u8 pad460[0x10];
    Vec f470;
    u8 pad480[0x2C];
    f32 f4AC;
    f32 f4B0;
    f32 f4B4;
    u8 pad4B8[0x18];
    Vec f4D0;
    u8 pad4E0[0x40];
    Vec f520;
    u8 pad530[0x20];
    s16 f550;
    s16 f552;
    u8 pad554[6];
    s16 f55A;
    s16 f55C;
    u8 pad55E[0xA];
    u64 f568;
    u64 f570;
    u8 pad578[0x18];
    u8 f590[0x2A0];
    Vec f830;
    Vec f840;
    f32 f850;
    s32 f854;
    s32 f858;
    s32 f85C;
    u8 f860;
    u8 pad861[0xCF];
    u8 f930[0x20];
    u8 f950[0x2C];
    u8 f97C[0x60];
    u8 f9DC[0x30];
    s32 fA0C;
    u8 padA10[0x1E];
    s16 fA2E;
    u8 padA30[2];
    s16 fA32;
    s16 fA34;
    s16 fA36;
    s16 fA38;
    u8 padA3A[0xA];
    u32 fA44;
    u8 padA48[4];
    s32 fA4C;
    u8 padA50[8];
    s16 fA58;
    s16 fA5A;
    s16 fA5C;
    s16 fA5E;
    f32 fA60;
    f32 fA64;
    u8 padA68[0x24];
    Trig fA8C;
    u8 padA8D[0x83];
    f32 fB10;
    f32 fB14;
    u8 fB18;
    u8 padB19[3];
    s32 fB1C;
    s32 fB20;
    s32 fB24;
} Chr;

class Svc {
public:
    virtual void d8();
    virtual void dC();
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1C();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2C();
    virtual void d30();
    virtual void d34();
    virtual void d38();
    virtual void d3C();
    virtual void d40();
    virtual void d44();
    virtual void d48();
    virtual void d4C();
    virtual void d50();
    virtual void d54();
    virtual void d58();
    virtual void d5C();
    virtual void d60();
    virtual void d64();
    virtual void d68();
    virtual void d6C();
    virtual void d70();
    virtual void d74();
    virtual void d78();
    virtual void d7C();
    virtual void d80();
    virtual void d84();
    virtual void d88();
    virtual void d8C();
    virtual void d90();
    virtual void d94();
    virtual void d98();
    virtual void d9C();
    virtual void dA0();
    virtual void dA4();
    virtual void dA8();
    virtual void dAC();
    virtual void dB0();
    virtual void dB4();
    virtual void dB8();
    virtual void dBC();
    virtual s32 Busy();
    virtual void dC4();
    virtual void dC8();
    virtual void dCC();
    virtual void dD0();
    virtual void dD4();
    virtual void dD8();
    virtual void dDC();
    virtual void dE0();
    virtual void dE4();
    virtual void dE8();
    virtual void dEC();
    virtual void dF0();
    virtual void dF4();
    virtual void dF8();
    virtual void dFC();
    virtual void d100();
    virtual void d104();
    virtual void d108();
    virtual void d10C();
    virtual void d110();
    virtual void d114();
    virtual void d118();
    virtual void d11C();
    virtual void d120();
    virtual void d124();
    virtual void d128();
    virtual void d12C();
    virtual void d130();
    virtual void d134();
    virtual void d138();
    virtual void d13C();
    virtual void d140();
    virtual void d144();
    virtual void d148();
    virtual void d14C();
    virtual void d150();
    virtual void d154();
    virtual void d158();
    virtual void d15C();
    virtual void d160();
    virtual void d164();
    virtual void d168();
    virtual void d16C();
    virtual void d170();
    virtual void d174();
    virtual void d178();
    virtual void d17C();
    virtual void d180();
    virtual void d184();
    virtual void d188();
    virtual void d18C();
    virtual void d190();
    virtual void d194();
    virtual void d198();
    virtual void d19C();
    virtual void d1A0();
    virtual void d1A4();
    virtual void d1A8();
    virtual void d1AC();
    virtual void d1B0();
    virtual void d1B4();
    virtual void d1B8();
    virtual void d1BC();
    virtual void d1C0();
    virtual void d1C4();
    virtual void d1C8();
    virtual void d1CC();
    virtual void d1D0();
    virtual void d1D4();
    virtual void d1D8();
    virtual void d1DC();
    virtual void d1E0();
    virtual void d1E4();
    virtual void d1E8();
    virtual void d1EC();
    virtual void d1F0();
    virtual void d1F4();
    virtual void d1F8();
    virtual void d1FC();
    virtual void d200();
    virtual void d204();
    virtual void d208();
    virtual void d20C();
    virtual void d210();
    virtual void d214();
    virtual void d218();
    virtual void d21C();
    virtual void d220();
    virtual void d224();
    virtual void d228();
    virtual void d22C();
    virtual void d230();
    virtual void d234();
    virtual void d238();
    virtual void d23C();
    virtual void d240();
    virtual void d244();
    virtual void d248();
    virtual void d24C();
    virtual void d250();
    virtual void d254();
    virtual void d258();
    virtual void d25C();
    virtual void d260();
    virtual void d264();
    virtual void d268();
    virtual void d26C();
    virtual void d270();
    virtual void d274();
    virtual void d278();
    virtual void d27C();
    virtual void d280();
    virtual void d284();
    virtual void d288();
    virtual void d28C();
    virtual void d290();
    virtual void d294();
    virtual void d298();
    virtual void d29C();
    virtual void d2A0();
    virtual void d2A4();
    virtual s32 Dead();
};

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
f32 Atan2f_1291a8(f32, f32);
void FrameCalcWorldMatrix_148ff0(s32, Mat *);
void ModelSetScale_150ff0(Obj *, Vec *);
void ModelSetRot_151080(Obj *, f32 *);
void ModelSetPos_151110(Obj *, Vec *);
s32 ModelGetFrame_1511f0(Obj *, s32);
s32 ModelFindFrameIndexByName_151220(Obj *, s32 *);
f32 ModelObjGetMotionPhase_1add70(Obj *);
void *ModelObjGetMotionName_1add90(Obj *);
void ModelObjExCalcSoundVolPan_1b0780(Obj *, f32 *, f32 *);
void SoundNoteListPush_1b4cd0(void *, s32, s32, s32, s32, f32, f32);
s32 SoundNextPlayHandle_1b81c0(void);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
Obj *ObjRecGetLiveObject_1c4a90(s32, s32);
s32 CollRaycastNearest_1c86e0(s32, s32, s32, Vec *, Vec *, f32 *);
s32 CollTriListCompact_1ca3e0(s32, s32);
s32 StrEqualNonNull_1ca6c0(void *, void *);
void MatToRotPos_1cade0(Vec *, Vec *, Mat *);
f32 VecLengthSqXZ_1cb450(Vec *);
f32 VecLengthSq_1cb470(Vec *);
f32 VecLengthXZ_1cb490(Vec *);
f32 VecLength_1cb4c0(Vec *);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
f32 VecDot3_1cba90(void *, void *);
void VecLerpPoint_1cbac0(Vec *, Vec *, Vec *, f32);
void VecNormalize_1cbb80(Vec *, Vec *);
void VecScale_1cbca0(void *, void *, f32);
void VecSub_1cbd00(void *, void *, void *);
void VecAdd_1cbdc0(void *, void *, void *);
void VecCopy_1cbe30(void *, void *);
void MatIdentity_1cbe40(Mat *);
f32 AngleWrap_1cbf30(f32);
f32 GameSceneGetTimeStep_1ceba0(s32);
void GameSceneSoundSlot5PlaySeVol_1d05d0(s32, s32, f32);
s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
void CharaAimCtrlSetEnabled_1d8150(Vec *, u8);
s32 MapFindLinkNearInBlock_1e3670(s32, s32, Vec *);
s32 MapResolveGroundMaterialIdMaybe_1e5290(s32, s32, s32);
s32 MapLinkGetTopAttrMaybe_1e9230(s32);
s32 MapLinkGetHeight_1e9240(s32);
f32 MapLinkGetAngle_1e9250(s32);
void MapLinkGetTopPosVec4_1e9260(s32, Vec *);
void MapLinkGetPosVec4_1e9290(s32, Vec *);
s32 GetCurrentScene_1f5be0(void);
s32 ActionMgrGetSurfaceParamsGlobal_1fd8e0(void);
s32 GetActionMgr_1fdb50(void);
Ctx *GetGameData_1fede0(void);
s32 MapEvCollectCollTrisNearMaybe_1ff130(s32, s32, Vec *, Vec *, s32, f32);
s32 GetMapMgr_201a90(void);
void FieldHudWidget80CarryOpenMaybe_203f70(void);
void CharaReleaseHeldTarget_2116b0(Chr *, f32, f32, s32, f32);
void CharaSpawnBlownGroundFx_212250(Chr *, s32);
void CharaSquashScaleGet_2191e0(void *, Vec *);
void CharaSquashTick_2192b0(void *);
s32 CharaMoveReqGetVelocity_219380(void *, Vec *);
f32 CharaMoveReqGetAgeParitySign_219450(void *);
void CharaMoveReqAge_219480(void *);
void CharaLadderStateReset_21ae70(Vec *);
void CharaUpdateLocomotionMotionMaybe_21c970(Chr *, void *);
void ActCfgTableGetRunMotionName_21f570(s32, void *, s32);
void ActCfgTableSumTimeMove_21fb80(s32, f32 *, s32, void *, f32, f32);
void ActCfgTableSumNormalTimeMove_21fba0(s32, f32 *, s32, void *, f32, f32);
void ActCfgTableSumTimeAccl_220260(s32, f32 *, s32, void *, f32, f32);
void ActCfgTableSumNormalTimeAccl_220280(s32, f32 *, s32, void *, f32, f32);
u64 ActCfgTableEvalAttrFlags_2219e0(s32, s32, void *, f32);
u64 ActCfgTableEvalNormalAttrFlags_221cc0(s32, s32, void *, f32);
s32 ActCfgTableGetNullNameById_223ab0(s32, s32, s32);
f32 ActCfgTableGetAccelScale_223cb0(s32);
Chr *ActionMgrFindById_233b50(s32, s32);
s32 ActionMgrFindRefById_233cf0(s32, s32);
void CharaMoveHangMaybe_234920(Chr *, St *);
void CharaMoveApplyMaybe_234bf0(Chr *, St *);
void CharaMoveCollideMaybe_234dc0(Chr *, St *);
s32 CharaCalcBoundsRangeMaybe_237f20(Chr *, Vec *, Vec *, s32, s32, f32);
f32 CharaGetSpeedScale_238240(Chr *);
s32 CharaIsHeadUnderwaterMaybe_238250(Chr *);
void CharaGetWaterSurfacePosMaybe_238290(Chr *, Vec *);
f32 CharaGetHeadHeightMaybe_238360(Chr *);
f32 CharaGetWaterDepthMaybe_238370(Chr *);
f32 CharaGetHeightAboveGround_238380(Chr *);
Anm *CharaGetWaterTriMaybe_2383d0(Chr *, s32);
Anm *CharaGetGroundTri_238410(Chr *, s32);
void CharaGetWaterFlowVelMaybe_238490(Chr *, Vec *);
void CharaGetPlatformVelMaybe_2384e0(Chr *, Vec *);
s32 CharaGetNthAttachPointPos_238580(Chr *, s32, s32, Vec *);
f32 CharaGetCollHeight_2385f0(Chr *);
f32 CharaGetCollWidth_238640(Chr *);
f32 CharaGetCollRadius_2386a0(Chr *);
void CharaAddReqMove_238730(Chr *, Vec *);
void CharaAddActMove_238740(Chr *, f32 *);
void CharaAddActAccel_238750(Chr *, f32 *);
void CharaSetSrtVec40_238760(Chr *, f32, f32, f32);
void CharaSetVelocity_238770(Chr *, f32, f32, f32);
void CharaSetRot_2387d0(Chr *, f32, f32, f32);
void CharaSetPosVec_2387e0(Chr *, Vec *);
void CharaGetPos_2388a0(Chr *, Vec *);
void CharaGetRot_2388b0(Chr *, Vec *);
void CharaAddCollIgnoreMask_238920(Chr *, s32);
s32 CharaGetCollIgnoreMask_238950(Chr *);
void CharaOrFlags3D0_238960(Chr *, u64);
s32 SurfaceParamFindByTriAttr_23a2b0(s32, Anm *);
f32 SurfaceParamGetSlideDecel_23a310(s32);
f32 SurfaceParamGetAccelMaybe_23a320(s32);
s32 CollTriVsCylinderMaybe_23a3e0(Col *, Vec *, f32, f32);
s32 IsInBattle_288420(void);
f32 AiGetSpeedCapScale_2c0f70(void *);
f32 AiGetSpeedScale_2c0f80(void *);
void EffectSpawnWaterSplash_2d8400(s32, Vec *);
void EffectSpawnWaterRipple_2d84e0(s32, Vec *);
s32 GetEffectMgr_2d9040(void);
void EffectSetId_2e0100(s32, void *, s32);
void EffectSetParamInt_2e0530(s32, void *, s32, s32);
void EffectSetParamFloat_2e0600(s32, void *, s32, f32);
void EffectSetPos_2e0bb0(s32, void *, Vec *);
void EffectCreateByName_2e1020(void *, s32, const char *, s32);
void TargetRefDetachFromParent_2e5890(void *);
void TargetRefSetTranslation_2e5bf0(void *, Vec *);
void TargetRefSetRotation_2e5d10(void *, Vec *);
s32 TargetRefResolve_2e5ed0(void *, s32);
Tgt *TargetRefGetMapObj_2e7050(void *);
s32 TargetRefGetId_2e7120(void *);
u32 TargetRefGetKind_2e7130(void *);
void CharaRefEvalCompByName_312090(s32, Vec *, void *, f32, f32);
Svc *ActorFindById_3eb870(Ctx *, s32);
char *strcpy(char *, const char *);
void SrtSetRotThunk_1c73d0(Chr *, f32, f32, f32);
void SrtSetPosFromVecThunk_1c7410(Chr *, Vec *);

extern const f32 D_0045B080[];
extern char D_0045C6E0[];
extern char D_0045C6E8[];
extern char D_0045C6F0[];
extern char D_0045C6F8[];
extern char D_0045C700[];
extern char D_0045C708[];
extern f32 D_0047D278;
extern f32 D_0047D288;
extern f32 D_0047DADC;
extern f32 D_0047DB20;
extern f32 D_0047DB30;
extern f32 D_0047DB34;
}

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 16; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }
#define ZERO32(d) { u8 *p_ = (u8 *)(d); u32 n_ = 32; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

static inline f32 AbsI(f32 x) {
    if (x < 0.0f) x = -x;
    return x;
}

static inline f32 AbsV(Vec *p) {
    f32 v = p->y;

    if (v < 0.0f) v = -v;
    return v;
}

static inline f32 AbsT(f32 x) {
    return (x < 0.0f) ? -x : x;
}

static inline f32 ClampAbs(Chr *c) {
    return AbsT(c->fA64);
}

static inline bool Alive(Chr *c) {
    return !(c->fA44 & 0x80000000);
}

static inline void SetBit(u32 *p, u32 bit, s32 on) {
    *p = on ? (*p | bit) : (*p & ~bit);
}

static inline bool Walk(Chr *c) {
    switch (c->fA32) {
    case 4:
        return true;
    case 16: {
        bool b = true;
        if (c->fA34 != 0 && c->fA34 != 1) b = false;
        return b;
    }
    }
    return false;
}

static inline bool Lifted(Chr *c) {
    return (c->f3D0 & 0x4000000000000ULL) ? true : false;
}

static inline u8 Hang(Chr *c) {
    if (c->f3D0 & 0x2000000000000000ULL) return true;
    switch (c->fA32) {
    case 0:
    case 1:
    case 2:
    case 3:
        switch (c->fA34) {
        case 0x14:
        case 0x15:
            return true;
        }
        break;
    case 15:
        switch (c->fA34) {
        case 1:
            return 1;
        }
        break;
    }
    return false;
}

static inline bool Brake(Chr *c) {
    if (c->f3D0 & 0x8000000000000ULL) return true;
    if (c->fA44 & 0x20000) return true;
    if (c->fA44 & 0x10000) return true;
    if (c->f3D0 & 0x400000000000ULL) return true;
    if (c->f3D8 & 1) return true;
    if (!(c->f3D8 & 4)) return true;
    if (CharaGetHeightAboveGround_238380(c) < D_0047DB20 * (f32)D_0045B080[0]) return true;
    return false;
}

static inline bool NoDrop(Chr *c) {
    return !(c->f3D0 & 0x800000000000000ULL);
}

static inline bool Slide(Chr *c, f32 &lo, f32 &hi) {
    if (CharaIsHeadUnderwaterMaybe_238250(c)) return true;
    if (!(c->f3D8 & 0x10)) return false;
    if (!(c->f3D8 & 4)) return true;
    lo = D_0047DB20 * (f32)D_0045B080[0];
    hi = CharaGetWaterDepthMaybe_238370(c);
    hi += lo;
    if (hi < CharaGetHeadHeightMaybe_238360(c)) return false;
    if (!(CharaGetHeightAboveGround_238380(c) <= lo)) return true;
    return false;
}

static inline void Set3(f32 *p, f32 x, f32 y, f32 z) {
    p[0] = x;
    p[1] = y;
    p[2] = z;
}

static inline s32 Hold(Chr *c) {
    if (c->f3D0 & 0x40000000) {
        if (!(c->fA44 & 0x8000)) return 0;
        return 1;
    }
    return 0;
}

static inline s32 Find(Obj *o, s32 *key) {
    return ModelGetFrame_1511f0(o, ModelFindFrameIndexByName_151220(o, key));
}

static inline s32 Leader(void) {
    return GetGameData_1fede0()->f18->f18E;
}

static inline s32 Kind(Obj *o) {
    return (o->f510 <= 0) ? -1 : o->f4F4;
}

static inline bool Ready(Chr *t) {
    Svc *v;

    if (!(t->fA44 & 0x40)) return false;
    if (t->fA38 == 0) {
        switch (t->fA32) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        default:
            return false;
        }
    }
    v = ActorFindById_3eb870(GetGameData_1fede0(), t->f424);
    if (v == 0) return false;
    if (v->Busy()) return false;
    return true;
}

extern "C" void CharaUpdateMovement_20a7d0(Chr *c, St *st) {
    f32 v4DC;
    f32 v4D8;
    f32 v4D4;
    f32 v4D0;
    s32 v4C8[2];
    Mat mat;
    Vec v470;
    f32 v460[4] __attribute__((aligned(16)));
    Seg seg[2];
    f32 v440[4] __attribute__((aligned(16)));
    f32 v430[4] __attribute__((aligned(16)));
    Vec v420;
    Vec v410;
    Vec v400;
    Vec v3F0;
    Vec v3E0;
    Vec v3D0;
    Vec v3C0;
    Vec v3B0;
    Vec v3A0;
    f32 v390[4] __attribute__((aligned(16)));
    f32 v380[4] __attribute__((aligned(16)));
    Vec v370;
    Vec v360;
    Vec v350;
    f32 v340[4] __attribute__((aligned(16)));
    f32 v330[4] __attribute__((aligned(16)));
    Vec v320;
    Vec v310;
    Vec v300;
    Vec v2F0;
    Vec v2E0;
    Vec v2D0;
    Vec v2C0;
    Vec v2B0;
    char buf[32];
    s32 v270[8];
    char buf2[32];
    s32 v230[8];
    s32 v210[8];
    s32 v1F0[8];
    s32 v1D0[8];
    Mat m190;
    Vec v180;
    Vec v170;
    Vec v160;
    Vec v150;
    Vec v140;
    Vec v130;
    Vec v120;
    Vec v110;
    Vec v100;
    Vec vF0;
    Vec vE0;
    Vec vD0;
    s32 w;
    s32 w2;
    s32 snd;
    s32 n;
    s32 k;
    s32 e;
    s32 q;
    s32 i;
    Chr *t2;
    bool ok;
    bool bad;
    bool hit;
    s32 a58;
    s32 a5C;
    s32 pos;
    void *ww;
    void *r;
    Obj *o;
    Seg *sg;
    Mo *mo;
    Svc *u;
    Col *cl;
    Tgt *tg;
    u64 fl;
    f32 f26;
    f32 k26;
    f32 f25;
    f32 n25;
    f32 lo;
    f32 f24;
    f32 y24;
    f32 y5;
    f32 hi;
    f32 ang24;
    f32 f23;
    f32 f22;
    f32 spd;
    f32 f21;
    f32 rate;
    f32 dec;
    f32 ang5;
    f32 a60;
    f32 vy;
    f32 bs;
    f32 f20;
    f32 cap;
    f32 acc;
    f32 sq;
    f32 dy;
    f32 t;
    f32 v;
    f32 m;
    f32 d;
    f32 l;
    f32 kf;
    f32 h;
    f32 rx;
    f32 rz;
    f32 sp;
    f32 lim;
    f32 one;

    if (!Alive(c)) return;
    if (st == 0) return;
    if (c->f3F4 == 0 || c->f428 == 0) return;
    if (c->fA44 & 0x80000) return;
    one = 1.0f;
    w = GetCurrentScene_1f5be0();
    f23 = GameSceneGetTimeStep_1ceba0(w);
    if (c->fA44 & 0x40) {
        o = ObjRecGetLiveObject_1c4a90(w, c->fB20);
        if (o == 0) return;
        MatIdentity_1cbe40(&mat);
        q = Find(o, (s32 *)((s32)c + 0xB24));
        if (q != 0) {
            FrameCalcWorldMatrix_148ff0(q, &mat);
        } else {
            MatIdentity_1cbe40(&mat);
        }
        VecCopy_1cbe30(&v470, &mat.d);
        v470.y = v470.y - 0.5f * D_0045B080[0];
        {
            ZERO16(v460);

            f20 = Atan2f_1291a8(mat.c.x, mat.c.z);
            v460[1] = f20;
            {
                f32 vC0[4] = {0};

                vC0[0] = Sinf_128fd0(f20);
                vC0[2] = Cosf_128d30(f20);
                CharaSetRot_2387d0(c, 0.0f, f20, 0.0f);
                SrtSetRotThunk_1c73d0(c, 0.0f, f20, 0.0f);
                Set3(&c->f450.x, vC0[0], vC0[1], vC0[2]);
                c->f450.w = 0.0f;
                VecNormalize_1cbb80(&c->f450, &c->f450);
                Set3(&c->f440.x, vC0[0], vC0[1], vC0[2]);
                c->f440.w = 0.0f;
                VecNormalize_1cbb80(&c->f440, &c->f440);
            }
            CharaSetPosVec_2387e0(c, &v470);
            SrtSetPosFromVecThunk_1c7410(c, &v470);
            ModelSetRot_151080(c->f3F4, v460);
            ModelSetPos_151110(c->f3F4, &v470);
        }
        return;
    }
    if (c->fA44 & 0x20) {
        c->f3D0 &= (u128)0xFFF7FFFFFFFFFFFFULL;
        c->f3D0 &= (u128)0xFFFF7FFFFFFFFFFFULL;
        c->f3D0 &= (u128)0xFFFFBFFFFFFFFFFFULL;
    }
    n = 0;
    r = 0;
    if (c->fA8C.on) r = ModelObjGetMotionName_1add90(c->f3F4);
    f20 = ModelObjGetMotionPhase_1add70(c->f3F4);
    if (StrEqualNonNull_1ca6c0((void *)c->f400, r)) {
        if (c->f3F8 <= f20) {
            n++;
            seg[0].a = c->f3F8;
            seg[0].b = f20 - c->f3F8;
        } else {
            seg[1].a = 0.0f;
            seg[1].b = f20;
            seg[0].a = c->f3F8;
            seg[0].b = 1.0f - c->f3F8;
            n += 2;
        }
    } else {
        seg[0].b = f20;
        n++;
        seg[0].a = 0.0f;
    }
    for (k = 0; k < n; k++) {
        ZERO16(v440);
        ZERO16(v430);

        if (c->fA38 == 0) {
            sg = &seg[k];
            f21 = sg->a;
            CharaOrFlags3D0_238960(c, ActCfgTableEvalNormalAttrFlags_221cc0(c->f428, c->fA32, r, f21));
            f20 = sg->b;
            ActCfgTableSumNormalTimeAccl_220280(c->f428, v440, c->fA32, r, f21, f20);
            ActCfgTableSumNormalTimeMove_21fba0(c->f428, v430, c->fA32, r, f21, f20);
        } else {
            sg = &seg[k];
            f21 = sg->a;
            CharaOrFlags3D0_238960(c, ActCfgTableEvalAttrFlags_2219e0(c->f428, c->fA0C, r, f21));
            f20 = sg->b;
            ActCfgTableSumTimeAccl_220260(c->f428, v440, c->fA0C, r, f21, f20);
            ActCfgTableSumTimeMove_21fb80(c->f428, v430, c->fA0C, r, f21, f20);
        }
        if (!(c->f3D0 & 0x10000000)) {
            if (StrEqualNonNull_1ca6c0(&c->fA8C, r) && (e = ActionMgrFindRefById_233cf0(GetActionMgr_1fdb50(), c->f426)) != 0) {
                CharaRefEvalCompByName_312090(e, &v420, r, f21, f20);
                VecAdd_1cbdc0(v430, v430, &v420);
            }
        }
        CharaAddActAccel_238750(c, v440);
        CharaAddActMove_238740(c, v430);
    }
    if (c->fA32 == 4 && c->fA34 == 5) CharaOrFlags3D0_238960(c, 0x4000000C00000000ULL);
    if (c->f3D0 & 0x8000000) CharaAddCollIgnoreMask_238920(c, 0x40);
    SetBit(&c->fA44, 0x100, (c->f3D0 & 0x100) != 0);
    SetBit(&c->fA44, 0x40, (c->f3D0 & 0x40) != 0);
    SetBit(&c->fA44, 0x20, (c->f3D0 & 0x20) != 0);
    SetBit(&c->fA44, 0x10, (c->f3D0 & 0x10) != 0);
    SetBit(&c->fA44, 0x8, (c->f3D0 & 0x8) != 0);
    SetBit(&c->fA44, 0x4, (c->f3D0 & 0x4) != 0);
    SetBit(&c->fA44, 0x2, (c->f3D0 & 0x2) != 0);
    SetBit(&c->fA44, 0x1, (c->f3D0 & 0x1) != 0);
    CharaMoveReqAge_219480(c->f930);
    if (CharaMoveReqGetVelocity_219380(c->f930, &v410)) {
        c->f3DC = 0.5f * CharaMoveReqGetAgeParitySign_219450(c->f930);
        CharaAddReqMove_238730(c, &v410);
        if (!(VecLengthSq_1cb470(&v410) <= 0.0f)) c->f3D0 |= 0x2000000000000000ULL;
    }
    CharaSquashTick_2192b0(c->f950);
    CharaSquashScaleGet_2191e0(c->f950, &v400);
    ModelSetScale_150ff0(c->f3F4, &v400);
    st->f10 = 0;
    st->f18 = 0;
    st->f20 = 0;
    st->f28 = 0;
    if (!(c->fA44 & 0x40)) {
        f20 = 1.5f * D_0045B080[0];
        if (CharaCalcBoundsRangeMaybe_237f20(c, &v3E0, &v3F0, 0, 0, f20)) {
            h = 5.0f * D_0045B080[0];
            v3E0.y = v3E0.y + h;
            v3F0.y = v3F0.y - 100.0f * D_0045B080[0];
            if (c->fA36 == 16) v3E0.y = v3E0.y + h;
            if ((a58 = c->fA36) == 16 || a58 == 17) {
                v3E0.x += f20;
                v3E0.z += f20;
                v3F0.x -= f20;
                v3F0.z -= f20;
            }
            VecLerpPoint_1cbac0(&v3D0, &v3E0, &v3F0, 0.5f);
            rx = 0.5f * (v3E0.x - v3F0.x);
            rz = 0.5f * (v3E0.z - v3F0.z);
            rx = (rx > rz) ? rx : rz;
            st->f10 = MapEvCollectCollTrisNearMaybe_1ff130(st->fC, st->f8, &v3E0, &v3D0, c->f424, rx);
            st->f10 = CollTriListCompact_1ca3e0(st->fC, st->f10);
        }
    }
    st->f34 = ActCfgTableGetNullNameById_223ab0(c->f428, 1, 0);
    st->f38 = ActCfgTableGetNullNameById_223ab0(c->f428, 2, 0);
    CharaGetRot_2388b0(c, &v3C0);
    switch (c->fA32) {
    case 7:
        CharaAddCollIgnoreMask_238920(c, 0x1000);
        CharaMoveApplyMaybe_234bf0(c, st);
        break;
    case 6:
        CharaAddCollIgnoreMask_238920(c, 0x1000);
        CharaSetVelocity_238770(c, 0.0f, 0.0f, 0.0f);
        CharaSetSrtVec40_238760(c, 0.0f, 0.0f, 0.0f);
        CharaMoveHangMaybe_234920(c, st);
        break;
    default:
        f22 = AngleWrap_1cbf30(Atan2f_1291a8(c->f450.x, c->f450.z) - v3C0.y);
        mo = c->f42C;
        rate = mo ? mo->f8 : 0.0f;
        cap = mo ? mo->f4 : 0.0f;
        if (c->fA44 & 0x1000000) cap *= AiGetSpeedCapScale_2c0f70(c->f590);
        c->f94 = 0.0f;
        fl = c->f570;
        if (fl & 0x1000) {
            c->f94 = f22;
        } else if (fl & 0x800) {
            for (t = 0.0f; t < f23; t += 1.0f) {
                if (!(rate <= 1.0f)) rate = 1.0f;
                v = rate * f22;
                c->f94 = v;
                if (v < 0.0f) v = -v;
                if (!(v <= cap)) c->f94 = (c->f94 < 0.0f) ? -cap : cap;
            }
        }
        acc = 0.0f;
        spd = acc;
        w2 = ActionMgrGetSurfaceParamsGlobal_1fd8e0();
        if (c->f42C) {
            spd = c->f42C->fC;
            acc *= CharaGetSpeedScale_238240(c);
            spd *= CharaGetSpeedScale_238240(c);
        }
        if (c->fA44 & 0x1000000) spd *= AiGetSpeedScale_2c0f80(c->f590);
        if (Walk(c)) {
            sq = spd * spd;
            dec = D_0047DADC * spd;
            for (n25 = 0.0f; n25 < f23; n25 += 1.0f) {
                fl = c->f570;
                kf = 0.0f;
                if (fl & 3) kf = (fl & 2) ? D_0047DB30 : 0.125f;
                k26 = spd * kf;
                y24 = c->f80.y;
                c->f80.y = 0.0f;
                if (y24 <= 0.0f) {
                    l = VecLengthXZ_1cb490(&c->f80) - dec;
                    if (l <= 0.0f) l = 0.0f;
                    VecScaleToLength_1cb510(&c->f80, &c->f80, l);
                }
                if (c->f570 & 3) {
                    VecScale_1cbca0(&v3B0, &c->f440, k26);
                    VecAdd_1cbdc0(&c->f80, &c->f80, &v3B0);
                }
                if (!(spd <= 0.0f)) {
                    if (!(VecLengthSqXZ_1cb450(&c->f80) <= sq)) VecScaleToLength_1cb510(&c->f80, &c->f80, spd);
                }
                c->f80.y = y24;
            }
            f23 = 1.0f;
    } else if (c->fA32 == 5) {
        e = 0;
        if (c->f3D8 & 0x10) e = SurfaceParamFindByTriAttr_23a2b0(w2, CharaGetWaterTriMaybe_2383d0(c, 0));
        if (e) {
            acc = SurfaceParamGetAccelMaybe_23a320(e) * ActCfgTableGetAccelScale_223cb0(c->f428);
        }
        CharaGetWaterFlowVelMaybe_238490(c, &v3A0);
        VecSub_1cbd00(&c->f80, &c->f80, &v3A0);
        y5 = c->f80.y;
        c->f80.y = 0.0f;
        ang5 = AngleWrap_1cbf30(v3C0.y + c->f94);
        {
            ZERO16(v390);
            v390[0] = Sinf_128fd0(ang5);
            v390[2] = Cosf_128d30(ang5);
            {
                ZERO16(v380);
                v380[0] = c->f440.x;
                v380[2] = c->f440.z;
                if (c->f570 & 3) {
                    d = VecDot3_1cba90(&c->f450, v390);
                    if (!(d <= 0.0f)) {
                        VecScale_1cbca0(&v370, &c->f450, acc * d);
                        VecAdd_1cbdc0(&c->f80, &c->f80, &v370);
                    }
                }
                VecScale_1cbca0(&c->f80, v380, VecDot3_1cba90(v380, &c->f80));
                if (!(spd <= 0.0f)) {
                    if (!(VecLengthSqXZ_1cb450(&c->f80) <= spd * spd)) VecScaleToLength_1cb510(&c->f80, &c->f80, spd);
                }
                if (VecDot3_1cba90(v380, &c->f80) < 0.0f) CharaSetVelocity_238770(c, 0.0f, 0.0f, 0.0f);
            }
        }
        c->f80.y = y5;
        VecAdd_1cbdc0(&c->f80, &c->f80, &v3A0);
    } else {
        e = (c->f3D8 & 4) ? SurfaceParamFindByTriAttr_23a2b0(w2, CharaGetGroundTri_238410(c, 0)) : w2;
        CharaGetPlatformVelMaybe_2384e0(c, &v360);
        VecSub_1cbd00(&c->f80, &c->f80, &v360);
        if (c->f3D0 & 0x8000000000000ULL) {
            if (c->fA32 != 16 && c->fA32 != 17) {
                if (c->f3D8 & 4) {
                    a60 = c->fA60;
                    c->f80.y = a60 - CharaGetHeightAboveGround_238380(c);
                    { f32 l_ = c->fA64;
                    v = ((Vec *)&c->f80)->y;
                    if (v < 0.0f) v = -v;
                    if (!(v <= AbsT(l_))) {
                        if (c->f80.y >= 0.0f) {
                            c->f80.y = c->fA64;
                        } else {
                            c->f80.y = -c->fA64;
                        }
                    }
                    }
                } else {
                    c->f80.y = 0.0f;
                }
            }
        }
        vy = c->f80.y;
        { f32 k_ = D_0047DB34;
        c->f80.y = 0.0f;
        VecScale_1cbca0(&c->f80, &c->f80, k_); }
        if (!Lifted(c)) {
            if (Hang(c)) {
                if (!(c->f3D8 & 4)) goto L_end;
                if (!(CharaGetHeightAboveGround_238380(c) <= D_0047DB20 * (f32)D_0045B080[0])) goto L_end;
                if (e) {
                    acc = SurfaceParamGetSlideDecel_23a310(e) * ActCfgTableGetAccelScale_223cb0(c->f428) * one;
                }
                if (vy < 0.0f) c->f80.y = vy;
                l = VecLength_1cb4c0(&c->f80);
                if (l <= acc) {
                    CharaSetVelocity_238770(c, 0.0f, 0.0f, 0.0f);
                } else {
                    VecScaleToLength_1cb510(&c->f80, &c->f80, l - acc);
                }
                if (vy < 0.0f) vy = c->f80.y;
                goto L_end;
            }
            if (!Brake(c)) {
                if (NoDrop(c)) goto L_end;
                if (!Slide(c, lo, hi)) goto L_end;
            }
            if (spd == 0.0f) {
                if (e) {
                    acc = SurfaceParamGetAccelMaybe_23a320(e) * ActCfgTableGetAccelScale_223cb0(c->f428) * one;
                }
                l = VecLengthXZ_1cb490(&c->f80);
                if (l <= acc) {
                    CharaSetVelocity_238770(c, 0.0f, 0.0f, 0.0f);
                } else {
                    VecScaleToLength_1cb510(&c->f80, &c->f80, l - acc);
                }
            } else if (c->f3D0 & 0x20000000) {
                if (e) {
                    acc = SurfaceParamGetAccelMaybe_23a320(e) * ActCfgTableGetAccelScale_223cb0(c->f428) * one;
                }
                if (c->f570 & 3) {
                    VecScale_1cbca0(&v350, &c->f440, acc);
                    VecAdd_1cbdc0(&c->f80, &c->f80, &v350);
                    if (!(VecLengthXZ_1cb490(&c->f80) < spd)) VecScaleToLength_1cb510(&c->f80, &c->f80, spd);
                } else {
                    l = VecLengthXZ_1cb490(&c->f80);
                    if (l <= acc) {
                        CharaSetVelocity_238770(c, 0.0f, 0.0f, 0.0f);
                    } else {
                        VecScaleToLength_1cb510(&c->f80, &c->f80, l - acc);
                    }
                }
            } else {
                if (e) {
                    acc = SurfaceParamGetAccelMaybe_23a320(e) * ActCfgTableGetAccelScale_223cb0(c->f428) * one;
                }
                ang24 = AngleWrap_1cbf30(v3C0.y + c->f94);
                {
                    ZERO16(v340);
                    v340[0] = c->f440.x;
                    v340[2] = c->f440.z;
                    {
                        ZERO16(v330);
                        v330[0] = Sinf_128fd0(ang24);
                        v330[2] = Cosf_128d30(ang24);
                        if (c->f570 & 3) {
                            if (IsInBattle_288420() && (c->fA44 & 0x1000000)) {
                                VecScale_1cbca0(&v320, v340, acc);
                                VecAdd_1cbdc0(&c->f80, &c->f80, &v320);
                            } else {
                                d = VecDot3_1cba90(&c->f450, v330);
                                if (!(d <= 0.0f)) {
                                    VecScale_1cbca0(&v310, &c->f450, acc * d);
                                    VecAdd_1cbdc0(&c->f80, &c->f80, &v310);
                                }
                            }
                        } else {
                            VecCopy_1cbe30(v340, v330);
                            l = VecLengthXZ_1cb490(&c->f80);
                            if (l <= acc) {
                                CharaSetVelocity_238770(c, 0.0f, 0.0f, 0.0f);
                            } else {
                                VecScaleToLength_1cb510(&c->f80, &c->f80, l - acc);
                            }
                        }
                    }
                    VecScale_1cbca0(&v300, v340, VecDot3_1cba90(v340, &c->f80));
                    VecSub_1cbd00(&v2F0, &c->f80, &v300);
                    l = VecLengthXZ_1cb490(&v2F0);
                    if (l <= acc) {
                        v2F0.x = 0.0f;
                        v2F0.y = 0.0f;
                        v2F0.z = 0.0f;
                        v2F0.w = 0.0f;
                    } else {
                        VecScaleToLength_1cb510(&v2F0, &v2F0, l - acc);
                    }
                    VecAdd_1cbdc0(&c->f80, &v300, &v2F0);
                    if (!(spd <= 0.0f)) {
                        if (!(VecLengthSqXZ_1cb450(&c->f80) <= spd * spd)) VecScaleToLength_1cb510(&c->f80, &c->f80, spd);
                    }
                }
            }
        }
    L_end:
        c->f80.y = vy;
        VecAdd_1cbdc0(&c->f80, &c->f80, &v360);
    }
    VecScale_1cbca0(&c->f80, &c->f80, f23);
    if (!(c->f3D8 & 4)) {
        c->f3D0 |= 0x400000000000ULL;
        c->f80.y = 0.0f;
    }
    CharaMoveCollideMaybe_234dc0(c, st);
    VecScale_1cbca0(&c->f80, &c->f80, 1.0f / f23);
    if (c->fA38 == 0) {
        switch (c->fA32) {
        case 0:
        case 1:
        case 2:
        case 3:
            CharaUpdateLocomotionMotionMaybe_21c970(c, &v4C8);
        }
    }
        break;
    }
    n = 0;
    if (c->fA44 & 0x8000) {
        if (c->f3D0 & 0x80000000ULL) {
            VecCopy_1cbe30(&v2E0, &c->f470);
            switch (TargetRefGetKind_2e7130(c->f97C)) {
            case 11:
                v2E0.y += D_0045B080[0];
            case 1:
            case 4:
            case 5:
            case 7:
            case 8:
            case 9:
                VecSub_1cbd00(&v2D0, &v2E0, &c->f70);
                bs = c->f70.y + D_0047D278 * CharaGetCollHeight_2385f0(c);
                dy = v2E0.y - bs;
                lim = VecLengthXZ_1cb490(&v2D0) / 1.5f;
                if (!(AbsT(dy) <= lim)) {
                    if (dy < 0.0f) dy = -lim;
                    else dy = lim;
                }
                n = 4;
                v2E0.y = bs + dy;
                *(u128 *)&c->f520 = *(u128 *)&v2E0;
                break;
            case 3:
                n = 2;
                q = TargetRefGetId_2e7120(c->f97C);
                c->f55A = c->f424;
                c->f55C = q;
                break;
            }
        }
    }
    c->f550 = n;
    c->f552 = 0;
    {
        s32 h_;

        if (c->f3D0 & 0x40000000) {
            if (!(c->fA44 & 0x8000)) {
                c = (Chr *)c;
            } else {
                h_ = 1;
                goto e_;
            }
        }
        h_ = 0;
    e_:;
        CharaAimCtrlSetEnabled_1d8150(&c->f4D0, h_);
    }
    *(u128 *)&c->f4D0 = *(u128 *)&c->f470;
    if (c->fA32 != 7) {
        CharaLadderStateReset_21ae70(&c->f830);
        if (c->fA38 == 0 && !IsInBattle_288420()) {
            switch (c->fA32) {
            case 0:
            case 1:
            case 2:
            case 3:
                q = MapFindLinkNearInBlock_1e3670(GetMapMgr_201a90(), c->fA4C, &c->f70);
                if (q) {
                    MapLinkGetPosVec4_1e9290(q, &c->f830);
                    MapLinkGetTopPosVec4_1e9260(q, &c->f840);
                    c->f850 = MapLinkGetAngle_1e9250(q);
                    c->f858 = MapLinkGetHeight_1e9240(q);
                    c->f85C = MapLinkGetTopAttrMaybe_1e9230(q);
                    c->f860 = 1;
                    if (c->f70.y < 0.5f * (c->f830.y + c->f840.y)) {
                        c->f854 = 0;
                    } else {
                        c->f854 = c->f858;
                    }
                }
            }
        }
    }
    k = 0;
    if (c->fA32 == 7 && c->fA34 != 0 && c->fA34 != 1) {
        k = c->f85C;
    } else if ((c->f3D8 & 4) && CharaGetHeightAboveGround_238380(c) <= D_0047DB20 * (f32)D_0045B080[0]) {
        k = CharaGetGroundTri_238410(c, 0)->f42;
    }
    q = MapResolveGroundMaterialIdMaybe_1e5290(GetMapMgr_201a90(), c->fA4C, k);
    c->f3F4->f4F0 = GameSceneSoundSlot1GetHandle_1d07b0(w);
    c->f3F4->f4F4 = q;
    v4DC = 0.0f;
    v4D8 = 0.0f;
    ModelObjExCalcSoundVolPan_1b0780(c->f3F4, &v4DC, &v4D8);
    a58 = c->fA58;
    ww = (u8 *)w + 0xB0A4;
    if (a58 >= 0) SoundNoteListPush_1b4cd0(ww, c->f3F4->f4FC, a58, 2, c->fA5A, v4DC, v4D8);
    a5C = c->fA5C;
    if (a5C >= 0) SoundNoteListPush_1b4cd0(ww, GameSceneSoundSlot5GetHandle_1d0790(w), a5C, 2, c->fA5E, v4DC, v4D8);
    snd = GetEffectMgr_2d9040();
    CharaGetWaterSurfacePosMaybe_238290(c, &v2C0);
    if ((c->f3D8 & 1) && !(c->f3D8 & 0x10) && CharaGetNthAttachPointPos_238580(c, 1, 0, &v2B0)) {
        ZERO32(buf);

        switch (Kind(c->f3F4)) {
        case 14:
        case 17:
            strcpy(buf, D_0045C6E0);
            break;
        case 22:
        case 16:
        case 1:
            strcpy(buf, D_0045C6E8);
            break;
        }
        if (buf[0]) {
            EffectCreateByName_2e1020(v270, snd, buf, -1);
            EffectSetId_2e0100(snd, v270, c->f424);
            EffectSetPos_2e0bb0(snd, v270, &v2B0);
        }
    }
    f20 = VecLengthXZ_1cb490(&c->f80);
    if (c->f3D0 & 0x80) CharaSpawnBlownGroundFx_212250(c, CharaGetGroundTri_238410(c, 0)->f42);
    if (Hang(c)) {
        c->fB14 += f20;
    } else {
        c->fB14 = 15.0f;
    }
    if (!(c->fB14 <= 15.0f)) {
        if (c->f3D8 & 1) {
            Anm *an;

            c->fB18 = 0;
            an = CharaGetGroundTri_238410(c, 0);
            {
                ZERO32(buf2);

                switch (an->f42) {
                case 14:
                case 17:
                    strcpy(buf2, D_0045C6F0);
                    break;
                case 22:
                case 16:
                case 1:
                    strcpy(buf2, D_0045C6F8);
                    break;
                }
                if (buf2[0]) {
                    EffectCreateByName_2e1020(v230, snd, buf2, -1);
                    EffectSetId_2e0100(snd, v230, c->f424);
                    c->fB14 = 0.0f;
                }
            }
        }
    }
    if (!(c->fB14 <= 15.0f)) c->fB14 = 15.0f;
    if (!(c->f3D8 & 0x10)) {
        c->fB10 = 0.0f;
        c->fB1C = 0;
    } else {
        c->fB10 += D_0047D278;
        c->fB10 += f20;
        if (!(c->fB10 <= 24.0f)) c->fB10 = 24.0f;
        if (!(c->fB10 < 24.0f)) {
            c->fB10 = 0.0f;
            EffectSpawnWaterRipple_2d84e0(c->f424, &v2C0);
        }
        if (Kind(c->f3F4) == 0x12 && CharaGetWaterDepthMaybe_238370(c) < D_0047D288 * (f32)D_0045B080[0]) {
            hit = 0;
            r = ModelObjGetMotionName_1add90(c->f3F4);
            if (r) {
                ActCfgTableGetRunMotionName_21f570(c->f428, v210, c->fA2E);
                switch (c->fA32) {
                case 0:
                case 1:
                    if (c->fA34 == 2 && StrEqualNonNull_1ca6c0(r, v210)) hit = 1;
                    break;
                case 2:
                    if (c->fA34 == 2 && StrEqualNonNull_1ca6c0(r, v210)) hit = 1;
                    break;
                case 3:
                    if (c->fA34 == 2 && StrEqualNonNull_1ca6c0(r, v210)) hit = 1;
                    break;
                }
                switch (c->fA32) {
                case 0:
                case 1:
                case 2:
                case 3:
                    if (c->fA34 == 10) hit = 1;
                    if (c->fA34 == 11) hit = 1;
                    if (c->fA34 == 12) hit = 1;
                    if (c->fA34 == 13) hit = 1;
                }
            }
            if (hit) {
                EffectCreateByName_2e1020(v1F0, snd, D_0045C700, -1);
                EffectSetPos_2e0bb0(snd, v1F0, &v2C0);
            }
        }
        sp = c->f24;
        lim = c->f70.y;
        if ((c->fA32 == 4 || (c->fA44 & 0x20)) && !(sp <= v2C0.y) && !(v2C0.y < lim)) {
            q = SoundNextPlayHandle_1b81c0();
            SoundPlayScaledVolume_1b9520(GameSceneSoundSlot1GetHandle_1d07b0(w), 0x3A, q, 1.0f);
            EffectSpawnWaterSplash_2d8400(c->f424, &v2C0);
        }
        if (c->fB18) {
            c->fB1C++;
            if (CharaGetWaterDepthMaybe_238370(c) + 0.5f * D_0045B080[0] < CharaGetHeadHeightMaybe_238360(c) && c->fB1C >= 30) {
                c->fB18 = 0;
                EffectCreateByName_2e1020(v1D0, snd, D_0045C708, -1);
                EffectSetId_2e0100(snd, v1D0, c->f424);
                EffectSetParamInt_2e0530(snd, v1D0, 0, 1);
                EffectSetParamFloat_2e0600(snd, v1D0, 1, CharaGetCollWidth_238640(c));
                EffectSetParamFloat_2e0600(snd, v1D0, 2, CharaGetCollHeight_2385f0(c));
                c->fB1C = 0;
            }
        } else if (c->fA32 == 5) {
            c->fB18 = 1;
            c->fB1C = 0;
        }
    }
    if (c->fA36 == 16 && c->f424 == Leader()) FieldHudWidget80CarryOpenMaybe_203f70();
    if ((a58 = c->fA36) == 16 || a58 == 17) {
        ok = 0;
        q = Find(c->f3F4, (s32 *)ActCfgTableGetNullNameById_223ab0(c->f428, 3, 0));
        if (q) {
            FrameCalcWorldMatrix_148ff0(q, &m190);
            switch (TargetRefGetKind_2e7130(c->f9DC)) {
            case 8:
                if (TargetRefResolve_2e5ed0(c->f9DC, 0)) {
                    tg = TargetRefGetMapObj_2e7050(c->f9DC);
                    if (tg && tg->f32) {
                        MatToRotPos_1cade0(&v170, &v180, &m190);
                        v180.y -= 10.0f;
                        TargetRefDetachFromParent_2e5890(c->f9DC);
                        TargetRefSetTranslation_2e5bf0(c->f9DC, &v180);
                        TargetRefSetRotation_2e5d10(c->f9DC, &v170);
                        ok = 1;
                    }
                }
                break;
            case 2: {
                Ctx *cx;

                e = GetActionMgr_1fdb50();
                t2 = ActionMgrFindById_233b50(e, TargetRefGetId_2e7120(c->f9DC));
                cx = GetGameData_1fede0();
                u = ActorFindById_3eb870(cx, TargetRefGetId_2e7120(c->f9DC));
                if (t2 && u && c->f424 == t2->fB20 && Ready(t2)) {
                    ok = 1;
                    v160.x = t2->f4AC;
                    v160.y = t2->f4B0;
                    v160.z = t2->f4B4;
                    v160.w = 1.0f;
                    CharaGetPos_2388a0(t2, &v150);
                    VecCopy_1cbe30(&v140, &v150);
                    VecCopy_1cbe30(&v130, &v150);
                    f20 = 0.5f * (f32)((f32 *)D_0045B080)[0];
                    v140.y += f20;
                    v130.y += CharaGetCollHeight_2385f0(t2);
                    VecSub_1cbd00(&v130, &v130, &v140);
                    v4D4 = 1.0f;
                    bad = CollRaycastNearest_1c86e0(st->f14, st->f18, CharaGetCollIgnoreMask_238950(t2), &v140, &v130, &v4D4) >= 0;
                    if (!bad) {
                        VecCopy_1cbe30(&v120, &v150);
                        VecCopy_1cbe30(&v110, &v150);
                        { f32 d_ = ((f32 *)D_0045B080)[0];
                        v120.y += f20;
                        v110.y = v110.y - 100.0f * d_; }
                        VecSub_1cbd00(&v110, &v110, &v120);
                        v4D0 = 1.0f;
                        bad = CollRaycastNearest_1c86e0(st->f14, st->f18, CharaGetCollIgnoreMask_238950(t2), &v120, &v110, &v4D0) < 0;
                    }
                    if (!bad) {
                        VecCopy_1cbe30(&v100, &c->f70);
                        VecCopy_1cbe30(&vF0, &c->f70);
                        { f32 d_ = ((f32 *)D_0045B080)[0];
                        v100.y += f20;
                        vF0.y += CharaGetCollHeight_2385f0(c);
                        VecSub_1cbd00(&vF0, &vF0, &v100);
                        f21 = CharaGetCollRadius_2386a0(c) + D_0047DB20 * d_; }
                        cl = st->f24;
                        for (i = 0; i < st->f28; i++, cl++) {
                            if (!(cl->f46 & CharaGetCollIgnoreMask_238950(t2)) && CollTriVsCylinderMaybe_23a3e0(cl, &v100, vF0.y, f21)) {
                                bad = 1;
                                break;
                            }
                        }
                    }
                    if (!bad) {
                        VecCopy_1cbe30(&vE0, &v150);
                        VecCopy_1cbe30(&vD0, &v150);
                        vE0.y += f20;
                        vD0.y += CharaGetCollHeight_2385f0(t2);
                        VecSub_1cbd00(&vD0, &vD0, &vE0);
                        f20 = CharaGetCollRadius_2386a0(t2);
                        cl = st->f24;
                        for (i = 0; i < st->f28; i++, cl++) {
                            if (!(cl->f46 & CharaGetCollIgnoreMask_238950(t2)) && CollTriVsCylinderMaybe_23a3e0(cl, &vE0, vD0.y, f20)) {
                                bad = 1;
                                break;
                            }
                        }
                    }
                    if (!bad) {
                        Set3(&t2->f4AC, v150.x, v150.y, v150.z);
                        VecCopy_1cbe30(&v160, &v150);
                    }
                    if (u->Busy() || u->Dead()) ok = 0;
                    if (ok && bad && !(c->f3D0 & 0x2000000)) {
                        ok = 0;
                        GameSceneSoundSlot5PlaySeVol_1d05d0(w, 0x41, 1.0f);
                    }
                    if (!ok) {
                        CharaSetPosVec_2387e0(t2, &v160);
                        SrtSetPosFromVecThunk_1c7410(t2, &v160);
                        TargetRefSetTranslation_2e5bf0(c->f9DC, &v160);
                    }
                }
                break;
            }
            }
        }
        if (!ok) {
            CharaReleaseHeldTarget_2116b0(c, 0.0f, 0.0f, 0, 0.0f);
            c->f568 |= 0x20000000000ULL;
        }
    } else {
        CharaReleaseHeldTarget_2116b0(c, 0.0f, 0.0f, 0, 0.0f);
    }
}
