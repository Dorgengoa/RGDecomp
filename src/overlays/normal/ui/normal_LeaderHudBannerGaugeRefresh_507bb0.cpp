#include "types.h"
/* normal 0x00507BB0 -- the 0xC / 0xD page-counter refresh.  Both counter
 * widgets are hidden, the active entity's slot-284 page total and slot-283
 * current page are read, and if the book has a scroll position the 0xD label is
 * placed and shown (plus the 0x7 arrow when the total is positive).  The
 * slot-282 "dirty" query drives the one-shot re-open and is latched into
 * D_00484584.
 *
 * C++ virtuals: 0x470/0x474/0x478 -> slots 282 / 283 / 284. */
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
    virtual s32 s283();
    virtual s32 s284();
};

typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern void *D_0048456C;          /* gp - 0xC04 */
extern s32   D_00484584;          /* gp - 0xBEC */

extern Ctx *func_1FEDE0(void);
extern Ent *func_3C2820(s32 w);
extern void func_291110(void *p, u16 id, s32 c, s32 d);
extern void func_290F60(void *p, u16 id, s32 x, s32 y);
extern void func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void func_2905B0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern s32  normal_LeaderHudGetBannerWidth_506ac0(void *p);
extern void normal_LeaderHudSetBannerCountdown_506ab0(void *p, s32 a);
extern void normal_LeaderHudSetBannerBlinking_506af0(void *p, s32 a);
extern void normal_LeaderHudGaugeBarSet_506630(void *p, s32 id, s32 c, s32 d, f32 x, f32 y);
extern void normal_LeaderHudBannerBlinkTick_507a90(void);
}

extern "C" s32 normal_LeaderHudBannerGaugeRefresh_507bb0(void)
{
    Ctx *c;
    Ent *e;
    s32  tot;
    s32  cur;
    s32  pos;

    func_291110(D_00484564, 0xC, 0, 1);
    func_291110(D_00484564, 0xD, 0, 1);
    c = func_1FEDE0();
    if (c == 0) {
        return 0;
    }
    e = func_3C2820(c->f18);
    if (e == 0) {
        return 0;
    }
    tot = e->s284();
    cur = e->s283();
    pos = normal_LeaderHudGetBannerWidth_506ac0(D_0048456C);
    normal_LeaderHudGaugeBarSet_506630(D_0048456C, 0xD, 1, 0x66, (f32)cur, (f32)tot);
    if (pos != 0) {
        func_290F60(D_00484564, 0xD, pos - 0x86, 0x26);
        func_291110(D_00484564, 0xD, 1, 1);
        if (tot > 0) {
            func_290690(D_00484564, 7, 1.0f, 0.0625f, -1.0f);
        }
    }
    if (e->s282() == 0) {
        if (D_00484584 != 0) {
            normal_LeaderHudSetBannerBlinking_506af0(D_0048456C, 1);
            normal_LeaderHudSetBannerCountdown_506ab0(D_0048456C, 0x1E);
        }
    }
    func_2905B0(D_00484564, 7, 1.0f, 1.0f, 1.0f, -1.0f);
    normal_LeaderHudBannerBlinkTick_507a90();
    D_00484584 = e->s282();
    return 1;
}
