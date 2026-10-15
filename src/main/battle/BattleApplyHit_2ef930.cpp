#pragma optimization_level 3
#include "types.h"

typedef unsigned __int128 u128;

struct V4 {
    f32 x, y, z, w;
};

struct Skill {
    s16 id;
    u8 pad2[4];
    s16 lo : 5;
    s16 anim : 9;
    s16 hi : 2;
};

struct Sub {
    u8 pad0[4];
    s16 kind;
    u8 pad6[6];
    union {
        struct {
            s32 p;
            Skill *sk;
        } k3;
        struct {
            Skill *sk;
        } k2;
        struct {
            u8 padC[2];
            s16 a;
            s16 b;
            u8 pad12[2];
            f32 f;
            Skill *sk;
        } k1;
    } u;
    u8 pad1C[0x6C - 0x1C];
};

struct Act {
    V4 p;
    Sub sub;
    u32 x7C;
    s32 x80;
    s16 x84;
    s16 x86;
    s16 x88;
    s16 x8A;
    s16 x8C;
    s16 x8E;
    s32 x90;
    f32 x94;
    s32 x98;
    s32 x9C;
    s32 xA0;
    s16 xA4;
    s16 xA6;
};

struct Tgt {
    V4 p;
    s16 x10;
    s16 x12;
    s16 x14;
    s16 x16;
    s16 x18;
    s16 x1A;
    s16 x1C;
    s16 x1E;
};

struct Req {
    Act *a;
    Tgt *b;
};

struct Ent {
    s8 type;
    u8 x1;
    s8 cnt;
    u8 x3;
    s32 val;
};

struct Fl0 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
};

struct Fl2 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 lv : 4;
    u8 b7 : 1;
};

struct Eff {
    s16 id;
    u8 pad2[6];
    s32 x8;
};

struct Info {
    u8 pad0[0x18];
    u8 b18;
    u8 pad19;
    s16 n;
    Ent ent[4];
    u8 pad3C[4];
    Fl0 f0;
    Fl0 f1;
    Fl2 f2;
    u8 f3;
    u8 pad44[4];
    s64 z48;
    s64 z50;
    s64 z58;
    s64 z60;
    u8 pad68[4];
    s16 neff;
    u8 pad6E[2];
    Eff *eff[8];
};

struct Bits48 {
    u64 w;
};

struct BitRef {
    Bits48 *b;
    u32 pos;
};

struct Dbg {
    u8 pad0[0xC];
    s32 xC;
};

struct Sys1x {
    u8 pad0[0x18E];
    s16 x18E;
};

struct Sys1c {
    u8 pad0[0x22];
    s16 x22;
};

struct Sys1 {
    u8 pad0[0xC];
    Sys1c *xC;
    u8 pad10[8];
    Sys1x *x18;
};

struct Wld {
    u8 pad0[0x4344];
    s32 x4344;
};

struct Unit {
    u8 pad0[0x3D0];
    u64 x3D0;
    u8 pad3D8[0xA44 - 0x3D8];
    u32 xA44;
};

struct Chr {
    u8 pad0[0x4FC];
    s32 x4FC;
};

struct Fx {
    u8 pad0[0x80];
    u32 x80;
};

struct Fx20 {
    u8 b[0x20];
} __attribute__((aligned(16)));

struct Eff3 {
    V4 p;
    V4 v;
    f32 ang;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    s32 x38;
};

class Obj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual s32 v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual s32 v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual s32 v151();
    virtual void v152();
    virtual void v153(f32);
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158(void *);
    virtual void v159(struct Info *);
    virtual void v160();
    virtual void v161();
    virtual void v162();
    virtual void v163();
    virtual void v164();
    virtual void v165();
    virtual void v166();
    virtual void v167();
    virtual void v168();
    virtual void v169();
    virtual void v170();
    virtual void v171();
    virtual void v172();
    virtual void v173();
    virtual void v174();
    virtual void v175();
    virtual void v176();
    virtual void v177();
    virtual void v178();
    virtual void v179();
    virtual void v180();
    virtual void v181();
    virtual void v182();
    virtual void v183();
    virtual void v184();
    virtual void v185();
    virtual void v186();
    virtual void v187();
    virtual void v188();
    virtual void v189();
    virtual void v190();
    virtual void v191();
    virtual void v192();
    virtual void v193();
    virtual void v194();
    virtual void v195(f32);
    virtual f32 v196();
    virtual void v197();
    virtual void v198();
    virtual void v199();
    virtual void v200();
    virtual void v201();
    virtual void v202();
    virtual void v203();
    virtual void v204();
    virtual void v205();
    virtual void v206();
    virtual void v207();
    virtual void v208();
    virtual void v209();
    virtual void v210();
    virtual void v211();
    virtual void v212();
    virtual void v213();
    virtual void v214();
    virtual void v215();
    virtual void v216();
    virtual void v217();
    virtual void v218();
    virtual void v219();
    virtual void v220();
    virtual void v221();
    virtual void v222();
    virtual void v223();
    virtual void v224();
    virtual void v225();
    virtual void v226();
    virtual void v227();
    virtual void v228();
    virtual void v229();
    virtual void v230();
    virtual void v231();
    virtual void v232();
    virtual void v233();
    virtual void v234();
    virtual void v235();
    virtual void v236();
    virtual void v237();
    virtual s32 v238();
    virtual void v239();
    virtual void v240();
    virtual void v241();
    virtual void v242();
    virtual void v243();
    virtual void v244();
    virtual void v245();
    virtual void v246();
    virtual void v247();
    virtual void v248();
    virtual void v249();
    virtual void v250();
    virtual void v251();
    virtual void v252();
    virtual void v253();
    virtual void v254();
    virtual void v255();
    virtual void v256();
    virtual f32 v257();
};

class Cam {
public:
    u8 pad0[0xC0];
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    virtual void c4();
    virtual void c5();
    virtual void c6();
    virtual void c7();
    virtual void c8();
    virtual void c9();
    virtual void c10();
    virtual void c11();
    virtual void c12();
    virtual void c13();
    virtual void c14();
    virtual void c15();
    virtual void c16();
    virtual void c17();
    virtual void c18();
    virtual void c19();
    virtual void c20();
    virtual void c21();
    virtual void c22();
    virtual void c23();
    virtual void c24();
    virtual void c25();
    virtual void c26();
    virtual void c27();
    virtual void c28();
    virtual void c29();
    virtual void c30();
    virtual void c31();
    virtual void c32();
    virtual void c33();
    virtual void c34();
    virtual void c35();
    virtual void c36();
    virtual void c37();
    virtual void c38();
    virtual void c39(void *);
};


extern "C" {
Sys1 *GetGameData_1fede0(void);
void *GetActionMgr_1fdb50(void);
Wld *GetCurrentScene_1f5be0(void);
Obj *ActorFindById_3eb870(void *, s32);
Unit *ActionMgrFindById_233b50(void *, s32);
void CharaGetPos_2388a0(Unit *, V4 *);
void CharaGetRot_2388b0(Unit *, V4 *);
f32 VecDistance_13d3d0(Act *, Tgt *);
s32 AbilityDataGetCompositeId_3f5e10(s32);
void CharaAddFlags_212460(Unit *, u64);
void VecSub_1cbd00(V4 *, V4 *, V4 *);
void VecScaleToLength_1cb510(V4 *, V4 *, f32);
void GuardEffectSpawn_2d8fb0(V4 *, V4 *);
s32 GetEventObjMgr_2d1960(void);
s32 EvMapObjFindById_2e9810(s32, s32);
s32 EvMapObjGetAreaObjMaybe_3669f0(s32, s32);
void NodeGetTranslation_186650(s32, V4 *);
f32 Sinf_128fd0(f32);
f32 Cosf_128d30(f32);
void VecNormalize_1cbb80(V4 *, V4 *);
void VecLerp_1cbb20(V4 *, V4 *, V4 *, f32);
f32 RandFloat_13c010(void);
void EvMapObjThrowStart_3661f0(s32, s32, V4 *, s32, void *);
void VecCopy_1cbe30(V4 *, V4 *);
s32 GetBattleEffectPool_2d9030(void);
void BattleEffectSpawnInFreeSlot_2d3c60(s32, V4 *);
s32 GetEffectMgr_2d9040(void);
void EffectCreateByName_2e1020(Fx20 *, s32, void *, s32);
void EffectSetId_2e0100(s32, Fx20 *, s32);
void EffectSetPos_2e0bb0(s32, Fx20 *, void *);
s32 GetObjRefTable_313de0(void);
Fx *HandleRegistryLookup_314aa0(s32, s32);
s32 CharaGetBaseActionMode_213830(Unit *);
s32 CharaGetId_214a80(Unit *);
void ActionResultClear_3a6e60(Info *);
void ActionResultSetupMaybe_3a6d70(Info *, void *, s32, s32, s32, s32, f32);
s32 CharaGetActionMode_213850(Unit *);
void Fprintf_12f9a0(s32, void *);
void Abort_12de80(void);
void EvSpawnChrMonographs_2e91e0(s32, s32, f32, f32);
void CharaSetInvincibleTime_2138a0(Unit *, f32);
Cam *ObjRecGetLiveObject_1c3bc0(Wld *, s32);
void CameraShakeStart_3058c0(Cam *, f32, f32, f32, f32);
s32 TargetMngHasTargetId_313bf0(void);
s32 CharaGetTargetRef_214a30(Unit *);
void TargetRefSetAttachPoint_2e65f0(s32, s32, s32, s32);
void TargetMngClearTarget_313c00(void);
void TargetMngSetTarget_313ad0(s32);
void EffectSpawnBarrierBreak_2d7c60(s32, V4 *);
Obj *ActorCastToUnit_3b8770(Obj *);
void EffectSpawnBarrierGuard_2d7d20(s32, V4 *);
void LightningRequestOnObj_2d7de0(s32, s32);
void EffectSpawnHitBullet_2d7eb0(s32, V4 *);
void EffectSpawnHitBulletAlt_2d7e00(s32, V4 *);
void EffectReleaseByNameKey_2e0e50(s32, s32, s32);
void VecAdd_1cbdc0(V4 *, V4 *, V4 *);
void GuardWaveEffectSpawnUnique_2d8ea0(V4 *, s32, s32, f32);
f64 dpmul(f64, f64);
Obj *ActorCastToChara_3b87b0(Obj *);
s32 CharaIsPartyLeader_3ae1a0(Obj *);
s32 GetDamagePopupList_2d9020(void);
void DamagePopupSpawn_2d2da0(s32, s32, V4 *, V4 *, s32, s32, f32);
V4 *CharaGetMoveReq_2149e0(Unit *);
Eff3 *CharaGetHitInfo_214a00(Unit *);
s32 AtkPrmGetKnockbackDirMode_3f8c90(Skill *);
void VecCross_1cb9f0(V4 *, V4 *, V4 *);
f32 VecDotDiff_1cba40(V4 *, V4 *, V4 *);
void VecNegate_1cb9a0(V4 *, V4 *);
f32 CharaGetBodyWeight_2385b0(Unit *);
f32 Atan2f_1291a8(f32, f32);
void BurningStrikeEffectSpawn_2d7b10(s32, f32);
f32 AtkPrmGetKnockbackSpeed_3f8c80(Skill *);
f32 AtkPrmGetKnockbackLift_3f8c70(Skill *);
void VecScale_1cbca0(V4 *, V4 *, f32);
void CharaMoveReqSet_219310(V4 *, V4 *, s32, s32);
void CharaGetVelocity_238890(Unit *, V4 *);
f32 VecDot3_1cba90(V4 *, V4 *);
f32 VecLengthSq_1cb470(V4 *);
void CharaSetVelocityFromVec_238790(Unit *, V4 *);
void EffectSpawnFinishingBlow_2d81b0(s32);
s32 GameSceneSoundSlot5GetHandle_1d0790(Wld *);
s32 SoundNextPlayHandle_1b81c0(void);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
void CharaRequestTint_213fd0(Unit *, s32, s32, f32, f32, f32, f32, f32);
s32 GetHpGaugeThin_206220(void);
void HpGaugeShow_31d2b0(s32, s32, f32);
void BattleHitNotifyStubRelated_1f9760(s32, s32, s32);
u64 CharaGetFlags_2124b0(Unit *);
void CharaSetFlags_212470(Unit *, u64);
void ExecInfoInit_3a7940(Sub *);
void ExecInfoInitFromObj_3a7790(Sub *, s32, void *);
Chr *ObjRecGetLiveObject_1c4a90(Wld *, s32);
s32 BattleApplyHit_2ef930(Req *);
}

extern "C" u8 D_00461B10[];
extern "C" u8 D_00461B20[];
extern "C" u8 D_00461B30[];
extern "C" u8 D_00461B48[];
extern "C" u8 D_0045CB40[];
extern "C" Dbg *D_00449858[];
extern "C" f32 D_0045B080[];
extern "C" f32 D_0047D1E0 __attribute__((section(".sdata")));
extern "C" f32 D_0047D240 __attribute__((section(".sdata")));
extern "C" f32 D_0047D244 __attribute__((section(".sdata")));
extern "C" f32 D_0047D278 __attribute__((section(".sdata")));
extern "C" f32 D_0047D288 __attribute__((section(".sdata")));
extern "C" f32 D_0047D28C __attribute__((section(".sdata")));
extern "C" f32 D_0047EFE0 __attribute__((section(".sdata")));
extern "C" f32 D_0047EFE4 __attribute__((section(".sdata")));
extern "C" f32 D_0047EFE8 __attribute__((section(".sdata")));
extern "C" f32 D_0047EFEC __attribute__((section(".sdata")));
extern "C" f32 D_0047EFF0 __attribute__((section(".sdata")));
extern "C" f32 D_0047EFF4 __attribute__((section(".sdata")));
extern "C" f32 D_0047EFF8 __attribute__((section(".sdata")));
extern "C" f32 D_0047EFFC __attribute__((section(".sdata")));

static inline void clr(void *p, s32 n)
{
    u8 *q;
    s32 c;
    c = n;
    q = (u8 *)p;
    if (q != NULL) {
        do {
            *q++ = 0;
        } while (--c);
    }
}

static inline bool InParty(s32 i)
{
    bool r = false;
    if (i >= 0 && i < 12) r = true;
    return r;
}

struct BS48;
struct BRef {
    BS48 *b;
    u32 pos;
    inline operator bool() const;
};

struct BS48 {
    u64 w;
    inline bool test(u32 pos) const
    {
        if (pos >= 48) {
            Fprintf_12f9a0(D_00449858[0]->xC, D_0045CB40);
            Abort_12de80();
        }
        return (w & ((u64)1 << pos)) != 0;
    }
    inline BRef operator[](u32 pos)
    {
        BRef r;
        r.b = this;
        r.pos = pos;
        return r;
    }
};

inline BRef::operator bool() const
{
    return b->test(pos);
}

template <int N> struct TBits {
    u64 w;
    bool test(u32 pos) const
    {
        BitRef r;
        r.b = (Bits48 *)this;
        r.pos = pos;
        if (pos >= N) {
            Fprintf_12f9a0(D_00449858[0]->xC, D_0045CB40);
            Abort_12de80();
        }
        return ((*(Bits48 *volatile *)&r.b)->w & ((u64)1 << pos)) != 0;
    }
};

template <int N> struct TRef {
    TBits<N> *b;
    u32 pos;
    operator bool() const { return b->test(pos); }
};

template <int N> struct TBits2 {
    u64 w;
    TRef<N> operator[](u32 pos)
    {
        TRef<N> r;
        r.b = (TBits<N> *)this;
        r.pos = pos;
        return r;
    }
};

template <int N> static bool TTest(TBits<N> *b, u32 pos)
{
    BitRef r;
    r.b = (Bits48 *)b;
    r.pos = pos;
    if (pos >= N) {
        Fprintf_12f9a0(D_00449858[0]->xC, D_0045CB40);
        Abort_12de80();
    }
    return ((*(Bits48 *volatile *)&r.b)->w & ((u64)1 << pos)) != 0;
}

static inline bool Test48(Bits48 *p, s32 n)
{
    BitRef r;
    r.b = p;
    r.pos = n;
    if ((u32)n >= 0x30) {
        Fprintf_12f9a0(D_00449858[0]->xC, D_0045CB40);
        Abort_12de80();
    }
    return ((*(Bits48 *volatile *)&r.b)->w & (1ULL << n)) != 0;
}

static inline bool BitTest(Bits48 *b, u32 pos)
{
    BitRef r;
    r.b = b;
    r.pos = pos;
    if (pos >= 48) {
        Fprintf_12f9a0(D_00449858[0]->xC, D_0045CB40);
        Abort_12de80();
    }
    return (r.b->w & ((u64)1 << pos)) != 0;
}

extern "C" s32 BattleApplyHit_2ef930(Req *r)
{
    Req r2;
    V4 pos;
    V4 rot;
    V4 v4A0;
    V4 v490;
    V4 v480;
    V4 v470;
    V4 v460;
    Fx20 v440;
    V4 v430;
    Info info;
    V4 v390;
    Fx20 v370;
    Fx20 v350;
    V4 v340;
    V4 v330;
    V4 v320;
    V4 v310;
    V4 v300;
    V4 v2F0;
    V4 v2E0;
    V4 v2D0;
    V4 v2C0;
    V4 v2B0;
    Act a2;
    Tgt b2;
    Wld *wld;
    Obj *obj;
    s32 st;
    Sys1 *s2;
    bool flagB;
    bool flagA;
    bool flagC;
    bool f17F;
    bool f17E;
    bool f160;
    s32 u;
    s32 h2;
    s32 j;
    s32 cnt;
    s32 step;
    s32 pass;
    V4 *col;
    bool skip;
    V4 *v;
    Eff3 *e3;
    Cam *cm;
    f64 d15;
    Tgt *b;
    Sub *sub;
    Sys1 *s1;
    void *map;
    Unit *m;
    f32 spd;
    f32 dist;
    Skill *sk;
    s32 anim;
    Obj *t;
    Unit *m2;
    s32 h;
    s32 c;
    Act *a;

    if (r == 0 || (a = r->a) == 0 || (b = r->b) == 0) return 0;
    sub = &a->sub;
    s1 = GetGameData_1fede0();
    map = GetActionMgr_1fdb50();
    wld = GetCurrentScene_1f5be0();
    if (a->x8A != 1) return 0;
    obj = ActorFindById_3eb870(s1, a->x86);
    if (obj == 0) return 0;
    m = ActionMgrFindById_233b50(map, a->x86);
    if (m == 0) return 0;
    CharaGetPos_2388a0(m, &pos);
    CharaGetRot_2388b0(m, &rot);
    spd = 0.0f;
    dist = spd;
    if (a->p.x != 0.0f || a->p.z != 0.0f) {
        if (b->p.x != 0.0f || b->p.z != 0.0f) {
            dist = VecDistance_13d3d0(a, b);
        }
    }
    st = -1;
    sk = 0;
    switch (sub->kind) {
    case 1:
        sk = sub->u.k1.sk;
        sub->u.k1.a = a->xA4;
        sub->u.k1.b = a->xA6;
        sub->u.k1.f = 1.0f;
        if (sk == 0) return 0;
        spd = dist;
        break;
    case 2:
        sk = sub->u.k2.sk;
        if (sk == 0) return 0;
        spd = dist;
        break;
    case 3:
        sk = sub->u.k3.sk;
        if (sub->u.k3.p != 0) st = AbilityDataGetCompositeId_3f5e10(sub->u.k3.p);
        spd = dist;
        break;
    case 4:
        sk = sub->u.k3.sk;
        break;
    case 5:
        sk = sub->u.k2.sk;
        break;
    default:
        break;
    }
    anim = -1;
    if (sk != 0) anim = sk->anim;
    if (a->xA0 >= 0) anim = a->xA0;
    switch (b->x16) {
    case 4: {
        u32 fl = a->x7C;
        if (!(fl & 0xE0)) return 0;
        if (fl & 0x20) {
            CharaAddFlags_212460(m, (u64)0x400 << 32);
            {
                bool ok = false;
                if (b->x12 >= 0 && b->x12 < 12) ok = true;
                anim = ok ? 1 : 2;
            }
            VecSub_1cbd00(&v4A0, &a->p, &b->p);
            v4A0.y = 0.0f;
            VecScaleToLength_1cb510(&v4A0, &v4A0, D_0047D278);
            v4A0.y = D_0047D240;
            GuardEffectSpawn_2d8fb0(&b->p, &v4A0);
        } else {
            h = EvMapObjFindById_2e9810(GetEventObjMgr_2d1960(), b->x12);
            if (h == 0) return 0;
            c = EvMapObjGetAreaObjMaybe_3669f0(h, b->x14);
            if (c == 0) return 0;
            if (a->x7C & 0x80) {
                NodeGetTranslation_186650(c, &v480);
                v470.x = Sinf_128fd0(rot.y);
                v470.y = 0.0f;
                v470.z = Cosf_128d30(rot.y);
                v470.w = 0.0f;
                VecSub_1cbd00(&v490, &v480, &pos);
                v490.y = 0.0f;
                VecNormalize_1cbb80(&v490, &v490);
                VecLerp_1cbb20(&v490, &v490, &v470, 0.25f);
                VecScaleToLength_1cb510(&v490, &v490, 12.0f);
                v490.y = 6.0f + 2.0f * RandFloat_13c010();
            } else {
                v490.x = 0.0f;
                v490.y = -2.0f;
                v490.z = 0.0f;
                v490.w = 0.0f;
            }
            EvMapObjThrowStart_3661f0(h, c, &v490, a->x86, D_00461B10);
            VecCopy_1cbe30(&v460, &b->p);
            BattleEffectSpawnInFreeSlot_2d3c60(GetBattleEffectPool_2d9030(), &v460);
        }
        break;
    }
    case 5: {
        s32 h;
        Fx *p;
        if (!(a->x7C & 0x400)) return 0;
        h = GetEffectMgr_2d9040();
        EffectCreateByName_2e1020(&v440, h, D_00461B20, -1);
        EffectSetId_2e0100(h, &v440, -1);
        EffectSetPos_2e0bb0(h, &v440, &a->p);
        p = HandleRegistryLookup_314aa0(GetObjRefTable_313de0(), b->x10);
        if (p != 0) p->x80 |= 8;
        VecCopy_1cbe30(&v430, &b->p);
        BattleEffectSpawnInFreeSlot_2d3c60(GetBattleEffectPool_2d9030(), &v430);
        break;
    }
    default: {
        if (b->x16 != 1) return 0;
        bool self;
        s32 i;
        bool hit;
        s32 dmg;
        f32 mul;
        f32 d;
        t = ActorFindById_3eb870(s1, b->x12);
        if (t == 0) return 0;
        m2 = ActionMgrFindById_233b50(map, b->x12);
        if (m2 == 0) return 0;
        if (t->v46()) return 0;
        if (b->x12 >= 0 && b->x12 < 12) {
            if (CharaGetBaseActionMode_213830(m2) == 0) return 0;
        }
        s2 = GetGameData_1fede0();
        {
            s32 me = s2->x18->x18E;
            self = me == CharaGetId_214a80(m);
        }
        info.z48 = 0;
        info.z50 = 0;
        flagB = false;
        flagA = true;
        info.z58 = 0;
        info.z60 = 0;
        flagC = false;
        ActionResultClear_3a6e60(&info);
        ActionResultSetupMaybe_3a6d70(&info, sub, b->x12, b->x1C, 1, b->x1A + 1, spd);
        t->v159(&info);
        hit = false;
        dmg = 0;
        f17F = false;
        f17E = false;
        f160 = false;
        mul = 1.0f;
        for (i = 0; i < info.n; i++) {
            Ent *e = &info.ent[i];
            f32 k;
            if (e == 0) continue;
            switch (e->type) {
            case 0:
                break;
            case 1:
                hit = true;
                dmg += e->val;
                break;
            case 2:
                hit = true;
                break;
            case 3:
                hit = true;
                break;
            case 4:
                hit = true;
                break;
            case 5:
                hit = true;
                f17F = true;
                break;
            case 6:
                hit = true;
                f17E = true;
                break;
            case 7:
                hit = false;
                f160 = true;
                break;
            }
            k = 1.0f;
            if (e->cnt > 1) k = 1.0f + 0.25f * (f32)(e->cnt - 1);
            if (mul < k) mul = k;
        }
        if (t->v46()) flagB = true;
        if (info.f0.b6) {
            CharaAddFlags_212460(m2, (u64)0x200 << 32);
        } else if (info.f0.b4) {
            CharaAddFlags_212460(m2, (u64)4 << 32);
            CharaAddFlags_212460(m2, (u64)8 << 32);
        } else if (info.f0.b1) {
            CharaAddFlags_212460(m2, (u64)4 << 32);
            if (CharaGetActionMode_213850(m2) == 4) CharaAddFlags_212460(m2, (u64)8 << 32);
        }
        if (info.f1.b1) {
            CharaAddFlags_212460(m, (u64)0x400 << 32);
            {
                bool ok = false;
                if (b->x12 >= 0 && b->x12 < 12) ok = true;
                anim = ok ? 1 : 2;
            }
            flagA = false;
            flagC = true;
        }
        if (info.f1.b5) CharaAddFlags_212460(m2, (u64)0x800 << 32);
        if (info.f1.b7) CharaAddFlags_212460(m2, (u64)0x1000 << 32);
        CharaAddFlags_212460(m2, (u64)2 << 32);
        if (((BS48 *)&info.z58)->operator[](0x1F)) {
            EvSpawnChrMonographs_2e91e0(GetEventObjMgr_2d1960(), b->x12, 0.0f, 10.0f);
        }
        if (a->x7C & 0x1000) m2->xA44 |= 0x40000;
        if (sk->id == 0x263) CharaSetInvincibleTime_2138a0(m2, 60.0f);
        if (a->xA6 > 0) {
            CameraShakeStart_3058c0(ObjRecGetLiveObject_1c3bc0(wld, wld->x4344), 0.0f, 25.0f, D_0047D244, D_0047D1E0);
        } else if (self && s2->xC->x22 == 1 && TargetMngHasTargetId_313bf0() == 0) {
            u = CharaGetTargetRef_214a30(m);
            TargetRefSetAttachPoint_2e65f0(u, CharaGetId_214a80(m2), 0x82, 0);
            TargetMngClearTarget_313c00();
            TargetMngSetTarget_313ad0(u);
        }
        VecCopy_1cbe30(&v390, &b->p);
        v390.y = v390.y + 5.0f;
        if (info.f2.b1) EffectSpawnBarrierBreak_2d7c60(CharaGetId_214a80(m2), &v390);
        if (info.f1.b2) {
            Obj *x;
            flagC = true;
            x = ActorCastToUnit_3b8770(t);
            if (x != 0 && x->v145() != 0 && t->v196() <= 0.0f) {
                EffectSpawnBarrierGuard_2d7d20(CharaGetId_214a80(m2), &v390);
                flagC = false;
            }
        }
        if (flagA && !info.f0.b2) BattleEffectSpawnInFreeSlot_2d3c60(GetBattleEffectPool_2d9030(), &v390);
        h2 = GetEffectMgr_2d9040();
        if (sk->id == 0x12) {
            EffectCreateByName_2e1020(&v370, h2, D_00461B30, -1);
            EffectSetId_2e0100(h2, &v370, CharaGetId_214a80(m2));
            EffectSetPos_2e0bb0(h2, &v370, &v390);
        } else if (!info.f0.b2 && !(a->x7C & 0x20000)) {
            for (j = 0; j < info.neff; j++) {
                Eff *ef = info.eff[j];
                switch (ef->id) {
                case 0x641:
                    LightningRequestOnObj_2d7de0(CharaGetId_214a80(m2), 0x1E);
                    break;
                case 0x645:
                    EffectSpawnHitBullet_2d7eb0(CharaGetId_214a80(m2), &v390);
                    break;
                case 0x64B:
                    EffectSpawnHitBulletAlt_2d7e00(CharaGetId_214a80(m2), &v390);
                    break;
                case 0x646:
                    flagC = false;
                default: {
                    EffectReleaseByNameKey_2e0e50(h2, ef->x8, CharaGetId_214a80(m2));
                    EffectCreateByName_2e1020(&v350, h2, (void *)ef->x8, 0xFA0);
                    EffectSetId_2e0100(h2, &v350, CharaGetId_214a80(m2));
                    EffectSetPos_2e0bb0(h2, &v350, &v390);
                    break;
                }
                }
            }
        }
        if (flagC) {
            Cam *cam;
            Wld *w2;
            VecSub_1cbd00(&v340, &a->p, &v390);
            v340.y = 0.0f;
            VecScaleToLength_1cb510(&v340, &v340, D_0047D278);
            v340.y = D_0047D240;
            GuardEffectSpawn_2d8fb0(&v390, &v340);
            w2 = GetCurrentScene_1f5be0();
            cam = ObjRecGetLiveObject_1c3bc0(w2, w2->x4344);
            if (cam != 0) {
                cam->c39(&v330);
                VecSub_1cbd00(&v330, &v330, &v390);
                VecScaleToLength_1cb510(&v330, &v330, D_0045B080[0]);
                VecAdd_1cbdc0(&v390, &v390, &v330);
            }
            GuardWaveEffectSpawnUnique_2d8ea0(&v390, CharaGetId_214a80(m2), CharaGetId_214a80(m), 20.0f);
        }
        if (hit) {
            if (dmg >= 0 || f17F || f17E) {
                cnt = 0;
                pass = 1;
                step = 0;
                d15 = 15.0 * mul;
                do {
                    s32 type;
                    f32 sc;
                    cnt += step;
                    v320.x = D_0047EFE0;
                    v320.y = D_0047EFE4;
                    v320.z = D_0047EFE8;
                    v320.w = D_0047EFEC;
                    col = 0;
                    type = 0;
                    sc = 1.0f;
                    if (pass == 1) {
                        if (!f17F) goto next;
                        type = 3;
                        step += 7;
                    } else if (f17E) {
                        type = 4;
                    } else {
                        if (dmg < 0) goto next;
                        if (a->xA6 > 0) {
                            sc = 2.0f;
                        } else {
                            Obj *x;
                            sc = mul;
                            x = ActorCastToChara_3b87b0(t);
                            if (x != 0) {
                                col = &v320;
                                if (CharaIsPartyLeader_3ae1a0(x) != 0 && !(mul <= 1.0f)) {
                                    cm = ObjRecGetLiveObject_1c3bc0(wld, wld->x4344);
                                    CameraShakeStart_3058c0(cm, (f32)d15, 0.0f, D_0047D244, D_0047D1E0);
                                }
                            }
                        }
                    }
                    skip = false;
                    if (type == 4) {
                        if (!(t->v196() <= 0.0f)) {
                            skip = true;
                        } else {
                            t->v195(15.0f);
                        }
                    } else {
                        t->v195(0.0f);
                    }
                    if (!skip) {
                        s32 w = GetDamagePopupList_2d9020();
                        if (col != 0) {
                            DamagePopupSpawn_2d2da0(w, dmg, &b->p, col, type, (s16)cnt, sc);
                        } else {
                            DamagePopupSpawn_2d2da0(w, dmg, &b->p, 0, type, (s16)cnt, sc);
                        }
                    }
                next:;
                } while (++pass <= 2);
            }
        }
        {
            v = CharaGetMoveReq_2149e0(m2);
            e3 = CharaGetHitInfo_214a00(m2);
            e3->x24 = -1;
            e3->x28 = dmg;
            e3->x2C = a->x86;
            e3->x30 = sk->id;
            e3->x34 = b->x12;
            e3->x38 = b->x18;
            VecCopy_1cbe30(&e3->p, &b->p);
            clr(&v300, 16);
            CharaGetPos_2388a0(m2, &v310);
            if (sk != 0) {
                switch (AtkPrmGetKnockbackDirMode_3f8c90(sk)) {
                case 0x10:
                    VecSub_1cbd00(&v300, &v310, &a->p);
                    break;
                case 0x20: {
                    v2F0.x = D_0047EFF0;
                    v2F0.y = D_0047EFF4;
                    v2F0.z = D_0047EFF8;
                    v2F0.w = D_0047EFFC;
                    VecSub_1cbd00(&v2E0, &v310, &a->p);
                    VecCross_1cb9f0(&v300, &v2F0, &v2E0);
                    if (VecDotDiff_1cba40(&v310, &b->p, &v300) < 0.0f) VecNegate_1cb9a0(&v300, &v300);
                    break;
                }
                default:
                    VecSub_1cbd00(&v300, &v310, &b->p);
                    break;
                }
            }
            mul = 1.0f;
            d = CharaGetBodyWeight_2385b0(m2);
            if (!(d <= 100.0f)) mul = D_0047D278;
            if (!(d <= 300.0f)) mul = D_0047D288;
            if (!(d <= 500.0f)) mul = D_0047D28C;
            v300.y = 0.0f;
            e3->ang = Atan2f_1291a8(v300.x, v300.z);
            if ((info.f3 & 0xF) > 0) BurningStrikeEffectSpawn_2d7b10(b->x12, e3->ang);
            if (sk != 0) {
                f32 s;
                VecNormalize_1cbb80(&v300, &v300);
                if (sk != 0 && a->x94 <= 0.0f) {
                    s = mul * AtkPrmGetKnockbackSpeed_3f8c80(sk);
                } else {
                    s = a->x94 / 8.0f;
                }
                VecScale_1cbca0(&v300, &v300, s);
                v300.y = mul * AtkPrmGetKnockbackLift_3f8c70(sk);
            }
            VecCopy_1cbe30(&e3->v, &v300);
            if (!(m2->x3D0 & ((u64)2 << 32))) {
                f32 s;
                VecSub_1cbd00(&v2D0, &v310, &a->p);
                v2D0.y = 0.0f;
                VecNormalize_1cbb80(&v2D0, &v2D0);
                if (sk != 0 && a->x94 <= 0.0f) {
                    s = 8.0f * mul * AtkPrmGetKnockbackSpeed_3f8c80(sk);
                } else {
                    s = a->x94;
                }
                VecScale_1cbca0(&v2D0, &v2D0, s);
                CharaMoveReqSet_219310(v, &v2D0, 10, 3);
                if (m->xA44 & 0x20) {
                    f32 q;
                    CharaGetVelocity_238890(m, &v2C0);
                    q = 1.125f * VecDot3_1cba90(&v2C0, v);
                    VecScale_1cbca0(&v2B0, v, q / VecLengthSq_1cb470(v));
                    VecSub_1cbd00(&v2C0, &v2C0, &v2B0);
                    v2C0.y = 1.0f + 2.0f * RandFloat_13c010();
                    CharaSetVelocityFromVec_238790(m, &v2C0);
                    CharaAddFlags_212460(m, (u64)2 << 32);
                }
            }
        }
        if (flagB) {
            s32 k;
            EffectSpawnFinishingBlow_2d81b0(CharaGetId_214a80(m2));
            k = GameSceneSoundSlot5GetHandle_1d0790(wld);
            SoundPlayScaledVolume_1b9520(k, 0x56, SoundNextPlayHandle_1b81c0(), 1.0f);
        }
        if (dmg > 0) {
            Obj *y;
            bool has;
            s32 lv;
            CharaRequestTint_213fd0(m2, 3, 2, 250.0f, 118.0f, 80.0f, 5.0f, 1.0f);
            y = ActorCastToUnit_3b8770(t);
            if (y != 0 && y->v238() == 0) {
                s32 z = GetHpGaugeThin_206220();
                s32 k = CharaGetId_214a80(m2);
                HpGaugeShow_31d2b0(z, k, y->v257());
            }
            has = false;
            lv = 0;
            if (info.f2.b0) {
                has = true;
                lv = info.f2.lv;
            }
            if (has) {
                BattleHitNotifyStubRelated_1f9760(CharaGetId_214a80(m), CharaGetId_214a80(m2), lv);
                obj->v153((f32)obj->v151());
                CharaSetFlags_212470(m2, CharaGetFlags_2124b0(m2) & ~((u64)8 << 32));
            }
        }
        if (f160 && st == 0x1391) {
            CharaRequestTint_213fd0(m2, 3, 2, 80.0f, 250.0f, 110.0f, 60.0f, 1.0f);
        }
        {
            switch (sk->id) {
            case 0x258:
            case 0x25A:
            case 0x260:
            case 0x25D:
            case 0x264: {
                Obj *o;
                ExecInfoInit_3a7940(&a2.sub);
                a2.p.x = 0.0f;
                a2.p.y = 0.0f;
                a2.p.z = 0.0f;
                a2.p.w = 1.0f;
                ExecInfoInit_3a7940(&a2.sub);
                a2.x7C = 0;
                a2.x80 = 0;
                a2.x84 = -1;
                a2.x86 = -1;
                a2.x88 = -1;
                a2.x8A = -1;
                a2.x8C = 0;
                a2.x8E = 0;
                a2.x90 = 0;
                a2.x94 = 0.0f;
                a2.x98 = 0;
                a2.x9C = 0;
                a2.xA0 = -1;
                a2.xA4 = 0;
                a2.xA6 = 0;
                b2.p.x = 0.0f;
                b2.p.y = 0.0f;
                b2.p.z = 0.0f;
                b2.p.w = 1.0f;
                b2.x10 = -1;
                b2.x12 = -1;
                b2.x14 = -1;
                b2.x16 = -1;
                b2.x18 = -1;
                b2.x1A = -1;
                b2.x1C = -1;
                r2.a = &a2;
                r2.b = &b2;
                a2.x84 = b->x10;
                a2.x86 = b->x12;
                a2.x88 = b->x14;
                a2.x8A = b->x16;
                CharaGetPos_2388a0(m2, &a2.p);
                b2.x10 = a->x84;
                b2.x12 = a->x86;
                b2.x14 = a->x88;
                b2.x16 = a->x8A;
                o = ActorFindById_3eb870(s2, a2.x86);
                if (o != 0) {
                    Obj *oo = ActorCastToUnit_3b8770(o);
                    if (oo != 0) {
                        ExecInfoInitFromObj_3a7790(&a2.sub, a2.x86, D_00461B48);
                        oo->v158(&a2.sub);
                        BattleApplyHit_2ef930(&r2);
                    }
                }
            }
            break;
            }
        }
        break;
    }
    }
    if (anim != 0) {
        if (anim < 0) {
            Chr *ch = ObjRecGetLiveObject_1c4a90(wld, CharaGetId_214a80(m));
            if (ch != 0) {
                s32 hh = ch->x4FC;
                SoundPlayScaledVolume_1b9520(hh, -anim, SoundNextPlayHandle_1b81c0(), 1.0f);
            }
        } else {
            s32 hh = GameSceneSoundSlot5GetHandle_1d0790(wld);
            SoundPlayScaledVolume_1b9520(hh, anim, SoundNextPlayHandle_1b81c0(), 1.0f);
        }
    }
    return 1;
}
