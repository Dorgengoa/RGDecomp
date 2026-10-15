#include "types.h"

class BV {
public:
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void set(void *);
};

class B : public BV {
public:
    u8 pad4[0xC];
    u8 *m10;
};

class A {
public:
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual s32 f60();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual void v028();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual void v034();
    virtual void v035();
    virtual void v036();
    virtual void v037();
    virtual void v038();
    virtual void v039();
    virtual void v040();
    virtual void v041();
    virtual void v042();
    virtual void v043();
    virtual void v044();
    virtual void v045();
    virtual void v046();
    virtual void v047();
    virtual void v048();
    virtual void v049();
    virtual void v050();
    virtual void v051();
    virtual void v052();
    virtual void v053();
    virtual void v054();
    virtual void v055();
    virtual void v056();
    virtual void v057();
    virtual void v058();
    virtual void v059();
    virtual void v060();
    virtual void v061();
    virtual void v062();
    virtual void v063();
    virtual void v064();
    virtual void v065();
    virtual void v066();
    virtual void v067();
    virtual void v068();
    virtual void v069();
    virtual void v070();
    virtual void v071();
    virtual void v072();
    virtual void v073();
    virtual void v074();
    virtual void v075();
    virtual void v076();
    virtual void v077();
    virtual void v078();
    virtual void v079();
    virtual void v080();
    virtual void v081();
    virtual void v082();
    virtual void v083();
    virtual void v084();
    virtual void v085();
    virtual void v086();
    virtual void v087();
    virtual void v088();
    virtual void v089();
    virtual void v090();
    virtual void v091();
    virtual void v092();
    virtual void v093();
    virtual void v094();
    virtual void v095();
    virtual void v096();
    virtual void v097();
    virtual void v098();
    virtual void v099();
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
    virtual B *f388();
    virtual B *f38C();
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
    virtual B *f3C4();
};

extern "C" {
extern void Sprintf_1343b8(u8 *, s32, s32);
extern void UiSetItemIconUv_288e50(u8 *, s32, s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
extern s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
extern u8 *UiGetWidgetText_28f620(s32, s32, s32);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern u8 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern u8 *CharaGetIconRecMaybe_3ae3e0(A *);
extern A *ItemFindOwnerChara_3d4d80(B *, s32);
extern s16 D_00450D30[];
extern s16 D_00450D32[];
extern s16 D_00450D34[];
extern s32 D_004823D8;
extern u8 D_004DB310[];
extern u8 D_004DB350[];
}

extern "C" s32 MenuItemEquipCompareShowMaybe_2a4310(u8 *arg0, B *arg1) {
    A *a;
    s32 id;
    u8 *w;
    u8 *m;
    B *b;
    s32 x;
    s32 y;
    s32 i;

    if (arg1 == 0) {
        return 0;
    }
    a = ItemFindOwnerChara_3d4d80(arg1, 1);
    if (a == 0) {
        return 0;
    }
    id = *(s16 *)(CharaGetIconRecMaybe_3ae3e0(a) + 0x2C);
    w = UiGetWidgetSprite_28fe10(*(s32 *)arg0, 0xAA, 0);
    if (w == 0) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (id == D_00450D30[i * 3]) {
            *(s16 *)(w + 0x8) = D_00450D32[i * 3];
            *(s16 *)(w + 0xA) = D_00450D34[i * 3];
            *(s16 *)(w + 0xC) = 0x36;
            *(s16 *)(w + 0x4) = 0x36;
            *(s16 *)(w + 0xE) = 0x42;
            *(s16 *)(w + 0x6) = 0x42;
            break;
        }
    }
    m = UiGetWidgetText_28f620(*(s32 *)arg0, 0xA6, 0);
    if (m == 0) {
        return 0;
    }
    Sprintf_1343b8(arg0 + 0x172, MsgTableLookup_28aa30(D_004823D8, 0x44E), a->f60());
    *(u8 **)(m + 4) = arg0 + 0x172;
    UiSetTextCenteredX_28f300(*(s32 *)arg0, 0xA6, 0x9D, 0);
    *(s16 *)m += 0x10;
    b = 0;
    x = *(s8 *)(arg1->m10 + 2);
    if (x == 0) {
        b = a->f388();
    } else if (x == 1) {
        b = a->f38C();
    } else if (x == 2) {
        b = a->f3C4();
    }
    if (b == 0) {
        return 0;
    }
    b->set(D_004DB310);
    arg1->set(D_004DB350);
    *(u8 **)(m + 0x14) = D_004DB310;
    *(u8 **)(m + 0x24) = D_004DB350;
    w = UiGetWidgetSprite_28fe10(*(s32 *)arg0, 0xA8, 0);
    if (w == 0) {
        return 0;
    }
    UiSetItemIconUv_288e50(w, *(s16 *)(b->m10 + 0x2C), 0x28, 0x2D);
    UiSetItemIconUv_288e50(w + 0x20, *(s16 *)(arg1->m10 + 0x2C), 0x28, 0x2D);
    x = UiGetWidgetTextWidth_28f400(*(s32 *)arg0, 0xA6, 1);
    y = UiGetWidgetTextWidth_28f400(*(s32 *)arg0, 0xA6, 2);
    UiSetSpriteX_28fcd0(*(s32 *)arg0, 0xA5, (x / 2 + y / 2) / 2 + 0x69, 2);
    return 1;
}
