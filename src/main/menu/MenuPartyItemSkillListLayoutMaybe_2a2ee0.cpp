#include "types.h"
#pragma optimization_level 3

typedef struct {
    s16 m0;
    s16 m2;
    u8 pad4[0x100];
    s16 m104;
} Win;

typedef struct {
    s16 m0;
    s16 m2;
    s32 m4;
    s32 m8;
    s32 mC;
} Row;

class Unit {
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
    virtual s32 f5C();
    virtual s32 f60();
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
    virtual s32 f368();
};

extern "C" {
u8 *GetGameData_1fede0(s32);
s32 MsgTableLookup_28aa30(s32, s32);
void UiSetSubItemGlyphUvSize_28f100(s32, s32, s32, s32, s32);
void UiSetSubItemPos_28f200(s32, s32, s32, s32, s32);
Row *UiGetWidgetText_28f620(s32, u16, s32);
void UiSetSpriteSizeUvSize_28f670(s32, u16, s32, s32, s32, s32, s32);
void UiSetSpritePos_28fd10(s32, u16, s32, s32, s32);
Win *UiGetWidgetSprite_28fe10(s32, u16, s32);
void UiSetWidgetPos_290f60(s32, u16, s32, s32);
void UiSetWidgetSubItemValue_291250(s32, s32, s32, s64);
u8 *MenuGetSelItem_2a02d0(s32 *);
Unit *PartyGetSlotChara_3c2fb0(s32, s32);
s32 SkillFlowCountByItemMaybe_3e97c0(u8 *, s32, s32, s32, s32, s32, s32);
s32 MenuPartyItemSkillListLayoutMaybe_2a2ee0(s32 *arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5);
}

s32 MenuPartyItemSkillListLayoutMaybe_2a2ee0(s32 *arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5) {
    Win *w;
    Row *rows;
    s32 bx;
    s32 by;
    u8 *mgr;
    s32 cnt;
    s32 i;
    Unit *u;
    u8 *info;
    s32 k;
    s32 x;
    s32 y;
    s32 id;
    s32 r;
    u8 *q;
    f32 f;

    w = UiGetWidgetSprite_28fe10(*arg0, arg1, 0);
    if (w == 0) {
        return 0;
    }
    rows = UiGetWidgetText_28f620(*arg0, arg1, 0);
    if (rows == 0) {
        return 0;
    }
    bx = w->m0 - w->m104 - 0x10;
    by = w->m2;
    mgr = GetGameData_1fede0(w->m0);
    cnt = 0;
    i = 0;
    do {
        u = PartyGetSlotChara_3c2fb0(*(s32 *)(mgr + 0x18), i);
        if (u != 0 && u->f368() == 0) {
            cnt++;
        }
        i++;
    } while (i < 8);
    info = MenuGetSelItem_2a02d0(arg0);
    if (info == 0) {
        return 0;
    }
    i = 0;
    do {
        UiSetSpriteSizeUvSize_28f670(*arg0, arg3, 0, 0, 0, 0, i);
        UiSetSubItemGlyphUvSize_28f100(*arg0, arg4, 0, 0, i);
        i++;
    } while (i < 8);
    k = 0;
    i = 0;
    do {
        rows[k].m0 = -1;
        u = PartyGetSlotChara_3c2fb0(*(s32 *)(mgr + 0x18), i);
        if (u != 0 && u->f368() == 0) {
            x = bx + 0x20;
            y = by + 8 + i * 0x1A;
            rows[k].m0 = x;
            rows[k + 1].m2 = y;
            rows[k].m2 = y;
            rows[k].m4 = u->f60();
            rows[k + 1].m0 = x + 0x50;
            id = **(s16 **)(info + 0x10);
            r = SkillFlowCountByItemMaybe_3e97c0(mgr, id, u->f5C(), 0, 1, 1, 0);
            if (r > 0) {
                rows[k + 1].m4 = MsgTableLookup_28aa30(arg5, 0x3F2);
                rows[k + 1].mC = 0xFF303030;
                rows[k].mC = 0xFF303030;
                UiSetSpritePos_28fd10(*arg0, arg3, x + 0xA0, y, i);
                UiSetSpriteSizeUvSize_28f670(*arg0, arg3, 0x1C, 0x14, 0x24, 0x14, i);
                UiSetSubItemPos_28f200(*arg0, arg4, x + 0xB8, y + 3, i);
                UiSetWidgetSubItemValue_291250(*arg0, arg4, i, r);
                UiSetSubItemGlyphUvSize_28f100(*arg0, arg4, 0xC, 0x10, i);
            } else {
                rows[k + 1].m4 = MsgTableLookup_28aa30(arg5, 0x3F3);
                rows[k + 1].mC = 0xFF202020;
                rows[k].mC = 0xFF202020;
            }
            k += 2;
        }
        i++;
    } while (i < 8);
    w = UiGetWidgetSprite_28fe10(*arg0, arg2, 0);
    if (w == 0) {
        return 0;
    }
    if (cnt == 1) {
        w->m0 = -1;
    } else {
        w->m0 = 0xC;
    }
    f = cnt - 1;
    *(f32 *)((u8 *)w + 0x14) = *(f32 *)((u8 *)w + 0x34) = *(f32 *)((u8 *)w + 0x54) = f;
    UiSetWidgetPos_290f60(*arg0, arg2, bx, by);
    return 1;
}
