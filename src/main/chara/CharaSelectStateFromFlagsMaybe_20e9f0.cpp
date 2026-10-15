#include "types.h"
#pragma inline_depth(8)

typedef struct Pos {
    u8 pad0[0x1F0];
    s32 v[3];
} Pos;

typedef struct Actor {
    u8 pad0[0x3D0];
    u64 x3D0;
    u32 x3D8;
    u8 pad3DC[0x3F4 - 0x3DC];
    Pos *x3F4;
    u8 pad3F8[0x424 - 0x3F8];
    s16 x424;
    u8 pad426[0xA2C - 0x426];
    s16 xA2C;
    s16 xA2E;
    s16 xA30;
    s16 xA32;
    s16 xA34;
    s16 xA36;
    s16 xA38;
    u8 padA3A[0xA44 - 0xA3A];
    u32 xA44;
} Actor;

class VObj {
public:
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
    virtual s32 v13();
    virtual s32 v14();
    virtual s32 v15();
    virtual s32 v16();
    virtual s32 v17();
    virtual s32 v18();
    virtual s32 v19();
    virtual s32 v20();
    virtual s32 v21();
    virtual s32 v22();
    virtual s32 v23();
    virtual s32 v24();
    virtual s32 v25();
    virtual s32 v26();
    virtual s32 v27();
    virtual s32 v28();
    virtual s32 v29();
    virtual s32 v30();
    virtual s32 v31();
    virtual s32 v32();
    virtual s32 v33();
    virtual s32 v34();
    virtual s32 v35();
    virtual s32 v36();
    virtual s32 v37();
    virtual s32 v38();
    virtual s32 v39();
    virtual s32 v40();
    virtual s32 v41();
    virtual s32 v42();
    virtual s32 v43();
    virtual s32 v44();
    virtual s32 v45();
    virtual s32 v46();
    virtual s32 v47();
    virtual s32 v48();
    virtual s32 v49();
    virtual s32 v50();
    virtual s32 v51();
    virtual s32 v52();
    virtual s32 v53();
    virtual s32 v54();
    virtual s32 v55();
    virtual s32 v56();
    virtual s32 v57();
    virtual s32 v58();
    virtual s32 v59();
    virtual s32 v60();
    virtual s32 v61();
    virtual s32 v62();
    virtual s32 v63();
    virtual s32 v64();
    virtual s32 v65();
    virtual s32 v66();
    virtual s32 v67();
    virtual s32 v68();
    virtual s32 v69();
    virtual s32 v70();
    virtual s32 v71();
    virtual s32 v72();
    virtual s32 v73();
    virtual s32 v74();
    virtual s32 v75();
    virtual s32 v76();
    virtual s32 v77();
    virtual s32 v78();
    virtual s32 v79();
    virtual s32 v80();
    virtual s32 v81();
    virtual s32 v82();
    virtual s32 v83();
    virtual s32 v84();
    virtual s32 v85();
    virtual s32 v86();
    virtual s32 v87();
    virtual s32 v88();
    virtual s32 v89();
    virtual s32 v90();
    virtual s32 v91();
    virtual s32 v92();
    virtual s32 v93();
    virtual s32 v94();
    virtual s32 v95();
    virtual s32 v96();
    virtual s32 v97();
    virtual s32 v98();
    virtual s32 v99();
    virtual s32 v100();
    virtual s32 v101();
    virtual s32 v102();
    virtual s32 v103();
    virtual s32 v104();
    virtual s32 v105();
    virtual s32 v106();
    virtual s32 v107();
    virtual s32 v108();
    virtual s32 v109();
    virtual s32 v110();
    virtual s32 v111();
    virtual s32 v112();
    virtual s32 v113();
    virtual s32 v114();
    virtual s32 v115();
    virtual s32 v116();
    virtual s32 v117();
    virtual s32 v118();
    virtual s32 v119();
    virtual s32 v120();
    virtual s32 v121();
    virtual s32 v122();
    virtual s32 v123();
    virtual s32 v124();
    virtual s32 v125();
    virtual s32 v126();
    virtual s32 v127();
    virtual s32 v128();
    virtual s32 v129();
    virtual s32 v130();
    virtual s32 v131();
    virtual s32 v132();
    virtual s32 v133();
    virtual s32 v134();
    virtual s32 v135();
    virtual s32 v136();
    virtual s32 v137();
    virtual s32 v138();
    virtual s32 v139();
    virtual s32 v140();
    virtual s32 v141();
    virtual s32 v142();
    virtual s32 v143();
    virtual s32 v144();
    virtual s32 v145();
    virtual s32 v146();
    virtual s32 v147();
    virtual s32 v148();
    virtual s32 v149();
    virtual s32 v150();
    virtual s32 v151();
    virtual s32 v152();
    virtual s32 v153();
    virtual s32 v154();
    virtual s32 v155();
    virtual s32 v156();
    virtual s32 v157();
    virtual s32 v158();
    virtual s32 v159();
    virtual s32 v160();
    virtual s32 v161();
    virtual s32 v162();
    virtual s32 v163();
    virtual s32 v164();
    virtual s32 v165();
    virtual s32 v166();
    virtual s32 v167();
    virtual s32 v168();
};

typedef struct Sub44 {
    u8 pad0[0x44];
    s16 x44;
} Sub44;

extern "C" char D_0045C830[];
extern "C" char D_0045C840[];
extern "C" char D_0045C848[];
extern "C" char D_0045C858[];
extern "C" char D_0045C868[];
extern "C" char D_0045C870[];
extern "C" f32 D_0045B080[];
extern "C" s64 D_0047D1A8;
extern "C" f32 D_0047DB20;

extern "C" s32 IsInBattle_288420(void);
extern "C" void CharaSetActionModeAppear_21c920(Actor *);
extern "C" void *GetGameData_1fede0(void);
extern "C" void *ActorFindById_3eb870(void *, s32);
extern "C" void CharaEnterDeathStateMaybe_217a00(Actor *);
extern "C" void CharaSetActionModeDeath_217d70(Actor *);
extern "C" char *strcpy(char *, const char *);
extern "C" s32 Sprintf_1343b8(char *, const char *, ...);
extern "C" s32 MotionListFindByName_1721d0(s32 *, char *, s32 *, s32 *);
extern "C" void CharaSetActionModeDamage_2190c0(Actor *);
extern "C" void CharaSetActionModeBlownAway_218840(Actor *);
extern "C" void *CharaGetHangLedge_238260(Actor *);
extern "C" s32 CharaHangLedgeIsValid_23a280(void *);
extern "C" s32 CharaIsHeadUnderwaterMaybe_238250(Actor *);
extern "C" f32 CharaGetHeadHeightMaybe_238360(Actor *);
extern "C" f32 CharaGetWaterDepthMaybe_238370(Actor *);
extern "C" f32 CharaGetHeightAboveGround_238380(Actor *);
extern "C" s64 fptodp(f32);
extern "C" s64 dpmul(s64, s64);
extern "C" s64 dpsub(s64, s64);
extern "C" s32 DoubleGreaterEqual_100230(s64, s64);
extern "C" void CharaSetActionModeSwim_21b170(Actor *);
extern "C" s32 CharaSwimShouldContinueMaybe_20f8f0(Actor *);
extern "C" void CharaResetToBaseMode_21e830(Actor *);
extern "C" Sub44 *CharaGetGroundTri_238410(Actor *, s32);
extern "C" void CharaSetActionModeMoveMotion_21bbb0(Actor *);

static inline bool NoBit58(Actor *p)
{
    return !(p->x3D0 & ((u64)0x04000000 << 32));
}

static inline bool NoBit59(Actor *p)
{
    return !(p->x3D0 & ((u64)0x08000000 << 32));
}

static inline s32 Lookup(Actor *p, char *buf)
{
    Pos *q = p->x3F4;
    s32 v[3];
    s32 a, b;
    switch ((u32)q) {
    case 0:
        return 0;
    default:
        v[0] = q->v[0];
        v[1] = q->v[1];
        v[2] = q->v[2];
        return MotionListFindByName_1721d0(v, buf, &a, &b);
    }
}

static inline bool IsSpecial(Actor *p, char *buf)
{
    if (buf[0] == '#') return 1;
    return Lookup(p, buf) != 0;
}

static inline bool Check6(Actor *p)
{
    void *q;
    if (!NoBit58(p)) return 0;
    q = CharaGetHangLedge_238260(p);
    if (q == 0 || CharaHangLedgeIsValid_23a280(q) == 0) return 0;
    return 1;
}

static inline bool CheckY(Actor *p)
{
    u32 f;
    f32 k, a;
    if (CharaIsHeadUnderwaterMaybe_238250(p)) return 1;
    f = p->x3D8;
    if (!(f & 0x10)) return 0;
    if (!(f & 4)) return 1;
    k = D_0047DB20 * (f32)D_0045B080[0];
    a = CharaGetWaterDepthMaybe_238370(p);
    a = a + k;
    if (a < CharaGetHeadHeightMaybe_238360(p)) return 0;
    if (!(CharaGetHeightAboveGround_238380(p) <= k)) return 1;
    return 0;
}

static inline bool ShouldAct(Actor *p)
{
    if (!NoBit59(p)) return 0;
    switch (p->xA32) {
    case 4:
        switch (p->xA34) {
        case 0:
            return 0;
        case 1:
        case 2: {
        s64 d;
        if (CharaIsHeadUnderwaterMaybe_238250(p)) return 1;
        if (p->x3D8 & 0x10) {
            s64 a = fptodp(CharaGetHeadHeightMaybe_238360(p));
            s64 k = D_0047D1A8;
            d = dpsub(a, dpmul(k, fptodp(D_0045B080[0])));
            if (DoubleGreaterEqual_100230(fptodp(CharaGetWaterDepthMaybe_238370(p)), d)) return 1;
        }
        return 0;
        }
        }
        return 0;
    case 5:
        return 0;
    }
    return CheckY(p);
}

extern "C" s16 CharaSelectStateFromFlagsMaybe_20e9f0(Actor *p, s64 flags)
{
    switch (p->xA32) {
    case 17:
        p->xA38 = 0;
        return p->xA32;
    case 10:
    case 18:
        return p->xA32;
    default:
        if (!(p->xA44 & 0x40000000)) {
            if ((p->x424 >= 0 && p->x424 < 12) || IsInBattle_288420()) {
                CharaSetActionModeAppear_21c920(p);
                return p->xA32;
            }
        }
        if (!(p->xA44 & 0x200000) && (flags & ((s64)0x800 << 32))) {
            VObj *o = (VObj *)ActorFindById_3eb870(GetGameData_1fede0(), p->x424);
            if (o != 0 && o->v168()) {
                CharaEnterDeathStateMaybe_217a00(p);
                return p->xA32;
            }
            CharaSetActionModeDeath_217d70(p);
            return p->xA32;
        }
        if (p->xA36 != 0x15 && p->xA36 != 0x16 && p->xA36 != 0x17 && p->xA32 != 0x10) {
            if (flags & ((s64)8 << 32)) {
                char buf[0x28];
                if (p->xA2E == 2) {
                    if (p->xA2C <= 0) {
                        strcpy(buf, D_0045C830);
                    } else {
                        Sprintf_1343b8(buf, D_0045C840, p->xA2C + 0x60, D_0045C848);
                    }
                } else if (p->xA2E == 3) {
                    if (p->xA2C <= 0) {
                        strcpy(buf, D_0045C858);
                    } else {
                        Sprintf_1343b8(buf, D_0045C868, p->xA2C + 0x60, D_0045C848);
                    }
                } else {
                    if (p->xA2C <= 0) {
                        strcpy(buf, D_0045C848);
                    } else {
                        Sprintf_1343b8(buf, D_0045C870, p->xA2C + 0x60, D_0045C848);
                    }
                    strcpy(buf, D_0045C848);
                }
                if (!IsSpecial(p, buf)) {
                    CharaSetActionModeDamage_2190c0(p);
                    return p->xA32;
                }
                CharaSetActionModeBlownAway_218840(p);
                return p->xA32;
            }
            if (flags & ((s64)4 << 32)) {
                CharaSetActionModeDamage_2190c0(p);
                return p->xA32;
            }
        }
        if (p->xA38 == 0) {
            s16 st = p->xA32;
            switch (st) {
            case 7:
                return p->xA32;
            case 6:
                if (Check6(p)) return p->xA32;
                break;
            case 0xF:
            case 0x10:
                return p->xA32;
            }
        }
        if (ShouldAct(p)) {
            CharaSetActionModeSwim_21b170(p);
            return p->xA32;
        }
        if (p->xA38 == 0) {
            switch (p->xA32) {
            case 5:
                if (!CharaSwimShouldContinueMaybe_20f8f0(p)) {
                    CharaResetToBaseMode_21e830(p);
                    return p->xA32;
                }
                break;
            case 0:
            case 1:
            case 2:
            case 3:
                if ((p->x3D8 & 4) && CharaGetGroundTri_238410(p, 0)->x44 == 8) {
                    CharaSetActionModeMoveMotion_21bbb0(p);
                    p->xA34 = 0x65;
                    return p->xA32;
                }
                break;
            case 6:
            case 7:
                CharaResetToBaseMode_21e830(p);
                break;
            case 4:
            case 10:
            case 15:
            case 16:
            case 17:
                break;
            default:
                p->xA2E = 0;
                CharaResetToBaseMode_21e830(p);
                break;
            }
        }
        return p->xA32;
    }
    return p->xA32;
}
