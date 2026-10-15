#include "types.h"
/* normal 0x00507540 -- the book screen's per-frame driver.  The 00506b20 phase
 * selects the open / close / page-turn transitions, then the 00506b00 mode runs
 * the matching sub-screen, and finally the 0xBC hold-down counter is ticked and
 * the fade is retired when it reaches zero.
 *
 * C++ virtual: `lw $25,0x470($25)` -> slot (0x470-8)/4 = 282.
 * The four phase arms are laid out 0 / 3 / 2 / 1 in ADDRESS order, so that is
 * the SOURCE order -- mwcc builds the compare chain itself
 * (levers.d/m2c-switch-arm-order). */
class Ent {
public:
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual void s128();
    virtual void s129();
    virtual void s130();
    virtual void s131();
    virtual void s132();
    virtual void s133();
    virtual void s134();
    virtual void s135();
    virtual void s136();
    virtual void s137();
    virtual void s138();
    virtual void s139();
    virtual void s140();
    virtual void s141();
    virtual void s142();
    virtual void s143();
    virtual void s144();
    virtual void s145();
    virtual void s146();
    virtual void s147();
    virtual void s148();
    virtual void s149();
    virtual void s150();
    virtual void s151();
    virtual void s152();
    virtual void s153();
    virtual void s154();
    virtual void s155();
    virtual void s156();
    virtual void s157();
    virtual void s158();
    virtual void s159();
    virtual void s160();
    virtual void s161();
    virtual void s162();
    virtual void s163();
    virtual void s164();
    virtual void s165();
    virtual void s166();
    virtual void s167();
    virtual void s168();
    virtual void s169();
    virtual void s170();
    virtual void s171();
    virtual void s172();
    virtual void s173();
    virtual void s174();
    virtual void s175();
    virtual void s176();
    virtual void s177();
    virtual void s178();
    virtual void s179();
    virtual void s180();
    virtual void s181();
    virtual void s182();
    virtual void s183();
    virtual void s184();
    virtual void s185();
    virtual void s186();
    virtual void s187();
    virtual void s188();
    virtual void s189();
    virtual void s190();
    virtual void s191();
    virtual void s192();
    virtual void s193();
    virtual void s194();
    virtual void s195();
    virtual void s196();
    virtual void s197();
    virtual void s198();
    virtual void s199();
    virtual void s200();
    virtual void s201();
    virtual void s202();
    virtual void s203();
    virtual void s204();
    virtual void s205();
    virtual void s206();
    virtual void s207();
    virtual void s208();
    virtual void s209();
    virtual void s210();
    virtual void s211();
    virtual void s212();
    virtual void s213();
    virtual void s214();
    virtual void s215();
    virtual void s216();
    virtual void s217();
    virtual void s218();
    virtual void s219();
    virtual void s220();
    virtual void s221();
    virtual void s222();
    virtual void s223();
    virtual void s224();
    virtual void s225();
    virtual void s226();
    virtual void s227();
    virtual void s228();
    virtual void s229();
    virtual void s230();
    virtual void s231();
    virtual void s232();
    virtual void s233();
    virtual void s234();
    virtual void s235();
    virtual void s236();
    virtual void s237();
    virtual void s238();
    virtual void s239();
    virtual void s240();
    virtual void s241();
    virtual void s242();
    virtual void s243();
    virtual void s244();
    virtual void s245();
    virtual void s246();
    virtual void s247();
    virtual void s248();
    virtual void s249();
    virtual void s250();
    virtual void s251();
    virtual void s252();
    virtual void s253();
    virtual void s254();
    virtual void s255();
    virtual void s256();
    virtual void s257();
    virtual void s258();
    virtual void s259();
    virtual void s260();
    virtual void s261();
    virtual void s262();
    virtual void s263();
    virtual void s264();
    virtual void s265();
    virtual void s266();
    virtual void s267();
    virtual void s268();
    virtual void s269();
    virtual void s270();
    virtual void s271();
    virtual void s272();
    virtual void s273();
    virtual void s274();
    virtual void s275();
    virtual void s276();
    virtual void s277();
    virtual void s278();
    virtual void s279();
    virtual void s280();
    virtual void s281();
    virtual s32 s282();
};

typedef struct Bk  { u8 pad00[0xBC]; s32 fBC; } Bk;
typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern Bk   *D_0048456C;          /* gp - 0xC04 */

extern Ctx *func_1FEDE0(void);
extern Ent *func_3C2820(s32 w);
extern s32  func_2899B0(Bk *p, s32 id);
extern void func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern s32  normal_LeaderHudGetBannerWidth_506ac0(Bk *p);
extern void normal_LeaderHudSetBannerBlinking_506af0(Bk *p, s32 a);
extern s32  normal_LeaderHudGetPanelMode_506b00(Bk *p);
extern void normal_LeaderHudSetPanelMode_506b10(Bk *p, s32 a);
extern s32  normal_LeaderHudGetBannerPhase_506b20(Bk *p);
extern void normal_LeaderHudSetBannerPhase_506b30(Bk *p, s32 a);
extern s32  normal_LeaderHudGetField74Related_506b50(Bk *p);
extern void normal_LeaderHudBossGaugeUpdate_506fe0(void);
extern void normal_LeaderHudWeaponShakeStep_5072a0(void);
extern void normal_LeaderHudReload_507990(void);
extern void normal_LeaderHudBannerRefresh_507a30(s32 a);
extern void normal_LeaderHudBannerSlide_507d70(s32 a, s32 b, s32 c);
extern void normal_LeaderHudGaugeLevelRefresh_507ff0(s32 a);
extern void normal_LeaderHudWeaponRefresh_508990(s32 a);
extern void normal_LeaderHudPanelSlide_509040(s32 a, s32 b, s32 c);
}

extern "C" s32 normal_LeaderHudUpdateState_507540(void)
{
    Ctx *c;
    Ent *e;
    Bk  *p;
    s32 *q;

    normal_LeaderHudWeaponShakeStep_5072a0();
    switch (normal_LeaderHudGetBannerPhase_506b20(D_0048456C)) {
    case 0:
        normal_LeaderHudBannerRefresh_507a30(0);
        break;
    case 3:
        if (func_2899B0(D_0048456C, 7) != 0) {
            normal_LeaderHudSetBannerPhase_506b30(D_0048456C, 0);
        }
        break;
    case 2:
        if (func_2899B0(D_0048456C, 7) != 0) {
            normal_LeaderHudBannerRefresh_507a30(0);
            c = func_1FEDE0();
            if (c == 0) {
                return 0;
            }
            e = func_3C2820(c->f18);
            if (e == 0) {
                return 0;
            }
            if (e->s282() != 0) {
                normal_LeaderHudSetBannerBlinking_506af0(D_0048456C, 0);
                normal_LeaderHudBannerSlide_507d70(normal_LeaderHudGetBannerWidth_506ac0(D_0048456C), 1, 1);
            }
            func_290690(D_00484564, 7, 1.0f, 0.0625f, -1.0f);
            normal_LeaderHudSetBannerPhase_506b30(D_0048456C, 3);
        }
        break;
    case 1:
        p = D_0048456C;
        q = &p->fBC;
        if (p->fBC == 0) {
            *q = 7;
        }
        break;
    }
    normal_LeaderHudBossGaugeUpdate_506fe0();
    if (normal_LeaderHudGetPanelMode_506b00(D_0048456C) == 0) {
        normal_LeaderHudWeaponRefresh_508990(0);
        normal_LeaderHudGaugeLevelRefresh_507ff0(0);
    } else if (normal_LeaderHudGetPanelMode_506b00(D_0048456C) == 3) {
        if (func_2899B0(D_0048456C, 2) != 0) {
            normal_LeaderHudSetPanelMode_506b10(D_0048456C, 0);
        }
    } else if (normal_LeaderHudGetPanelMode_506b00(D_0048456C) == 2) {
        if (func_2899B0(D_0048456C, 2) != 0) {
            normal_LeaderHudReload_507990();
        }
    } else if (normal_LeaderHudGetPanelMode_506b00(D_0048456C) == 1) {
        normal_LeaderHudPanelSlide_509040(0, 0, normal_LeaderHudGetField74Related_506b50(D_0048456C));
        normal_LeaderHudSetPanelMode_506b10(D_0048456C, 2);
    }
    p = D_0048456C;
    q = &p->fBC;
    if (p->fBC > 0) {
        *q = p->fBC - 1;
        p = D_0048456C;
        if (p->fBC <= 0) {
            normal_LeaderHudBannerSlide_507d70(normal_LeaderHudGetBannerWidth_506ac0(p), 0, 0);
            func_290690(D_00484564, 7, 0.0f, 0.0625f, -1.0f);
            normal_LeaderHudSetBannerPhase_506b30(D_0048456C, 2);
            D_0048456C->fBC = 0;
        }
    }
    return 1;
}
