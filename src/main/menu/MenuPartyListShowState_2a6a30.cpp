#pragma optimization_level 3
#include "types.h"

typedef struct Rect {
    s32 x, y, w, h;
} Rect;

typedef struct Desc {
    void *tex;      /* +0x00 */
    s16 *info;      /* +0x04 */
    s32 pad08[2];
    s32 x;          /* +0x10 */
    s32 y;          /* +0x14 */
    s32 w;          /* +0x18 */
    s32 h;          /* +0x1C */
    Rect rect;      /* +0x20 */
    s16 mode;       /* +0x30 */
} Desc;

typedef struct Cell {
    s16 a[8];
    f32 u, v;
    s16 b, c;
    u16 flags;
} Cell;

typedef struct Actor {
    u8 pad0[0x18];
    s32 id;
} Actor;

extern "C" Actor *GetGameData_1fede0(void);
class VObj {
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
    virtual s32 IsBusy();
};
extern "C" VObj *PartyGetSlotChara_3c2fb0(s32, s32);
extern "C" s32 MsgTableLookup_28aa30(void *, s32);
extern "C" void UiSetTextString_28f510(s32, s32, s32, s32);
extern "C" void *memset(void *, s32, u32);
extern "C" void *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern "C" s16 *UiGetWidgetText_28f620(s32, s32, s32);
extern "C" void UiWindowFitToText_28d0c0(Desc *, s32, s32, s32);
extern "C" void UiSetTextY_28f550(s32, s32, s32, s32);
extern "C" void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern "C" void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
extern "C" void MenuPartyItemSkillListLayoutMaybe_2a2ee0(s32, s32, s32, s32, s32, void *);
extern "C" void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern "C" void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern "C" s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
extern "C" void StateMachineSetState_28ede0(void *, s32, s32);
extern "C" void UiSelFrameAnimStep_28d820(void *, s32);
extern f32 D_0047D6D0;
extern void *D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482374;
extern void *D_004823D8;
extern u8 D_004B2570[];
extern u8 D_004DB430[];

extern "C" s32 MenuPartyListShowState_2a6a30(s32 arg0, s32 arg1)
{
    Desc a;
    Desc b;
    Actor *actor;
    VObj *o;
    s32 n;
    s32 i;
    s32 w;
    Cell *src;
    Cell *dst;
    Rect *r;

    if (arg1 != 0) {
        actor = GetGameData_1fede0();
        n = 0;
        for (i = 0; i < 8; i++) {
            o = PartyGetSlotChara_3c2fb0(actor->id, i);
            if (o != 0 && o->IsBusy() == 0) {
                n++;
            }
        }
        UiSetTextString_28f510(D_00482360, 0x9B, MsgTableLookup_28aa30(D_004823D8, 0x3F1), 0);
        UiSetTextString_28f510(D_00482360, 0x9C, MsgTableLookup_28aa30(D_004823D8, 0x3F1), 0);
        memset(&a, 0, 0x34);
        memset(&b, 0, 0x34);
        a.tex = UiGetWidgetSprite_28fe10(D_00482360, 0x9B, 0);
        b.tex = UiGetWidgetSprite_28fe10(D_00482360, 0x9C, 0);
        a.info = b.info = UiGetWidgetText_28f620(D_00482360, 0x9C, 0);
        b.x = 0x28;
        a.y = 0xC;
        w = (n - 1) * 0x1A + 0xC;
        b.y = w;
        b.w = 0x12;
        b.h = 8;
        a.h = 8;
        a.x = 0x28;
        b.rect.x = 0x62;
        b.rect.y = 69.0f + (f32)(n - n * 14);
        a.w = 0x12;
        b.rect.w = 0x186;
        b.rect.h = 0x12C;
        r = &b.rect;
        a.rect.x = r->x; a.rect.y = r->y; a.rect.w = r->w; a.rect.h = r->h;
        b.rect.y += w / 2 + 0x1A;
        b.mode = 4;
        a.mode = 4;
        UiWindowFitToText_28d0c0(&a, 0, 0, 0);
        UiWindowFitToText_28d0c0(&b, 0, 0, 0);
        UiSetTextY_28f550(D_00482360, 0x9B, a.info[1] - 0x20, 0);
        src = (Cell *)UiGetWidgetSprite_28fe10(D_00482360, 0x9B, 0);
        if (src == 0) {
            return 0;
        }
        { s16 a0_ = ((volatile Cell *)src)->a[0]; UiSetWidgetPos_290f60(D_00482360, 0x9A, a0_ - *(volatile s16 *)((u8 *)src + 0x104) - 0x10, src[0].a[1]); }
        dst = (Cell *)UiGetWidgetSprite_28fe10(D_00482360, 0x99, 0);
        if (dst == 0) {
            return 0;
        }
        i = 0;
        do {
            Cell *c = &src[i];
            Cell *d = &dst[i];
            d->a[0] = c->a[0];
            d->a[1] = c->a[1];
            d->a[2] = c->a[2];
            d->a[3] = c->a[3];
            d->a[4] = c->a[4];
            d->a[5] = c->a[5];
            d->a[6] = c->a[6];
            d->a[7] = c->a[7];
            d->u = c->u;
            d->v = c->v;
            d->b = c->b;
            d->c = c->c;
            d->flags = c->flags;
            d->flags = 0x40;
            i++;
        } while (i < 3);
        UiSetSpriteSizeUvSize_28f670(D_00482360, 0x9B, 0, 0, 0, 0, 4);
        UiSetTextString_28f510(D_00482360, 0x9C, 0, 0);
        MenuPartyItemSkillListLayoutMaybe_2a2ee0(D_00482374, 0x9C, 0x9F, 0x9D, 0x9E, D_004823D8);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x99, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x99, 1.0f, D_0047D6D0, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x9C, 1, 1);
        UiFadeWidgetAlpha_290690(D_00482360, 0x9C, 1.0f, D_0047D6D0, 0.0f);
    }
    if ((u32)(MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0) - 1) < 2) {
        StateMachineSetState_28ede0(D_0048235C, 0x3E, 0);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
