#include "types.h"

typedef struct V80 {
    u8 b[0x60];
} V80;

class Base {
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
    virtual void vApply(V80 *);
};

class Act : public Base {
public:
    u8 pad4[8];
    s32 xC;
};

typedef struct Rec {
    u8 pad0[4];
    s16 x4;
    u8 pad6[0x10 - 6];
    s16 *x10;
} Rec;

typedef struct Cur {
    u8 pad0[8];
    s16 x8;
    u8 padA[6];
    s16 x10;
    s16 x12;
} Cur;

typedef struct Game {
    u8 pad0[0x18];
    s32 x18;
} Game;

typedef struct Ctx {
    u8 pad0[0x11];
    s8 x11;
} Ctx;

extern "C" {
s32 SoundNextPlayHandle_1b81c0(void);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
s32 GetCurrentScene_1f5be0(void);
Game *GetGameData_1fede0(void);
s32 SceneSoundGetSlot0HandleCur_207df0(void);
s32 MenuGridCursorInput_28e170(s32, u8 *, s32, s32);
s32 UiEntryListFindByTag_28ea40(s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
Cur *UiEntryListGetCurrentData_28ec60(s32);
void StateMachineSetState_28ede0(s32, s32, s32);
f32 *UiGetWidgetColor_2904b0(s32, s32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
void MenuItemUseTargetReserveGaugesRefresh_2a1ab0(Ctx *, s32);
void MenuItemUseTargetMemberStatValues_2a25c0(Ctx *, s32);
void MenuItemUseTargetMemberGaugesRefresh_2a2800(Ctx *, s32);
Rec *MenuGetItemAtCell_2a7000(s8, s32);
void MenuItemUseSeReset_2aea90(void);
void ItemUseMaybe_2eef60(s32, V80 *, void (*)(void), s32, u8 *);
void ExecInfoInitFromInvItem_3a7430(V80 *, s32, s16, s32);
void ExecInfoInit_3a7940(V80 *);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
Act *PartyGetLeaderChara_3c2820(s32);
s32 PartyGetSlotId_3c3120(s32, s32);
s32 ItemGetUseEffectTargetModeMaybe_3d4f00(Rec *);
void MenuItemUseFxCb_2ae7c0(void);
extern u8 D_004B2570[];
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Ctx *D_00482374;
extern s32 D_004824C4;
s32 MenuItemUseTargetState_2ae490(s32 arg0, s32 arg1);
}


s32 MenuItemUseTargetState_2ae490(s32 arg0, s32 arg1) {
    u8 flag;
    V80 v80;
    Rec *rec;
    s32 st;
    s32 i;
    s32 h;
    u32 id;
    Game *g;
    s32 n1;
    Act *act;
    s32 idx;
    s16 s6v;
    s32 n0;
    Cur *cur;
    s32 s5v;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 9, 0);
    }
    idx = UiEntryListFindByTag_28ea40(D_00482364, 3);
    g = GetGameData_1fede0();
    rec = MenuGetItemAtCell_2a7000(D_00482374->x11, idx + 4);
    if (rec == 0) {
        StateMachineSetState_28ede0(D_0048235C, 0x2B, 0);
        return 1;
    }
    st = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 7, 0);
    cur = UiEntryListGetCurrentData_28ec60(D_00482364);
    n0 = PartyCountMembers_3c2010(g->x18, 1, 1);
    n1 = PartyCountReserve_3c1c20(g->x18, 1, 1);
    if (cur->x12 == 0) {
        cur->x8 = n0 - 1;
    } else if (cur->x12 == 1) {
        cur->x8 = n1 - 1;
    }

    if (st == 1) {
        act = PartyGetLeaderChara_3c2820(g->x18);
        s6v = rec->x4;
        s5v = *rec->x10;
        h = -1;
        if (ItemGetUseEffectTargetModeMaybe_3d4f00(rec) == 0) {
            h = PartyGetSlotId_3c3120(g->x18, cur->x10 + cur->x12 * n0);
        }
        ExecInfoInit_3a7940(&v80);
        ExecInfoInitFromInvItem_3a7430(&v80, act->xC, s6v, 0);
        act->vApply(&v80);
        for (i = 0; i < 10; i++) {
            id = (u16)(i + 0x8F);
            if (!(*UiGetWidgetColor_2904b0(D_00482360, id) < 1.0f)) {
                UiSetWidgetColor_2905b0(D_00482360, id, 1.0f, 1.0f, 1.0f, 1.0f);
            }
        }
        flag = 0;
        MenuItemUseSeReset_2aea90();
        ItemUseMaybe_2eef60(h, &v80, MenuItemUseFxCb_2ae7c0, 0, &flag);
        bool ok = true;
        if ((u32)(s5v - 0x40DA) < 6) {
            ok = false;
        }
        if (ok) {
            s32 x = GetCurrentScene_1f5be0();
            if (flag) {
                SoundPlayScaledVolume_1b9520(GameSceneSoundSlot1GetHandle_1d07b0(x), 0x4A, SoundNextPlayHandle_1b81c0(), 1.0f);
            } else {
                SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 6, SoundNextPlayHandle_1b81c0(), 1.0f);
            }
        }
        if (flag) {
            MenuItemUseTargetMemberGaugesRefresh_2a2800(D_00482374, 0xEF);
            MenuItemUseTargetMemberStatValues_2a25c0(D_00482374, 0xEC);
            MenuItemUseTargetReserveGaugesRefresh_2a1ab0(D_00482374, 0x105);
            StateMachineSetState_28ede0(D_0048235C, 0x2C, 0);
        }
    } else if (st == 2) {
        SoundPlayScaledVolume_1b9520(D_004824C4, 6, 0, 1.0f);
        StateMachineSetState_28ede0(D_0048235C, 0x2B, 0);
    }
    return 1;
}
