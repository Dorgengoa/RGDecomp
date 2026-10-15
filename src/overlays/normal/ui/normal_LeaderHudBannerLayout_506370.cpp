#include "types.h"
/* normal 0x00506370 -- lay out the 0x3C-family caption box.  Stages a cleared
 * 12-byte block plus two Vec3 copies from gp small data on the stack, fills
 * the 9 fields of the widget cell, then measures the string through a C++
 * VIRTUAL (`lw $25,0x470($25) / jalr $25`, vptr offset 0 so slot index
 * (0x470-8)/4 = 282) and converts the accumulated height back to an int.
 *
 * The byte-clear loop at sp+0x90 NULL-CHECKS the address of a local, which is
 * never hand-written C -- it is a block-scoped `= {0}` array initialiser
 * (levers.d/mwcc-array-initialiser-clear-loop).
 * The 4 far s16 globals are INCOMPLETE extern arrays so they take %hi/%lo;
 * the 6 Vec3 sources are separate f32 scalars so each stays under the
 * small-data threshold and comes out gp-relative.
 * m2c invented four arguments for func_1FEDE0 out of the argument registers
 * the preceding store sequence happened to leave live -- it takes none. */

typedef struct Vec3 { f32 x; f32 y; f32 z; } Vec3;

typedef struct Cell {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s16 f008;
    s16 f00A;
    s16 f00C;
    s16 f00E;
    f32 f010;
} Cell;

typedef struct Box {
    s16 f000;
    u8  pad002[2];
    s32 f004;
    u8  pad008[2];
    u8  f00A;
    u8  pad00B[1];
    s32 f00C;
} Box;

typedef struct Rec {
    u8    pad000[0x20];
    Cell *f020;
    u8    pad024[4];
    Box  *f028;
} Rec;

typedef struct Panel {
    u8  pad000[0xAC];
    s16 f0AC;
} Panel;

typedef struct Slots {
    u8  pad000[0x10];
    s32 f010[4];
} Slots;

typedef struct Ctx {
    u8    pad000[0x18];
    void *f018;
} Ctx;

struct Meas {
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
    virtual void *fetch();
};

extern "C" const s16 D_00526478[];
extern "C" const s16 D_00526480[];
extern "C" const s16 D_00526488[];
extern "C" const s16 D_00526490[];

extern "C" f32 D_00480600;     /* gp - 0x4B70 */
extern "C" f32 D_00480604;     /* gp - 0x4B6C */
extern "C" f32 D_00480608;     /* gp - 0x4B68 */
extern "C" f32 D_00480610;     /* gp - 0x4B60 */
extern "C" f32 D_00480614;     /* gp - 0x4B5C */
extern "C" f32 D_00480618;     /* gp - 0x4B58 */

extern "C" void *func_289B60(void);
extern "C" Rec  *func_290460(void *a, s32 id);
extern "C" Ctx  *func_1FEDE0(void);
extern "C" Meas *func_3C2820(void *a);
extern "C" s32   func_3A07A0(void *a);
extern "C" s32   func_134BB0(s32 a);
extern "C" void  func_290010(void *a, s32 id, s32 c, s32 d);
extern "C" void  normal_LeaderHudSetBannerWidth_506ad0(Panel *a, s32 b);

extern "C" s32 normal_LeaderHudBannerLayout_506370(Panel *a0, s32 a1, s32 a2, Slots *a3);

s32 normal_LeaderHudBannerLayout_506370(Panel *a0, s32 a1, s32 a2, Slots *a3)
{
    void *own;
    Rec  *rec;
    Cell *cell;
    Ctx  *ctx;
    Meas *ms;
    Box  *bx;
    void *res;
    f32   y;
    s32   cnt;
    s32   i;
    s32   v;
    s32   ret;

    own = func_289B60();
    if (own == NULL) {
        return 0;
    }
    rec = func_290460(own, a1);
    if (rec == NULL) {
        return 0;
    }
    cell = rec->f020;
    if (cell == NULL) {
        return 0;
    }
    cnt = 0;
    for (i = 0; i < 4; i++) {
        if (a3->f010[i] == -1) {
            break;
        }
        cnt++;
    }
    if (cnt == 0) {
        return 0;
    }
    {
        Vec3 pad = {0};
        Vec3 v1 = *(Vec3 *)&D_00480600;
        Vec3 v2 = *(Vec3 *)&D_00480610;

        pad.x = 0.0f;

        y = 0.0f;
        cell->f000 = (s16)y;
        cell->f002 = (s16)v1.x;
        cell->f004 = cell->f00C = D_00526488[0];
        cell->f006 = cell->f00E = D_00526490[0];
        cell->f008 = D_00526478[0];
        cell->f00A = D_00526480[0];
        cell->f010 = v2.x;
        y = y + (f32)cell->f004;
    }

    ctx = func_1FEDE0();
    if (ctx == NULL) {
        return (s32)y;
    }
    ms = func_3C2820(ctx->f018);
    if (ms == NULL) {
        return (s32)y;
    }
    res = ms->fetch();
    if (res == NULL) {
        return (s32)y;
    }
    bx = rec->f028;
    bx->f00A = 2;
    bx->f004 = func_3A07A0(res);
    bx->f00C = 0xFF404040;
    v = 0x14 - func_134BB0(bx->f004);
    if (v < 0) {
        v = 0;
    }
    if (v > 4) {
        bx->f000 = 0x16;
        v = 4;
    } else {
        bx->f000 = 0xC;
    }
    a0->f0AC = v;
    y = (y - (f32)(v * 9 + 8)) - 8.0f;
    func_290010(own, a1, 1, -1);
    ret = (s32)y;
    normal_LeaderHudSetBannerWidth_506ad0(a0, ret);
    return ret;
}
