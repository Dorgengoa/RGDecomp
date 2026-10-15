#include "types.h"
/* normal 0x00507170 -- rebuilds the D_00525A10 id list.  Iterates the party
 * roster, and for every member whose slot-238 query is true records the
 * iteration index into the next list slot and raises the gp `any` flag; if any
 * survived, refreshes the 0xF gauge through normal_LeaderHudBossGaugeUpdate_506fe0.
 *
 * C++ virtual: `lw $25,0x3C0($25)` -> slot (0x3C0-8)/4 = 238.
 * The two `dsll32/dsra32 ..,16` pairs are explicit `(s16)` casts on s32
 * counters, not s16 locals.
 *
 * BYTE-IDENTICAL (s23), 26 bad -> MATCH on ONE TOKEN, found by
 * build/wf-normal/s23/bl_screen.py: retail has `bnel` at the iterator latch
 * where ours had `bne`.  `while ((e = f(&it)) != 0)` tests the ASSIGNMENT
 * EXPRESSION -- the call's return in $2 -- so the coalescing copy into `e`'s
 * register is independent of the branch and mwcc SINKS it into the delay slot.
 * `while (e = f(&it), e != 0)` tests the NAMED `e`, the copy must precede the
 * branch, and mwcc falls back to the likely-branch strategy retail has.
 * Same close as normal_TransWarpListCollapse_51ad60; see its header for the measured
 * alternatives.  [[mwcc-branch-likely-duplication]] read in REVERSE. */
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
    virtual s32 s238();
};

typedef struct It  { u8 pad00[8]; } It;
typedef struct Ctx { u8 pad00[0x1C]; void *f1C; } Ctx;

extern s16 D_00525A10[64];

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern u8    D_00484570;          /* gp - 0xC00 */
extern f32   D_0047D34C;          /* gp - 0x7E24 */

extern Ctx  *func_1FEDE0(void);
extern void  func_370170(It *it, void *src);
extern Ent  *func_370040(It *it);
extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_290010(void *p, u16 id, s32 c, s32 d);
extern void  func_2907A0(void *p, u16 id, f32 v);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void  normal_LeaderHudBossGaugeUpdate_506fe0(void);
}

extern "C" s32 normal_LeaderHudBossGaugeRebuild_507170(void)
{
    It   it;
    Ctx *c;
    Ent *e;
    s32  i;
    s32  n;

    c = func_1FEDE0();
    func_370170(&it, c->f1C);
    D_00484570 = 0;
    func_131B60(D_00525A10, -1, 0x20);
    func_290010(D_00484564, 0xE, 0, -1);
    i = 0;
    n = 0;
    while (e = func_370040(&it), e != 0) {
        if (e->s238() != 0) {
            D_00484570 = 1;
            D_00525A10[(s16)n] = i;
            n = (s16)(n + 1);
        }
        i = (s16)(i + 1);
    }
    if (D_00484570 != 0) {
        normal_LeaderHudBossGaugeUpdate_506fe0();
        func_290010(D_00484564, 0xE, 1, -1);
        func_2907A0(D_00484564, 0xF, 0.0f);
        func_290690(D_00484564, 0xF, 1.0f, D_0047D34C, -1.0f);
    }
    return 0;
}
