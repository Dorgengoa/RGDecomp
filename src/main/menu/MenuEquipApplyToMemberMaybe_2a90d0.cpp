#include "types.h"

typedef struct Card Card;

class Member {
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
    virtual s32 getName();
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
    virtual void attach(Card *c);
};

typedef struct Cursor {
    u8 pad[0x14];
    s16 col;
    s16 row;
} Cursor;

typedef struct Face {
    u8 pad[0x2C];
    s16 x2C;
} Face;

struct Card {
    u8 pad[0x10];
    Face *face;
};

typedef struct Panel {
    s16 x;
    s16 y;
} Panel;

typedef struct Party {
    u8 pad[0x18];
    s32 x18;
} Party;

typedef struct Menu {
    u8 pad[0x11];
    s8 x11;
} Menu;

extern "C" {
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Menu *D_00482374;
extern s8 D_00482500;
extern f32 D_0047D6E4;
extern f32 D_0047D35C;
extern f32 D_0047D588;
extern f32 D_0047D6E8;
extern f32 D_0047D6D0;
extern u8 D_004B2570[];

extern Cursor *UiEntryListFindByTag_28ea40(s32 a, s32 b);
extern void UiEntryListSelectByTag_28ea90(s32 a, s32 b, s32 c);
extern void UiFadeWidgetAlpha_290690(s32 a, s32 b, f32 x, f32 y, f32 z);
extern Party *GetGameData_1fede0(void);
extern Card *MenuGetItemAtCell_2a7000(s32 a, s32 b);
extern Panel *UiGetWidgetSprite_28fe10(s32 a, s32 b, s32 c);
extern void UiSetItemIconUv_288e50(Panel *p, s32 a, s32 b, s32 c);
extern void UiSetSpriteFlags_290bd0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void UiSetWidgetColor_2905b0(s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void UiFadeWidgetColor_2904e0(s32 a, s32 b, f32 x, f32 y, f32 z, f32 w, f32 v);
extern Member *PartyGetSlotChara_3c2fb0(s32 a, s32 b);
extern void MenuSetTitleFmtMaybe_2a3f40(Menu *m, s32 n);
extern void PlayMenuSe_289ef0(s32 a);
extern f32 *UiGetWidgetColor_2904b0(s32 a, s32 b);
extern void UiSetWidgetsVisibleById_291110(s32 a, s32 b, s32 c, s32 d);
extern void UiSetWidgetPos_290f60(s32 a, s32 b, s32 c, s32 d);
extern s32 MenuGridCursorInput_28e170(s32 a, void *b, s32 c, s32 d);
extern void StateMachineSetState_28ede0(s32 a, s32 b, s32 c);
}

extern "C" s32 MenuEquipApplyToMemberMaybe_2a90d0(s32 unused, s32 init)
{
    Cursor *cur;
    s32 sel;
    Party *party;
    Card *card;
    Panel *panel;
    s32 i;
    Member *m;
    s32 r;
    s32 t;

    cur = UiEntryListFindByTag_28ea40(D_00482364, 10);
    sel = cur->col + cur->row * 4;
    if (init) {
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D6E4, -1.0f);
        party = GetGameData_1fede0();
        t = (s32)UiEntryListFindByTag_28ea40(D_00482364, 3);
        card = MenuGetItemAtCell_2a7000(D_00482374->x11, t + 4);
        if (card == 0) {
            return 0;
        }
        panel = UiGetWidgetSprite_28fe10(D_00482360, 0xB0, sel);
        if (panel == 0) {
            return 0;
        }
        UiSetItemIconUv_288e50(panel, card->face->x2C, 0x28, 0x2D);
        panel->x = cur->col * 97 + 0x4E;
        panel->y = (cur->row + 1) * 97;
        for (i = 0; i < 8; i++) {
            if (i == sel) {
                UiSetSpriteFlags_290bd0(D_00482360, 0xB0, 8, -1, i, 0);
            } else {
                UiSetSpriteFlags_290bd0(D_00482360, 0xB0, 8, 1, i, 0);
            }
        }
        UiSetWidgetColor_2905b0(D_00482360, 0xB0, D_0047D35C, D_0047D35C, D_0047D35C, 1.0f);
        UiFadeWidgetColor_2904e0(D_00482360, 0xB0, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D588);
        m = PartyGetSlotChara_3c2fb0(party->x18, sel);
        if (m == 0) {
            return 0;
        }
        MenuSetTitleFmtMaybe_2a3f40(D_00482374, m->getName());
        m->attach(card);
        PlayMenuSe_289ef0(9);
        D_00482500 = 0;
    }
    if (*UiGetWidgetColor_2904b0(D_00482360, 0xB0) < D_0047D6E8 && D_00482500 == 0) {
        UiSetWidgetsVisibleById_291110(D_00482360, 0xB4, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0xB4, 0x89, 0xD2);
        UiFadeWidgetAlpha_290690(D_00482360, 0xB4, 1.0f, D_0047D6D0, 0.0f);
        D_00482500 = 1;
    }
    if (D_00482500 == 1) {
        r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
        if (r == 1 || r == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0x48, 0);
        }
    }
    return 1;
}
