#include "types.h"

typedef struct {
    s32 a;
    s32 b;
} Seg2116B0;

typedef struct {
    s16 a;
    s16 b;
} HP2116B0;

typedef struct {
    f32 x, y, z, w;
} V4_2116B0;

typedef struct {
    Seg2116B0 s[6];
    V4_2116B0 v;
    HP2116B0 h[5];
    s32 w;
} __attribute__((aligned(16))) Blk2116B0;

typedef struct {
    u8 pad[0x110];
    Blk2116B0 b[2];
} T2116B0;

typedef struct {
    s16 a;
    s32 b;
    s32 c;
    union {
        s32 w;
        struct {
            u16 lo;
            u16 hi;
        } h;
    } u;
    s32 e;
} Rec2116B0;

class Q2116B0 {
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
    virtual void v46();
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
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158();
    virtual void v159();
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
    virtual void v195();
    virtual void v196();
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
    virtual void v238();
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
    virtual void v257();
    virtual void v258();
    virtual void v259();
    virtual void v260();
    virtual void v261();
    virtual void v262();
    virtual void v263();
    virtual void v264();
    virtual void v265();
    virtual void v266();
    virtual void v267();
    virtual void v268();
    virtual void v269();
    virtual void v270();
    virtual void v271();
    virtual void v272();
    virtual void v273();
    virtual void v274();
    virtual void v275();
    virtual void v276();
    virtual void v277();
    virtual void v278();
    virtual void v279();
    virtual void v280();
    virtual void v281();
    virtual u8 *f282();
};

extern "C" {
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern void SrtSetRotThunk_1c73d0(u8 *, f32, f32, f32);
extern void SrtSetPosFromVecThunk_1c7410(u8 *, void *);
extern void MatToRotPos_1cade0(void *, void *, void *);
extern void MatMulVec4Args_1cb7f0(void *, void *, f32, f32, f32, f32);
extern void VecNormalize_1cbb80(void *, void *);
extern u8 *GetActionMgr_1fdb50(void);
extern u8 *GetGameData_1fede0(void);
extern void CharaResetBattleStateMaybe_212f20(u8 *, s32);
extern void CharaStartActionByName_216d90(u8 *, void *, f32, s32);
extern u8 *ActionMgrFindById_233b50(u8 *, s32);
extern f32 CharaGetGroundY_238350(u8 *);
extern Blk2116B0 *CharaGetGroundTri_238410(u8 *, s32);
extern void CharaSetVelocityFromVec_238790(u8 *, void *);
extern void CharaSetRot_2387d0(u8 *, f32, f32, f32);
extern void CharaSetPosVec_2387e0(u8 *, void *);
extern void CharaGetSrtMatrix_2388c0(u8 *, void *);
extern s32 GetEventObjMgr_2d1960(void);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32, void *, s32);
extern void EffectSetParamInt_2e0530(s32, void *, s32, s32);
extern void EffectCreateByName_2e1020(void *, s32, void *, s32);
extern void TargetRefDetachFromParent_2e5890(void *);
extern s32 TargetRefGetMatrix_2e6870(void *, void *);
extern s32 TargetRefIsActive_2e6f00(void *);
extern s32 TargetRefGetMapObj_2e7050(void *);
extern u8 *TargetRefGetObjSlot_2e70e0(void *);
extern s32 TargetRefGetId_2e7120(void *);
extern s32 TargetRefGetKind_2e7130(void *);
extern void TargetRefClear_2e71d0(void *);
extern u8 *EvMapObjFindById_2e9810(s32, s32);
extern s32 EvMapObjThrowStart_3661f0(u8 *, s32, void *, s32, void *);
extern s32 EquipSlotGetRecId_3a0760(u8 *);
extern Q2116B0 *CharaMgrPoolFindById_3a8c60(s32, s32);
extern u8 D_0045C920[];
extern u8 D_0045C930[];
extern u8 D_0045C950[];
extern u8 D_0045C960[];
extern u8 D_0045C970[];
extern u8 D_0045C980[];
extern u8 D_0045C9A0[];
extern u8 D_0045C9C0[];
extern u8 D_0045C9E0[];
extern s32 D_0047E600;
extern s32 D_0047E604;
extern s32 D_0047E608;
extern s32 D_0047E60C;
extern s32 D_0047E610;
extern s32 D_004BCB20[];
}

static inline s32 HasF(u8 *o, s32 m) {
    return (*(s32 *)(o + 0x3D8) & m) != 0;
}

extern "C" s32 CharaReleaseHeldTarget_2116b0(u8 *o, s32 flag, f32 x, f32 y, f32 z) {
    f32 v190[16];
    f32 v180[4];
    f32 v170[4];
    f32 v130[16];
    f32 v120[4];
    Rec2116B0 rec;
    f32 vC0[16];
    f32 vB0[4];
    Rec2116B0 t90;
    Rec2116B0 t70;
    f32 v60[4];
    u8 *pl;
    u8 *t;
    u8 *t8;
    f32 ang;
    Q2116B0 *q;
    u8 *r;
    s32 i;
    Blk2116B0 *src;
    s32 g;
    s32 s;
    u8 *str;
    s32 lo;
    s32 hi;

    if (TargetRefIsActive_2e6f00(o + 0x9DC) != 0) {
        TargetRefGetMatrix_2e6870(o + 0x9DC, v190);
        MatToRotPos_1cade0(v170, v180, v190);
        TargetRefDetachFromParent_2e5890(o + 0x9DC);
        switch (TargetRefGetKind_2e7130(o + 0x9DC)) {
        case 2:
            pl = GetActionMgr_1fdb50();
            t = ActionMgrFindById_233b50(pl, TargetRefGetId_2e7120(o + 0x9DC));
            if (t == 0) {
                break;
            }
            CharaResetBattleStateMaybe_212f20(t, 0);
            ang = *(f32 *)(o + 0x64);
            {
                u8 *p_ = (u8 *)v60;
                u32 n_ = 0x10;
                if (p_) {
                    while (n_) {
                        *p_ = 0;
                        n_--;
                        p_++;
                    }
                }
            }
            v60[0] = Sinf_128fd0(ang);
            v60[2] = Cosf_128d30(ang);
            CharaSetRot_2387d0(t, 0.0f, ang, 0.0f);
            SrtSetRotThunk_1c73d0(t, 0.0f, ang, 0.0f);
            { f32 c_ = v60[2]; f32 b_ = v60[1]; f32 a_ = v60[0];
            *(f32 *)(t + 0x450) = a_;
            *(f32 *)(t + 0x454) = b_;
            *(f32 *)(t + 0x458) = c_; }
            *(f32 *)(t + 0x45C) = 0.0f;
            VecNormalize_1cbb80(t + 0x450, t + 0x450);
            { f32 c_ = v60[2]; f32 b_ = v60[1]; f32 a_ = v60[0];
            *(f32 *)(t + 0x440) = a_;
            *(f32 *)(t + 0x444) = b_;
            *(f32 *)(t + 0x448) = c_; }
            *(f32 *)(t + 0x44C) = 0.0f;
            VecNormalize_1cbb80(t + 0x440, t + 0x440);
            CharaSetPosVec_2387e0(t, v180);
            SrtSetPosFromVecThunk_1c7410(t, v180);
            *(s32 *)(t + 0xA44) &= ~0x40;
            *(s32 *)(t + 0xB20) = -1;
            D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E600;
            q = CharaMgrPoolFindById_3a8c60(*(s32 *)(GetGameData_1fede0() + 0x14), *(s16 *)(o + 0x424));
            if (q != 0 && (r = q->f282()) != 0) {
                switch (EquipSlotGetRecId_3a0760(r)) {
                case 0x6F:
                    D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E604;
                    break;
                case 0x70:
                    D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E608;
                    break;
                case 0x32B:
                    D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E60C;
                    break;
                case 0x32C:
                    D_004BCB20[*(s16 *)(t + 0x424)] = D_0047E610;
                    break;
                }
            }
            for (i = 0; i < 2; i++) {
                src = CharaGetGroundTri_238410(o, i);
                ((T2116B0 *)t)->b[i] = *src;
            }
            *(s32 *)(t + 0x3D8) &= ~1;
            *(s32 *)(t + 0x3D8) &= ~2;
            *(s32 *)(t + 0x3D8) = HasF(o, 4) ? (*(s32 *)(t + 0x3D8) | 4) : (*(s32 *)(t + 0x3D8) & ~4);
            *(s32 *)(t + 0x3D8) = HasF(o, 8) ? (*(s32 *)(t + 0x3D8) | 8) : (*(s32 *)(t + 0x3D8) & ~8);
            *(s32 *)(t + 0x3D8) &= ~0x10;
            *(s32 *)(t + 0x3D8) &= ~0x20;
            *(s32 *)(t + 0x3D8) &= ~0x40;
            *(s32 *)(t + 0x3D8) &= ~0x80;
            *(f32 *)(t + 0x3EC) = CharaGetGroundY_238350(o);
            *(f32 *)(t + 0x3E0) = v180[1] - *(f32 *)(t + 0x3EC);
            CharaGetSrtMatrix_2388c0(o, v130);
            MatMulVec4Args_1cb7f0(v120, v130, x, y, z, 0.0f);
            CharaSetVelocityFromVec_238790(t, v120);
            if (flag == 0) {
                CharaStartActionByName_216d90(t, D_0045C920, 1.0f, 0);
                *(s16 *)(t + 0xA36) = 0x16;
            } else {
                CharaStartActionByName_216d90(t, D_0045C930, 1.0f, 0);
                *(s16 *)(t + 0xA36) = 0x17;
                g = GetEffectMgr_2d9040();
                rec.u.w = 0;
                if (*(s16 *)(o + 0x424) != 4) {
                    EffectCreateByName_2e1020(&t90, g, D_0045C950, -1);
                    rec.a = t90.a;
                    rec.b = t90.b;
                    rec.c = t90.c;
                    rec.u.w = t90.u.w;
                    lo = t90.u.h.lo;
                    lo = (rec.u.h.lo & 0xFFFF0000) | lo;
                    hi = t90.u.h.hi;
                    hi = (rec.u.h.hi & 0xFFFF0000) | hi;
                    rec.u.h.lo = lo;
                    rec.u.h.hi = hi;
                    rec.e = t90.e;
                } else {
                    EffectCreateByName_2e1020(&t70, g, D_0045C960, -1);
                    rec.a = t70.a;
                    rec.b = t70.b;
                    rec.c = t70.c;
                    rec.u.w = t70.u.w;
                    lo = t70.u.h.lo;
                    lo = (rec.u.h.lo & 0xFFFF0000) | lo;
                    hi = t70.u.h.hi;
                    hi = (rec.u.h.hi & 0xFFFF0000) | hi;
                    rec.u.h.lo = lo;
                    rec.u.h.hi = hi;
                    rec.e = t70.e;
                }
                EffectSetId_2e0100(g, &rec, *(s16 *)(o + 0x424));
                EffectSetParamInt_2e0530(g, &rec, 0, 0);
                EffectSetParamInt_2e0530(g, &rec, 1, TargetRefGetId_2e7120(o + 0x9DC));
            }
            *(s32 *)(t + 0xA44) |= 0x20;
            break;
        case 8:
            s = GetEventObjMgr_2d1960();
            t8 = EvMapObjFindById_2e9810(s, *(s32 *)(TargetRefGetObjSlot_2e70e0(o + 0x9DC) + 8));
            if (t8 == 0) {
                break;
            }
            CharaGetSrtMatrix_2388c0(o, vC0);
            MatMulVec4Args_1cb7f0(vB0, vC0, x, y, z, 0.0f);
            str = D_0045C970;
            q = CharaMgrPoolFindById_3a8c60(*(s32 *)(GetGameData_1fede0() + 0x14), *(s16 *)(o + 0x424));
            if (q != 0 && (r = q->f282()) != 0) {
                switch (EquipSlotGetRecId_3a0760(r)) {
                case 0x6F:
                    str = D_0045C980;
                    break;
                case 0x70:
                    str = D_0045C9A0;
                    break;
                case 0x32B:
                    str = D_0045C9C0;
                    break;
                case 0x32C:
                    str = D_0045C9E0;
                    break;
                }
            }
            EvMapObjThrowStart_3661f0(t8, TargetRefGetMapObj_2e7050(o + 0x9DC), vB0, *(s16 *)(o + 0x424), str);
            break;
        }
    }
    TargetRefClear_2e71d0(o + 0x9DC);
    return 1;
}
