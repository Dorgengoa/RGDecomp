#include "types.h"

class A21C1F0 {
    u8 pad[0x1B0];
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
    virtual void f15(f32);
};

class B21C1F0 {
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
    virtual void f198();
};

extern "C" {
extern void strcpy(char *, const char *);
extern f32 RandFloat_13c010(void);
extern void MotionListResetAll_171e00(void *);
extern void ModelObjPlayMotionByName_1867a0(A21C1F0 *, char *, s32);
extern void ModelObjSetMotionPhase_1add80(A21C1F0 *, f32);
extern void ModelMotionEventReleaseHandlers_1b02b0(A21C1F0 *);
extern s32 SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern void ParamTableFadeToOne_1cf9e0(s32, s32, s32);
extern void ParamTableSetAlpha_1cfb10(s32, s32, f32);
extern s32 ParamTableIsFadeIdle_1cfb70(s32, s32);
extern s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 ModelHasMotion_20a5b0(A21C1F0 *, char *);
extern void CharaClearFlags_2124a0(u8 *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(u8 *);
extern void CharaPlayMotion_212590(u8 *, A21C1F0 *, char *, s32, f32);
extern void CharaSetInvincibleTime_2138a0(u8 *, f32);
extern s32 CharaGetId_214a80(u8 *);
extern s32 CharaAppearSelectState_21c8a0(u8 *);
extern void CharaActLoco_21cc10(u8 *, void **);
extern void CharaResetToBaseMode_21e830(u8 *);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern u8 *CharaGetGroundTri_238410(u8 *, s32);
extern s32 CharaGetCurMotionName_238560(u8 *);
extern f32 CharaGetMotionFrame_238570(u8 *);
extern f32 CharaGetCollRadius_2386a0(u8 *);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32, void *, s32);
extern void EffectSetRotXyz_2e0910(s32, void *, f32, f32, f32);
extern void EffectSetPos_2e0bb0(s32, void *, void *);
extern void EffectSetScaleXyz_2e0c90(s32, void *, f32, f32, f32);
extern void EffectCreateByName_2e1020(void *, s32, char *, s32);
extern B21C1F0 *ActorCastToUnit_3b8770(void *);
extern f32 D_0045B080[];
extern char D_0045CF08[];
extern char D_0045CF10[];
extern char D_0045CF18[];
extern char D_0045CF20[];
extern char D_0045CF28[];
extern f32 D_0047DB00;
}

static inline void Notify(void **p) {
    B21C1F0 *v;
    if (*p != 0) {
        v = ActorCastToUnit_3b8770(*p);
        if (v != 0) {
            v->f198();
        }
    }
}

extern "C" void CharaActAppear_21c1f0(u8 *o, void **p) {
    char buf[0x20];
    u8 v60[0x20];
    s32 k;
    u64 keep;
    s32 r;
    s32 g;
    s32 s;
    f32 t;
    B21C1F0 *v;

    *(s32 *)(o + 0x42C) = 0;
    k = CharaGetCurMotionName_238560(o);
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o));
    k = CharaGetCurMotionName_238560(o);
    *(u64 *)(o + 0x570) = *(u64 *)(o + 0x568) & ActCfgTableEvalNormalPrmtFlags_221600(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o));
    r = CharaAppearSelectState_21c8a0(o);
    if (*(u64 *)(o + 0x3D0) & 0x0008000000000000ULL) {
        *(u64 *)(o + 0x3D0) |= 0x0000400000000000ULL;
        *(s32 *)(o + 0x84) = 0;
    }
    g = GetCurrentScene_1f5be0();
    *(u64 *)(o + 0x3D0) &= ~0x0010000000000000ULL;
    switch (r) {
    case 0x14:
        CharaSetInvincibleTime_2138a0(o, 1.0f);
        ObjRecSetFlags_1c3e00(g, 1, CharaGetId_214a80(o), 0xA0030);
        MotionListResetAll_171e00(*(u8 **)(o + 0x3F4) + 0x1F0);
        ModelObjPlayMotionByName_1867a0(*(A21C1F0 **)(o + 0x3F4), D_0045CF08, 6);
        (*(A21C1F0 **)(o + 0x3F4))->f15(1.0f);
        ModelObjSetMotionPhase_1add80(*(A21C1F0 **)(o + 0x3F4), 1.0f);
        ModelMotionEventReleaseHandlers_1b02b0(*(A21C1F0 **)(o + 0x3F4));
        *(s16 *)(o + 0xA34) = 0x15;
        *(s32 *)(o + 0xAD0) = 0;
        *(s32 *)(o + 0xAD4) = 0;
        CharaClearFlags_2124a0(o);
    case 0x15:
        if (!(*(f32 *)(o + 0xAD0) < (f32)*(s16 *)(o + 0xB4A))) {
            ObjRecClearFlags_1c3dc0(g, 1, CharaGetId_214a80(o), 0xA0030);
            s = GameSceneSoundSlot5GetHandle_1d0790(g);
            SoundPlayScaledVolume_1b9520(s, 0x47, SoundNextPlayHandle_1b81c0(), 1.0f);
            s = GetEffectMgr_2d9040();
            {
                u8 *p_ = (u8 *)buf;
                u32 n_ = 0x20;
                if (p_) {
                    while (n_) {
                        *p_ = 0;
                        n_--;
                        p_++;
                    }
                }
            }
            switch (*(s16 *)(CharaGetGroundTri_238410(o, 0) + 0x42)) {
            case 0xE:
            case 0x11:
                strcpy(buf, D_0045CF10);
                break;
            case 2:
            case 0x10:
            case 1:
                strcpy(buf, D_0045CF18);
                break;
            }
            EffectCreateByName_2e1020(v60, s, buf, -1);
            EffectSetId_2e0100(s, v60, CharaGetId_214a80(o));
            EffectSetPos_2e0bb0(s, v60, o + 0x70);
            EffectSetRotXyz_2e0910(s, v60, 0.0f, D_0047DB00 * (RandFloat_13c010() - 0.5f), 0.0f);
            t = CharaGetCollRadius_2386a0(o) / (2.0f * D_0045B080[0]);
            if (t < 0.25f) {
                t = 0.25f;
            }
            EffectSetScaleXyz_2e0c90(s, v60, t, t, t);
            if (ModelHasMotion_20a5b0(*(A21C1F0 **)(o + 0x3F4), D_0045CF20) == 0) {
                v = ActorCastToUnit_3b8770(*p);
                if (v != 0) {
                    v->f198();
                }
                CharaResetToBaseMode_21e830(o);
                CharaActLoco_21cc10(o, p);
                return;
            }
            CharaPlayMotion_212590(o, *(A21C1F0 **)(o + 0x3F4), D_0045CF20, 6, 1.0f);
            *(s16 *)(o + 0xA34) = 0x16;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            *(u64 *)(o + 0x3D0) |= 0x0010000000000000ULL;
        }
        CharaSetInvincibleTime_2138a0(o, 15.0f);
        break;
    case 0x16:
        if (CharaPlayedMotionIsCurrent_2124c0(o) == 0 || (CharaPlayedMotionIsCurrent_2124c0(o) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f))) {
            Notify(p);
            CharaResetToBaseMode_21e830(o);
            CharaActLoco_21cc10(o, p);
            return;
        }
        break;
    case 0xA:
        if (*(s16 *)(o + 0xA34) != r) {
            ObjRecSetFlags_1c3e00(g, 1, CharaGetId_214a80(o), 0xA0000);
            ParamTableSetAlpha_1cfb10(g, CharaGetId_214a80(o), 0.0f);
            ParamTableFadeToOne_1cf9e0(g, CharaGetId_214a80(o), *(s16 *)(o + 0xB4A));
            CharaPlayMotion_212590(o, *(A21C1F0 **)(o + 0x3F4), D_0045CF28, 6, 1.0f);
            *(s16 *)(o + 0xA34) = 0xA;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
        }
        if (ParamTableIsFadeIdle_1cfb70(g, CharaGetId_214a80(o)) != 0) {
            Notify(p);
            ObjRecClearFlags_1c3dc0(g, 1, CharaGetId_214a80(o), 0xA0000);
            CharaResetToBaseMode_21e830(o);
            CharaActLoco_21cc10(o, p);
            return;
        }
        break;
    default:
        Notify(p);
        CharaResetToBaseMode_21e830(o);
        CharaActLoco_21cc10(o, p);
        return;
    }
    *(u64 *)(o + 0x3D0) |= 0x0400000000000000ULL;
    Notify(p);
    *(u64 *)(o + 0x568) &= keep;
}
