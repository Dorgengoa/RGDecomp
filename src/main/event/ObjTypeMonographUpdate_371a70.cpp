#include "types.h"

class C371A70 {
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
    virtual s32 f101(s32);
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
    virtual s32 f114(s32);
};

extern "C" {
extern f32 GetScaledGravity_23b170(void);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern s32 ObjRecGetFlags_1c3d90(s32, s32, s32);
extern void MatIdentity_1cbe40(void *);
extern s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern u8 *GetActionMgr_1fdb50(void);
extern u8 *GetGameData_1fede0(void);
extern s32 CharaHasEvObjContact_214960(u8 *);
extern u8 *CharaGetEvObjContact_214990(u8 *);
extern u8 *ActionMgrFindById_233b50(u8 *, s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetPos_2e0bb0(s32, void *, void *);
extern void EffectCreateByName_2e1020(void *, s32, void *, s32);
extern f32 EventParamRecGetLimit_2e3af0(s32);
extern f32 EventParamRecGetDamping_2e3b00(s32);
extern f32 EventParamRecGetSpring_2e3b10(s32);
extern f32 EventVolumeRecGetMass_2e4d20(s32);
extern void TargetRefResolve_2e5ed0(void *, s32);
extern void TargetRefApplyToEventObj_2e6810(void *, void *);
extern void TargetRefGetPos_2e6a60(void *, f32 *);
extern s32 TargetRefGetId_2e7120(void *);
extern s32 TargetRefGetKind_2e7130(void *);
extern void EventObjSetFromMatrix_2e72f0(void *, void *);
extern void EventObjGetPos_2e7640(void *, f32 *);
extern void EvObjUpdateBase_2f9910(u8 *, u8 *);
extern s32 ObjTypeMonographIsActiveWithRecs_372be0(u8 *);
extern C371A70 *ActorFindById_3eb870(u8 *, s32);
extern f32 D_0045B080[];
extern u8 D_00463810[];
}

static inline bool Not31(u8 *o) {
    return !((*(u32 *)(o + 0xD0) & 0x80000000) != 0);
}

static inline bool Not29(u8 *o) {
    return !((*(u32 *)(o + 0xD0) & 0x20000000) != 0);
}

extern "C" void ObjTypeMonographUpdate_371a70(u8 *o, u8 *p) {
    f32 vB0[4];
    f32 m80[12];
    u8 v60[0x20];
    f32 v50[4];
    f32 t;
    f32 f20;
    s32 s;
    f32 f21;
    f32 g;
    f32 f4;
    f32 lim;
    f32 a;
    C371A70 *c;
    u8 *q;
    s32 n;

    EvObjUpdateBase_2f9910(o, p);
    t = *(f32 *)(o + 0xF8) - *(f32 *)p;
    *(f32 *)(o + 0xF8) = t;
    if (t < 0.0f) {
        *(f32 *)(o + 0xF8) = -1.0f;
    }
    *(u32 *)(o + 0xD0) &= ~0x200000;
    if (!Not31(o)) {
        *(u32 *)(o + 0xD0) |= 0x1000000;
        return;
    }
    TargetRefApplyToEventObj_2e6810(o + 0xA0, o + 0x10);
    f20 = *(f32 *)(o + 0x100);
    t = f20 - *(f32 *)p;
    *(f32 *)(o + 0x100) = t;
    if (t < 0.0f) {
        *(f32 *)(o + 0x100) = -1.0f;
    }
    if (!(*(f32 *)(o + 0x100) < 0.0f)) {
        return;
    }
    TargetRefResolve_2e5ed0(o + 0xA0, 0);
    if (ObjTypeMonographIsActiveWithRecs_372be0(o) == 0) {
        *(u32 *)(o + 0xD0) |= 0x1000000;
        return;
    }
    if (!(*(f32 *)(o + 0x104) < 0.0f)) {
        t = *(f32 *)(o + 0x104) + *(f32 *)p;
        *(f32 *)(o + 0x104) = t;
        if (!(t <= 40.0f)) {
            *(f32 *)(o + 0x104) = -1.0f;
        }
    }
    *(u32 *)(o + 0xD0) &= ~0x40000000;
    MatIdentity_1cbe40(m80);
    TargetRefGetPos_2e6a60(o + 0xA0, vB0);
    vB0[1] = vB0[1] + *(f32 *)(o + 0xF0);
    if (GetGameMode_1f59c0() != 11 && GetGameMode_1f59c0() != 9 && !(f20 < 0.0f)) {
        s = GetEffectMgr_2d9040();
        EffectCreateByName_2e1020(v60, s, D_00463810, -1);
        EffectSetPos_2e0bb0(s, v60, vB0);
        SoundPlayScaledVolume_1b9520(GameSceneSoundSlot5GetHandle_1d0790(GetCurrentScene_1f5be0()), 0x50, 0, 1.0f);
    }
    if (!Not29(o)) {
        EventObjSetFromMatrix_2e72f0(o + 0x10, m80);
        *(f32 *)(o + 0xE8) = 0.0f;
        *(f32 *)(o + 0xEC) = 0.0f;
        return;
    }
    *(f32 *)(o + 0xE8) = *(f32 *)(o + 0xE8) * (1.0f - EventParamRecGetDamping_2e3b00(*(s32 *)(o + 0xE4)));
    EventObjGetPos_2e7640(o + 0x58, v50);
    f20 = (vB0[1] - v50[1]) * EventParamRecGetSpring_2e3b10(*(s32 *)(o + 0xE4)) + *(f32 *)(o + 0xEC) * GetScaledGravity_23b170();
    f4 = f20 / EventVolumeRecGetMass_2e4d20(*(s32 *)(o + 0xE0));
    t = *(f32 *)(o + 0xE8) + f4;
    lim = 0.25f * D_0045B080[0];
    *(f32 *)(o + 0xE8) = t;
    a = t;
    if (t < 0.0f) {
        a = -t;
    }
    if (!(a <= lim)) {
        if (*(f32 *)(o + 0xE8) < 0.0f) {
            *(f32 *)(o + 0xE8) = -lim;
        } else {
            *(f32 *)(o + 0xE8) = lim;
        }
    }
    v50[1] = v50[1] + *(f32 *)(o + 0xE8);
    f21 = vB0[1] - v50[1];
    if (f21 < 0.0f) {
        f20 = -f21;
    } else {
        f20 = f21;
    }
    if (!(f20 <= EventParamRecGetLimit_2e3af0(*(s32 *)(o + 0xE4)))) {
        if (f21 < 0.0f) {
            vB0[1] = vB0[1] + EventParamRecGetLimit_2e3af0(*(s32 *)(o + 0xE4));
        } else {
            vB0[1] = vB0[1] - EventParamRecGetLimit_2e3af0(*(s32 *)(o + 0xE4));
        }
    } else {
        vB0[1] = v50[1];
    }
    *(f32 *)(o + 0xEC) = 0.0f;
    EventObjSetFromMatrix_2e72f0(o + 0x10, m80);
    if (TargetRefGetKind_2e7130(o + 0xA0) == 5) {
        s = GetCurrentScene_1f5be0();
        if (ObjRecGetFlags_1c3d90(s, 1, TargetRefGetId_2e7120(o + 0xA0)) & 0x10000000) {
            *(u32 *)(o + 0xD0) |= 0x1000000;
        }
        c = ActorFindById_3eb870(GetGameData_1fede0(), TargetRefGetId_2e7120(o + 0xA0));
        if (c == 0 || c->f101(0x1F) == 0 || c->f114(0x1F) <= 0) {
            *(u32 *)(o + 0xD0) |= 0x1000000;
        }
        q = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), TargetRefGetId_2e7120(o + 0xA0));
        if (q != 0 && CharaHasEvObjContact_214960(q) != 0 && *(s16 *)(CharaGetEvObjContact_214990(q) + 4) == 3) {
            *(u32 *)(o + 0xD0) |= 0x1000000;
        }
    }
    if ((*(u32 *)(o + 0xD0) & 0x800000) && *(u8 *)(p + 4) == 0) {
        t = *(f32 *)(o + 0xFC) - *(f32 *)p;
        *(f32 *)(o + 0xFC) = t;
        n = (s32)t;
        if (t < 90.0f) {
            *(u32 *)(o + 0xD0) = ((n >> 1) & 1) ? (*(u32 *)(o + 0xD0) | 0x200000) : (*(u32 *)(o + 0xD0) & ~0x200000);
        } else if (t < 300.0f) {
            *(u32 *)(o + 0xD0) = ((n >> 2) & 1) ? (*(u32 *)(o + 0xD0) | 0x200000) : (*(u32 *)(o + 0xD0) & ~0x200000);
        }
        if (*(f32 *)(o + 0xFC) < 0.0f) {
            *(u32 *)(o + 0xD0) |= 0x1000000;
        }
    }
}
