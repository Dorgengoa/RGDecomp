/* SESSION 32 (lane nc32q): BYTE-IDENTICAL -- 137 words, 0 bad, MATCH under
 * build/wf-normal/s32/nscore.py.  Reached from the s31 draft (137 w / 12 bad)
 * by a THREE-EDIT CROSS in which no single edit pays:
 *   1. the o-guard became an assignment INSIDE the condition, and the guard
 *      exits with `return 0;` (with `goto _x29;` it is 139 words / 92 bad);
 *   2. `p = func_36FFF0(&it, st); if (p != 0)` became
 *      `if ((p = func_36FFF0(&it, st)) != 0)` -- retail tests the RAW call
 *      result with a non-likely branch and sinks the copy into the delay slot;
 *   3. `lim = it.f04;` moved from before func_3A8180 to after func_370170
 *      (it is only meaningful there -- func_370170 fills `it`).
 * Then the last two words: `o` is TWO variables.  o2 is the short-lived
 * caller-saved copy ($2) that feeds func_3A8180's second argument, `o` is the
 * callee-saved one ($19) the loop uses; and the `o = o2` copy must sit BEFORE
 * the guard, which is what turns `bnel $2,$0` into retail's plain `bne`.
 * Deck: 107 arms over 3 bulk32 decks; see build/wf-normal/s32/reports/nc32q.md
 */
#include "types.h"
/* normal 0x00502E50 -- paints `cnt` inventory cells starting at widget id
 * `base`, three ids apart.  Each cell is cleared, then in `mode` 0 it takes the
 * next item's icon and is greyed 0xFF202020, darkened to 0xFF404040 when the
 * owner's slot-178 query claims it; past the end of the list, or in any other
 * mode, the cell is just blanked.
 *
 * C++ virtual: `lw $25,0x2D0($25)` -> slot (0x2D0-8)/4 = 178, taking the item's
 * s16 id straight from an `lh` -- the callee parameter is `s16`.
 * `andi $22,$17,0xFFFF` hoisted above the loop is the NAMED `u16` base id. */
class Own {
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
    virtual s32 owns(s16 k);
};

typedef struct It  { u8 pad00[4]; s16 f04; u8 pad06[2]; } It;
typedef struct Qry { u8 pad00[0x18]; } Qry;
typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct St  { u8 pad00[0x76]; s16 f76; } St;
typedef struct Itm { s16 f00; u8 pad02[6]; s32 f08; } Itm;

extern "C" {
extern void *D_004844A0;          /* gp - 0xCD0 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern St   *D_00484454;          /* gp - 0xD1C */

extern Ctx  *func_1FEDE0(void);
extern s32   func_28EC60(void *p);
extern Own  *func_3C2FB0(s32 w, s32 k);
extern void  func_3A8180(Qry *q, Own *o, s32 a, s32 b);
extern void  func_370170(It *it, Qry *q);
extern Itm  *func_36FFF0(It *it, s32 n);
extern Itm  *func_370040(It *it);
extern void  func_290A80(void *p, u16 id, s32 a, s32 b);
extern void  func_290A40(void *p, u16 id, s32 rgba, s32 a);
extern void  func_290B20(void *p, u16 id, s32 a, s32 b, s32 c, s32 d);
extern s32   normal_BtlChgPageGetMember_505f90(St *s);
}

extern "C" s32 normal_BtlChgMenuAbilityNamesRefresh_502e50(s32 base, s32 cnt, s32 mode)
{
    u16  id;
    It   it;
    Qry  q;
    Ctx *c;
    Own *o;
    Own *o2;
    Itm *p;
    s32  i;
    s32  st;
    s32  lim;
    u16  b16;

    if (func_28EC60(D_004844A0) == 0) {
        return 0;
    }
    st = D_00484454->f76;
    c = func_1FEDE0();
    if (c == 0) {
        return 0;
    }
    o2 = func_3C2FB0(c->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
    o = o2;
    if (o2 == 0) {
        return 0;
    }
    func_3A8180(&q, o2, 0, -1);
    func_370170(&it, &q);
    lim = it.f04;
    if ((p = func_36FFF0(&it, st)) != 0) {
        b16 = (u16)base;
        for (i = 0; i < cnt; i++) {
            id = (u16)(b16 + i * 3);
            func_290A80(D_0048449C, id, 2, 0);
            if (mode != 0) {
                if ((st + i) < lim) {
                    func_290B20(D_0048449C, id, 0, -1, -1, 0);
                }
            } else {
                if (((st + i) < lim) && (p != 0)) {
                    func_290B20(D_0048449C, id, p->f08, -1, -1, 0);
                    func_290A40(D_0048449C, id, 0xFF202020, 0);
                    if (o->owns(p->f00) != 0) {
                        func_290A40(D_0048449C, id, 0xFF404040, 0);
                    }
                } else {
                    func_290B20(D_0048449C, id, 0, -1, -1, 0);
                }
                p = func_370040(&it);
            }
        }
    }
    return 1;
_x29:
    return 0;
}
