#include "types.h"

class V218880 {
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
    virtual s32 f129();
};


extern "C" {
extern s32 Rand_133710(void);
extern s32 Sprintf_1343b8(char *, const char *, ...);
extern char *strcpy(char *, const char *);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern f32 AngleWrap_1cbf30(f32);
extern void ParamTableSetAlpha_1cfb10(s32, s32, f32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 ModelHasMotion_20a5b0(s32, char *);
extern s32 CharaWeaponStateValidateMaybe_20a600(s32);
extern void CharaRequestAction_212410(u8 *, char *, f32);
extern void CharaClearFlags_2124a0(u8 *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(u8 *);
extern void CharaPlayMotion_212590(u8 *, s32, char *, s32, f32);
extern s32 CharaGetBaseActionMode_213830(u8 *);
extern void CharaSetMoveDirMaybe_213b00(u8 *, void *);
extern s32 CharaGetId_214a80(u8 *);
extern s32 CharaActDamageNextStateMaybe_218fc0(u8 *);
extern void CharaActLoco_21cc10(u8 *, void **);
extern void CharaResetToBaseMode_21e830(u8 *);
extern s32 CharaInputInterruptMaybe_21e8f0(u8 *, void **);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern s32 ActCfgTableFindMoveById_223080(s32, s32);
extern s32 CharaGetCurMotionName_238560(u8 *);
extern f32 CharaGetMotionFrame_238570(u8 *);
extern void CharaSetVelocity_238770(u8 *, f32, f32, f32);
extern void CharaGetForwardVec_238830(u8 *, void *);
extern char D_0045CBD8[];
extern char D_0045CBF0[];
extern char D_0045CBF8[];
extern char D_0045CCF0[];
extern char D_0045CD00[];
extern char D_0045CD10[];
extern char D_0045CD18[];
extern char D_0045CD20[];
extern char D_0045CD28[];
extern char D_0045CD38[];
extern char D_0045CD48[];
extern f32 D_0047D1FC;
}


typedef struct {
    u64 pad0 : 46;
    u64 b46 : 1;
    u64 pad47 : 17;
} BF218880;

static inline void MakeName(u8 *o, char *buf, char *s2, char *s3, char *suf) {
    if (*(s16 *)(o + 0xA2E) == 2) {
        if (*(s16 *)(o + 0xA2C) <= 0) {
            strcpy(buf, s2);
        } else {
            Sprintf_1343b8(buf, D_0045CBD8, *(s16 *)(o + 0xA2C) + 0x60, suf);
        }
    } else if (*(s16 *)(o + 0xA2E) == 3) {
        if (*(s16 *)(o + 0xA2C) <= 0) {
            strcpy(buf, s3);
        } else {
            Sprintf_1343b8(buf, D_0045CBF0, *(s16 *)(o + 0xA2C) + 0x60, suf);
        }
    } else {
        if (*(s16 *)(o + 0xA2C) <= 0) {
            strcpy(buf, suf);
        } else {
            Sprintf_1343b8(buf, D_0045CBF8, *(s16 *)(o + 0xA2C) + 0x60, suf);
        }
        strcpy(buf, suf);
    }
}

extern "C" void CharaActDamage_218880(u8 *o, void **p) {
    char bB0[0x20];
    char b90[0x20];
    u8 v80[0x10];
    char b60[0x20];
    s32 k;
    u64 keep;
    u64 mask;
    s32 r;
    s32 t;

    *(s32 *)(o + 0x42C) = 0;
    if (((V218880 *)*p)->f129() == 5) {
        CharaResetToBaseMode_21e830(o);
        CharaActLoco_21cc10(o, p);
        return;
    }
    k = CharaGetCurMotionName_238560(o);
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o));
    k = CharaGetCurMotionName_238560(o);
    mask = ActCfgTableEvalNormalPrmtFlags_221600(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o)) | 0x0017C7FC00000000ULL;
    if (!(*(s32 *)(o + 0xA44) & 0x1000000)) {
        if (*(f32 *)(o + 0xACC) > 5.0f && (*(u64 *)(o + 0x568) & 0x100000000ULL)) {
            switch (CharaGetBaseActionMode_213830(o)) {
            case 2:
                CharaRequestAction_212410(o, D_0045CCF0, 0.25f);
                break;
            case 3:
                CharaRequestAction_212410(o, D_0045CD00, 0.25f);
                break;
            }
        }
    }
    *(u64 *)(o + 0x570) = *(u64 *)(o + 0x568) & mask;
    r = CharaActDamageNextStateMaybe_218fc0(o);
    if (*(s32 *)(o + 0x3D8) & 1) {
        *(u64 *)(o + 0x3D0) &= ~0x0000400000000000ULL;
    }
    *(s32 *)(o + 0x42C) = ActCfgTableFindMoveById_223080(*(s32 *)(o + 0x428), CharaWeaponStateValidateMaybe_20a600(*(s16 *)(o + 0xA2E)));
    switch (r) {
    case 1:
        if (*(s16 *)(o + 0xA34) != r) {
            MakeName(o, bB0, D_0045CD10, D_0045CD20, D_0045CD18);
            MakeName(o, b90, D_0045CD28, D_0045CD48, D_0045CD38);
            if (ModelHasMotion_20a5b0(*(s32 *)(o + 0x3F4), b90) != 0) {
                CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), bB0, 4, 1.0f);
            } else {
                CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), bB0, 6, 1.0f);
            }
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            ParamTableSetAlpha_1cfb10(GetCurrentScene_1f5be0(), CharaGetId_214a80(o), 1.0f);
            if (!(*(u64 *)(o + 0x3D0) & 0x200000000ULL)) {
                CharaSetVelocity_238770(o, 0.0f, 0.0f, 0.0f);
            }
            if (!(*(u64 *)(o + 0x3D0) & 0x100000000ULL)) {
                *(f32 *)(o + 0x64) = AngleWrap_1cbf30(*(f32 *)(o + 0x890) - D_0047D1FC);
                *(s32 *)(o + 0x94) = 0;
                CharaGetForwardVec_238830(o, v80);
                CharaSetMoveDirMaybe_213b00(o, v80);
            }
            if (CharaGetId_214a80(o) >= 0 && CharaGetId_214a80(o) < 12) {
                t = *(s32 *)(*(u8 **)(o + 0x3F4) + 0x4FC);
                SoundPlayScaledVolume_1b9520(t, Rand_133710() % 3 + 9, 0, 1.0f);
            }
        }
        break;
    case 2:
        if (*(s16 *)(o + 0xA34) != r) {
            MakeName(o, b60, D_0045CD28, D_0045CD48, D_0045CD38);
            if (ModelHasMotion_20a5b0(*(s32 *)(o + 0x3F4), b60) == 0) {
                CharaResetToBaseMode_21e830(o);
                CharaActLoco_21cc10(o, p);
                return;
            }
            CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), b60, 6, 1.0f);
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
        } else {
            if (CharaInputInterruptMaybe_21e8f0(o, p) != 0) {
                return;
            }
            if (CharaPlayedMotionIsCurrent_2124c0(o) == 0 || (CharaPlayedMotionIsCurrent_2124c0(o) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f))) {
                CharaResetToBaseMode_21e830(o);
                CharaActLoco_21cc10(o, p);
                return;
            }
        }
        break;
    default:
        CharaResetToBaseMode_21e830(o);
        CharaActLoco_21cc10(o, p);
        return;
    }
    *(u64 *)(o + 0x3D0) |= 4;
    *(u64 *)(o + 0x3D0) |= 0x0400000000000000ULL;
    *(u64 *)(o + 0x568) &= keep;
}
