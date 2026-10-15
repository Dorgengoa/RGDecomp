/* === SESSION 43 (2026-09-07, SOLO): 45 bad -> MATCH.  585 words / 2,340 B.
 * TWO EDITS, A REQUIRED CROSS -- each one alone is the WRONG LENGTH:
 *   1. `Pan *pb;` moved to the LAST declaration position.  That flips the
 *      allocation tie this unit's header had called "one ALLOCATION TIE
 *      between the loop bound and the loop panel": retail keeps `cnt` in
 *      $22 and spills `pb` to 0xCC($sp); we had it exactly the other way,
 *      so the 0x2B loop test cost an extra `lw $2,0xCC($sp)` (-1 word).
 *   2. The 0x2A caption guard spelled `if (dist >= 75.0f) { a = 0.0f; }
 *      else { a = (75.0f - dist) * K; }` (+1 word).
 * SCREENS THAT FOUND IT (both new to this unit, run BEFORE any arm):
 *   - build/wf-normal/s43/opscan.py  -> `daddu:76->77`
 *   - build/wf-normal/s43/spscan.py  -> `0xCC:3->2  0xC4:2->3`, the
 *     STACK-SLOT class ([[levers.d/mwcc-stack-slot-decl-order]]), which no
 *     NORMAL screen had ever named.
 * ⚠⚠ THIS UNIT RETIRES TWO OF ITS OWN RECORDED VERDICTS:
 *   a. "s31: `if (d<75){small} else {a=0;}` and `if (!(d<75)){a=0;} else
 *      {small}` are the SAME OBJECT -- mwcc normalises the arm swap."  TRUE
 *      for those two, but `dist >= 75.0f` is a THIRD object and it is the
 *      matching one.  On a FLOAT guard, `>=` is NOT `!(<)`: `!(d<75)` keeps
 *      `c.lt.s` + `bc1f`+nop with the small arm INLINE; `d>=75` emits
 *      `c.lt.s` + `bc1tl` INTO a small arm moved to the BOTTOM, with the
 *      subtraction in the likely slot and the call's `daddu $5,$18,$0`
 *      duplicated into the `b`'s delay.  Sweep `>=` separately from `!(<)`.
 *   b. s31's 1,891-arm whole-list declaration sweep found this unit's decl
 *      order inert.  It was inert IN THAT COAT.  With edit 2 installed the
 *      coat changes, and then 29 of 30 decl positions are STILL inert but
 *      `pb` last is 45 -> 7 ([[levers.d/normal-session42-levers]]'s rule:
 *      a coat change invalidates every statement-order null measured in the
 *      old coat -- re-sweep, do not trust the recorded null).
 * ⚠ s31's `__w553` call-result split is LOAD-BEARING, not a scaffold:
 * folding it back to `cnt = func_3C2610(...)` is 0x928, one word LONG. */
/* SESSION 31 (3/3): 69 -> 45 bad at exact length on a 1,891-arm deck
 * (defining-statement moves + the whole-list declaration sweep over 35
 * declarations).  160 distinct objects; 29 arms reach 45 and ALL 29 ARE
 * ONE OBJECT -- moving `e`'s declaration down to position 28-34, or
 * `id`'s to 09-17, are the same lever.  1,096 of the 1,891 arms are the
 * base object, so the axis is narrow but real here.
 * Installed: `Ent *e;` moved below `Cam *cam;`. */
/* SESSION 31 (2/2): RIGHT LENGTH AT LAST -- 585 words, 69 bad, after
 * many sessions LENGTH-WRONG.  The whole length defect was ONE FP guard
 * at 0x004F3F68.  `if (d < 75) {small} else {a = 0;}` and `if (!(d<75))
 * {a=0;} else {small}` are the SAME OBJECT -- mwcc normalises the arm
 * swap -- and the ternary collapses onto it too.  What pays is deleting
 * the else: `a = 0.0f; if (d < 75.0f) { a = ...; }`, which lets mwcc
 * thread the arm and fill the branch-likely delay slot (bc1f+nop ->
 * bc1tl+sub.s).  8 arms; p_seed2 (the inverse seed) is 584, two short.
 * ==> A RECORDED POLARITY VERDICT IS SITE-SPECIFIC.  This unit's own
 * header said the polarity here had been measured and the current
 * spelling was retail's; that measurement was on the 0x2A caption site.
 * RESIDUE NOW: ~50 of the 69 words are a pure s1 <-> s2 TRANSPOSITION
 * over the entity iterator and the u16 loop counter, plus `cnt` which
 * retail keeps in $s6 where we spill it to 204(sp).  KEEP OUT OF
 * config/ocunits/normal.txt. */
/* SESSION 31: l1 8 -> 4 at the same 586 words, on ONE arm of the
 * pool-wide CALL-ARGUMENT EXTRACTION deck (mkextract31.py, family SP:
 * split the call RESULT onto a fresh web).  `cnt = func_3C2610(...)`
 * became `__w553 = func_3C2610(...); cnt = __w553;` and the whole
 * CALLEE-SAVED imbalance reconciled: sq/lq/sw/lw were +1/+1/-1/-1
 * against retail and are now exact.  The unit is still LENGTH-WRONG,
 * 586 vs retail's 588, and the residue is now exactly TWO NOPS plus
 * one FP branch that is `bc1f` where retail has `bc1tl` -- a
 * branch-likely site whose delay slot we fill and retail does not
 * ([[mwcc-branch-likely-duplication]]).  KEEP OUT OF
 * config/ocunits/normal.txt. */
/* !! PARKED, ONE WORD LONG (0x928 vs 0x924).  NOT under src/.
 * 3 scoring round trips + one 5-arm sweep.  585 retail words, 586 ours, and
 * the WHOLE surplus is one instruction: at 0x004F3EE4 retail tests the 0x2B
 * loop with `slt $2,$17,$22` -- the bound lives in $22, the register `w`
 * vacates after the entity loop -- while mwcc spills the bound to 0xB0 and
 * reloads it with an `lq` at every iteration, keeping the loop PANEL in $22
 * instead.  Retail spills that panel to 0xCC.  So the residue is one
 * ALLOCATION TIE between the loop bound and the loop panel, not structure:
 * every other hunk in the unit is a 1-for-1 scheduling swap that cancels.
 *
 * ARMS MEASURED against that one word (all still 586 words):
 *  base  `pb = func_290460(m,id); o = pb->f20;`            -> d1a73ff1
 *  D     `o = (pb = func_290460(m,id))->f20;`              -> d1a73ff1, INERT
 *  E     bound copied through a second local (`n`, then `cnt = n`)
 *                                    -> 4452a915, a live object, same length
 *  F     reuse the 0x25 panel variable `p` for the loop     -> same length
 *  G     `cnt` moved to the FIRST declaration position, ahead of every
 *        pointer local  -> INERT, the hunk list is the same set
 * !! Three further sweep arms (block-scoped panel / reuse p / reuse pc) DID
 * print the right length at 362 bad -- they are MALFORMED, not a result: the
 * replacement dropped the panel's definition while leaving its use, so the
 * call read an uninitialised local.  Recorded so nobody re-reads that row as
 * a hit.
 *
 * Everything else in the unit is confirmed correct: two C++ classes (vptr
 * +0xC0 slot 44 on func_1C3BC0's return, vptr +0 slots 45/134/242 on the list
 * entity), the five distance-fade blocks, the 57/67 thresholds on the 0x3E
 * cursor, and the STALE `id` the 0x2A caption reads out of the 0x2B loop.
 * The 0x2A guard polarity was measured: `if (dist < 75.0f) {small} else
 * {a = 0.0f;}` is retail's `bc1tl`-into-the-small-arm layout and the inverse
 * spelling costs a `b`+`nop` pair.
 */
/* (s23) The iterator latch was CORRECTED, not closed: bl_screen.py reported
 * retail `bnel` vs our `bne` at 0x004F3BC0, and the comma-operator loop test
 * `while (e = func_370040(&it), e != 0)` clears it -- the screen is now silent
 * on this unit.  Same lever as MERGED normal_TransWarpListCollapse_51ad60 / 00507170.
 * STILL LENGTH-WRONG (0x928 vs 0x924) on unrelated classes: an `sq` where
 * retail has `daddu` at 0x004F3D68, a `daddu`/`lw` pair in the same block, and
 * `bc1f nop sub.s lwc1 b` where retail has `bc1tl sub.s mtc1 b daddu lwc1`.
 * ⚠ The `trunc.w.s` / `.word` hunks odiff prints are NOT differences -- same
 * encoding 0x46000864. */

#include "types.h"
/* normal 0x004F3720 -- 2,340 bytes, 585 instructions.  The town-map marker
 * refresh: it walks the entity list, and for every marker widget it computes
 * the planar distance from the fixed map centre (92,106) and fades / clamps
 * the marker by that distance.  The same distance-fade block appears FIVE
 * times (entity solid, entity pulsing, the 0x3E cursor, the 0x2B..0x2B+n
 * bookmarks and the 0x2A caption), which is why one spelling carries the
 * whole unit.
 *
 * TWO C++ classes, both read straight off the `lw $25,K(...)` sites:
 *   - the object from func_1C3BC0 has its vptr at +0xC0 and calls slot
 *     (0xB8-8)/4 = 44;
 *   - the list entity has its vptr at +0x00 and calls slots 45 (0xBC),
 *     134 (0x220) and 242 (0x3D0).
 * The 0xC0 and 0x0 vptrs sit on DIFFERENT objects (one is func_1C3BC0's
 * return, the other func_370040's), so the one-subtraction test does not
 * apply -- these really are two classes.
 *
 * The 0x2A caption at the end reuses `id` from the 0x2B loop without
 * reassigning it -- that stale read is retail's, not a transcription slip,
 * which is why `id` is a function-scope u16.
 */

typedef struct V4 { f32 x; f32 y; f32 z; f32 w; } V4;
typedef struct It { void *f00; void *f04; } It;

typedef struct Obj { s16 f00; s16 f02; } Obj;
typedef struct Pan { u8 pad00[0x04]; u8 f04[0x10];
                     f32 f14; f32 f18; u8 pad1C[0x20 - 0x1C]; Obj *f20; } Pan;
typedef struct Menu { u8 pad000[0x4F0]; s32 f4F0; } Menu;
typedef struct W { u8 pad0000[0x4344]; s32 f4344; } W;
typedef struct Stage { u8 pad000[0x18E]; s16 f18E; } Stage;
typedef struct Ctx { u8 pad00[0x18]; Stage *f18; void *f1C; } Ctx;

class Cam {
public:
    u8 pad000[0xC0];
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
    virtual f32  eyeY();          /* slot 44 -> vtable +0xB8 */
};

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
    virtual s32  isSolid();       /* slot 45  -> vtable +0xBC  */
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
    virtual s32  phase();         /* slot 134 -> vtable +0x220 */
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
    virtual s32  hidden();        /* slot 242 -> vtable +0x3D0 */
    u8  pad04[0x0C - 0x04];
    s32 f0C;
};

extern "C" {

extern f32 D_0047D1FC;            /* gp - 0x7F74,  3.141592741 */
extern f32 D_0047D814;            /* gp - 0x795C,  0.05        */
extern f32 D_0047D7CC;            /* gp - 0x79A4,  0.1         */
extern f32 D_0047D824;            /* gp - 0x794C,  3.14        */

extern s32   func_15DE80(void);
extern s32   func_15DE40(void);
extern Ctx  *func_1FEDE0(void);
extern W    *func_1F5BE0(void);
extern Pan  *func_290460(Menu *m, u16 id);
extern s16  *func_159FB0(s32 h, void *p, s32 k);
extern void  func_1418C0(s32 h, s16 v, f32 a);
extern Cam  *func_1C3BC0(W *w, s32 k);
extern void  func_370170(It *it, void *list);
extern Ent  *func_370040(It *it);
extern s32   func_141B00(s32 h);
extern void  func_141A20(s32 h);
extern s32   func_1C4A90(W *w, s32 k);
extern f32   func_13D390(V4 *a, V4 *b);
extern void  func_13BD90(V4 *a, V4 *b);
extern void  func_2907A0(Menu *m, u16 id, f32 a);
extern f32   func_128D30(f32 x);
extern s32   func_3C2610(Stage *s, s32 a, s32 b);
extern void *func_1FDB50(void);
extern void *func_233B50(void *p, s16 k);
extern void  func_2388E0(void *p, V4 *out);
extern void  normal_FieldHudRadarDrawBlip_4f33f0(Menu *m, s32 e, Pan *p, s32 x, s32 y, s16 *t);
extern void  normal_FieldHudRadarDrawArrow_4f2ff0(Menu *m, s32 e, Pan *p, s32 x, s32 y, s16 *t,
                                 f32 a);

extern void normal_FieldHudRadarDraw_4f3720(Menu *m);

}

void normal_FieldHudRadarDraw_4f3720(Menu *m)
{
    It    it;
    V4    ref;
    V4    cur;
    V4    d1;
    V4    d2;
    V4    d3;
    V4    d4;
    V4    box;
    s32   h1;
    s32   h0;
    Ctx  *g;
    W    *w;
    s32   cnt;
    Pan  *p;
    Pan  *pc;
    Cam  *cam;
    Obj  *o;
    s16  *t;
    void *q;
    s32   x;
    s32   y;
    s32   ec;
    s32   ec3;
    s32   n;
    s32   i;
    s16   k;
    u16   id;
    Ent  *e;
    f32   camY;
    f32   dist;
    f32   a;
    f32   a2;
    f32   ph;
    s32 __w553;
    Pan  *pb;

    h1 = func_15DE80();
    h0 = func_15DE40();
    g  = func_1FEDE0();
    if (g != 0) {
        w = func_1F5BE0();
        if (w != 0) {
            p = func_290460(m, 0x25);
            x = (s32) p->f14;
            y = (s32) p->f18;
            ref.x = 92.0f;
            ref.y = 0.0f;
            ref.z = 106.0f;
            ref.w = 1.0f;
            t = func_159FB0(h0, &p->f04, 0x32B);
            if (t != 0) {
                func_1418C0(h1, *t, 1.0f);
            }
            func_290460(m, 0x27);
            cam = func_1C3BC0(w, w->f4344);
            if (cam != 0) {
                camY = cam->eyeY();
                func_370170(&it, g->f1C);
                n  = 0;
                ec = func_141B00(h1);
                while (e = func_370040(&it), e != 0) {
                    if ((func_1C4A90(w, e->f0C) != 0) && (e->hidden() == 0)) {
                        id = n + 0x2E;
                        p  = func_290460(m, id);
                        o  = p->f20;
                        cur.x = (f32) o->f00;
                        cur.y = 0.0f;
                        cur.z = (f32) o->f02;
                        cur.w = 1.0f;
                        dist = func_13D390(&ref, &cur);
                        if (e->isSolid() != 0) {
                            if (!(dist < 65.0f)) {
                                if (!(dist < 75.0f)) {
                                    d1.x = (f32) o->f00 - ref.x;
                                    d1.y = 0.0f;
                                    a = D_0047D814;
                                    d1.z = (f32) o->f02 - ref.z;
                                    d1.w = 1.0f;
                                    func_13BD90(&d1, &d1);
                                    o->f00 = (s16) (s32) (ref.x + 75.0f * d1.x);
                                    o->f02 = (s16) (s32) (ref.z + 75.0f * d1.z);
                                } else {
                                    a = D_0047D814 + (75.0f - dist) * D_0047D7CC;
                                }
                                func_2907A0(m, id, a);
                            }
                        } else {
                            ph = D_0047D1FC * ((f32) (e->phase() % 32) / 16.0f);
                            a2 = 0.0f;
                            if ((f32) e->phase() < 112.0f) {
                                a2 = (1.0f + func_128D30(ph)) / 2.0f;
                            }
                            if (!(dist < 65.0f)) {
                                if (!(dist < 75.0f)) {
                                    d2.x = (f32) o->f00 - ref.x;
                                    d2.y = 0.0f;
                                    a = D_0047D814;
                                    d2.z = (f32) o->f02 - ref.z;
                                    d2.w = 1.0f;
                                    func_13BD90(&d2, &d2);
                                    o->f00 = (s16) (s32) (ref.x + 75.0f * d2.x);
                                    o->f02 = (s16) (s32) (ref.z + 75.0f * d2.z);
                                } else {
                                    a = D_0047D814 + (75.0f - dist) * D_0047D7CC;
                                }
                                a2 = a2 * a;
                            }
                            func_2907A0(m, id, a2);
                        }
                        normal_FieldHudRadarDrawBlip_4f33f0(m, ec, p, x, y, t);
                        n = n + 1;
                    }
                }
                func_141A20(h1);
                pc = func_290460(m, 0x3E);
                o  = pc->f20;
                cur.x = (f32) o->f00;
                cur.y = 0.0f;
                cur.z = (f32) o->f02;
                cur.w = 1.0f;
                dist = func_13D390(&ref, &cur);
                if (!(dist < 57.0f)) {
                    if (!(dist < 67.0f)) {
                        d3.x = (f32) o->f00 - ref.x;
                        d3.y = 0.0f;
                        a = D_0047D814;
                        d3.z = (f32) o->f02 - ref.z;
                        d3.w = 1.0f;
                        func_13BD90(&d3, &d3);
                        o->f00 = (s16) (s32) (ref.x + 75.0f * d3.x);
                        o->f02 = (s16) (s32) (ref.z + 75.0f * d3.z);
                    } else {
                        a = D_0047D814 + (67.0f - dist) * D_0047D7CC;
                    }
                    func_2907A0(m, 0x3E, a);
                }
                ec3 = func_141B00(h1);
                if (m->f4F0 != -1) {
                    normal_FieldHudRadarDrawBlip_4f33f0(m, ec3, pc, x, y, t);
                }
                func_141A20(h1);
                __w553 = func_3C2610(g->f18, 1, 1);
                cnt = __w553;
                ec3 = func_141B00(h1);
                for (i = 0; i < cnt; i++) {
                    id = i + 0x2B;
                    pb = func_290460(m, id);
                    o  = pb->f20;
                    cur.x = (f32) o->f00;
                    cur.y = 0.0f;
                    cur.z = (f32) o->f02;
                    cur.w = 1.0f;
                    dist = func_13D390(&ref, &cur);
                    if (!(dist < 65.0f)) {
                        if (!(dist < 75.0f)) {
                            d4.x = (f32) o->f00 - ref.x;
                            d4.y = 0.0f;
                            a = D_0047D814;
                            d4.z = (f32) o->f02 - ref.z;
                            d4.w = 1.0f;
                            func_13BD90(&d4, &d4);
                            o->f00 = (s16) (s32) (ref.x + 75.0f * d4.x);
                            o->f02 = (s16) (s32) (ref.z + 75.0f * d4.z);
                        } else {
                            a = D_0047D814 + (75.0f - dist) * D_0047D7CC;
                        }
                        func_2907A0(m, id, a);
                    }
                    normal_FieldHudRadarDrawBlip_4f33f0(m, ec3, pb, x, y, t);
                }
                func_141A20(h1);
                pc = func_290460(m, 0x2A);
                o  = pc->f20;
                cur.x = (f32) o->f00;
                cur.y = 0.0f;
                cur.z = (f32) o->f02;
                cur.w = 0.0f;
                dist = func_13D390(&ref, &cur);
                if (!(dist < 65.0f)) {
                    if (dist >= 75.0f) {
                        a = 0.0f;
                    } else {
                        a = (75.0f - dist) * D_0047D7CC;
                    }
                    func_2907A0(m, id, a);
                }
                k = g->f18->f18E;
                q = func_1FDB50();
                if (q != 0) {
                    q = func_233B50(q, k);
                    if (q != 0) {
                        func_2388E0(q, &box);
                        normal_FieldHudRadarDrawArrow_4f2ff0(m, func_141B00(h1), pc, x, y, t,
                                            (D_0047D824 + box.y) - camY);
                        func_141A20(h1);
                    }
                }
            }
        }
    }
}
