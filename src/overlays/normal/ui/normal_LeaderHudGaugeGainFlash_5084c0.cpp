/* === SESSION 53 (2026-09-08, SOLO): CLOSED.  74 bad / 215 words -> MATCH,
 * object cefcaa97.  FOUR edits, in the order they were found; each is priced.
 * NOTHING below this note reflects the current state -- read it as history.
 *
 * (1) + (2) A CROSS, and NEITHER HALF WORKS ALONE (both are LENGTH-WRONG on
 *     their own; together they are exact) -- [[two-edit-cross-beats-count-ranking]]:
 *       (1) `hi = b[(s16)n + 1];` HOISTED ABOVE the `if (d != 0)` test.  The
 *           tell is retail 0x005085A8 `beqz $17,.L00508758` carrying
 *           `lw $3,0x68($4)` in its DELAY SLOT, with the `sll/addu` that
 *           builds &b[n] two slots above the branch: retail computes hi
 *           UNCONDITIONALLY.  Alone: 0x358 vs 0x35c (one word SHORT).
 *       (2) `D_00484578 = v;` MOVED UP to before `func_28FCD0(...)`, the first
 *           of the four widget calls.  The tell is retail 0x0050869C
 *           `jal func_28FCD0` / 0x005086A0 `sw $18,-0xBF8($28)` -- the store
 *           is in that call's delay slot.  Alone: 0x360 (one word LONG).
 *     Together: 74 -> 18.
 * (3) `*(AU *)tbl = *(AU *)&D_00480620[0];` with
 *     `typedef union AU { s16 v[4]; S3 s; }` -- the FULL FOUR-ELEMENT copy.
 *     18 -> 11 (7 words: the fill window at 0x005084DC-F4).
 *     ⚠ [[mwcc-aggregate-fill-vs-elementwise]] says a 4-entry table wants the
 *     3+1 SPLIT; here the 3+1 split (`*(S3 *)tbl = ...; tbl[3] = ...;`) and
 *     the `au.s = ...; au.v[3] = ...;` union-member form are BOTH INERT
 *     (identical object to the elementwise baseline).  Only the 8-byte
 *     `*(AU *)` cast reaches retail's L,L,L,S,S,S + L,S.  The 3+1 rule is
 *     normal_BtlChgMenuMsgBoxOpenState_4fcc90's, not a board-wide one.
 * (4) `struct BW { s32 pad; s32 b[5]; } bw;` -- the one-word pad wrapper that
 *     s51 wrote down as untried arm 1 and s44 identified as the defect.
 *     18 -> 11 on its own, and it is INDEPENDENT of (3): crossing them is 4.
 *     It confirms s44's reading exactly: our local area starts at 0x60 and
 *     mwcc rounds b[5]'s 20 bytes up to 24; the pad puts b at 0x64 with tbl
 *     still at 0x78.  ⚠ THIS IS THE SAME SHAPE AS normal_LeaderHudGaugeLevelRefresh_507ff0
 *     (`v[]` at 0x74 retail / 0x6C ours) -- an EIGHT-byte shift, so try a
 *     TWO-word pad there.
 * (5) `r = 88.0f; r = r / (f32)(hi - lo);` instead of
 *     `r = 88.0f / (f32)(hi - lo);` -- 4 -> MATCH.  The last four words were a
 *     pure FPR swap: retail `div.s $f1,$f1,$f0` coalesces the destination with
 *     the NUMERATOR's register, ours `div.s $f1,$f0,$f1` with the
 *     DENOMINATOR's.  Splitting the literal into its own assignment to `r`
 *     makes r the numerator's register.  ⚠ The n==0 arm's IDENTICAL spelling
 *     (`r = 88.0f / (f32)b[1];`) already MATCHED ($f2/$f1), which is why this
 *     read as an allocator fact and not a shape fact.
 *     MEASURED INERT on this axis: a named `f32 num` numerator local (either
 *     decl position), a named `f32 den` denominator local, and all three
 *     tested decl-order permutations of {r,s,t}.  `r /= ...` and hoisting
 *     `d = hi - lo;` give the SAME object -- three spellings, one object.
 */
/* === SESSION 51 (2026-09-08): NOT SWEPT, but s44's frame fact now has a NAME
 * and a candidate arm, from the alignment work that closed four units this
 * session ([[mwcc-sdata-alignment-wrapper]], [[mwcc-union-aggregate-fill]]).
 * s44 measured `b[]` at 0x60 ours / 0x64 retail with `tbl` at 0x78 in both,
 * and that OUR local area starts at 0x60 while retail's `b[5]` is 20 bytes
 * TIGHT (0x64 + 20 = 0x78).  Read as an ALIGNMENT fact: mwcc gives `s32 b[5]`
 * an 8-ALIGNED cell and rounds 20 up to 24; retail's is 4-ALIGNED.
 * TWO UNTRIED ARMS, in this order:
 *   1. a wrapper that forces the 4-alignment -- `struct { s32 pad; s32 b[5]; }`
 *      -- which puts b at 0x64 exactly, at the cost of a dead word at 0x60;
 *   2. s44's own reading, that retail HAS a 4-byte memory-homed local at
 *      0x60..0x63 that we keep in a register.  Look for the scalar retail
 *      spills and we do not ([[mwcc-stack-slot-decl-order]], spmap.py).
 * The same shape with an EIGHT-byte shift is on normal_LeaderHudGaugeLevelRefresh_507ff0. */
/* SESSION 44 (n44p/n44q, SOLO): 74 bad / 215 words, UNMOVED, but the defect
 * class is now IDENTIFIED and it is one NO EXISTING SCREEN COULD SEE.
 * The new build/wf-normal/s44/offscan.py reads `0x60: retail 0 -> ours 2`,
 * `0x64: 2 -> 1`, `0x68: 1 -> 0`, and the full K($sp) sets say the same thing
 * with no ambiguity at all:
 *     retail  0x68 x2, 0x6C, 0x70   tbl 0x78,0x7A,0x7C,0x7E
 *     ours    0x64 x2, 0x68, 0x6C   tbl 0x78,0x7A,0x7C,0x7E
 * `tbl` is at 0x78 in BOTH; `b[]` is at 0x64 in retail and 0x60 in ours.
 * EVERY frame slot below tbl is shifted by exactly -4.
 * spscan.py CANNOT see this: every b[] access is `K($3)` with
 * `$3 = $sp + i*4`, not `K($sp)`, so the frame slot hides behind a COMPUTED
 * base.  That is the gap offscan.py was written to fill.
 * MEASURED (17 arms): the base is 0x60 for b[4], b[5] AND b[6] -- b's own size
 * does not move it -- and for all six declaration permutations of
 * {b[5], hi, lo, tbl[4], r, s, t} including tbl-before-b and floats-first.
 * `s16 tbl[5]` reads 78, `s32 tbl[4]` moves b to 0x70 and reads 79, `b[7]` and
 * `b[8]` push tbl to 0x88.  So OUR local area starts at 0x60 and mwcc rounds
 * b[5]'s 20 bytes up to 24; RETAIL's b[5] is 20 bytes TIGHT against tbl
 * (0x64 + 20 = 0x78) with 0x60..0x63 belonging to something else.
 * `gbuild.py` confirms: b sp+0x60, tbl sp+0x78, r/s/t sp+0x80, the rest in
 * registers.
 * => Retail has FOUR MORE BYTES of frame below `b[]` than we do, and it is not
 * a declaration-order fact.  normal_LeaderHudGaugeLevelRefresh_507ff0 shows the SAME shape with an
 * EIGHT-byte shift (`v[]` at 0x74 retail / 0x6C ours), so this is a two-unit
 * class, not a quirk. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_D_00484578_L404_T408_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 216 words, ? bad   after: 215 words, 74 bad   (retail 215 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x005084C0 -- session 31 lane a8, FRESH.
 * The widget-0x14 gauge updater.  Reads a 4-entry s16 table out of gp
 * (D_00480620) into a stack copy, gets the field context and its entity, asks
 * the entity for slot 303 (a small count) and slot 305 (a value), and when the
 * value moved since the last frame (D_00484578) recomputes an 88-wide bar
 * position/width from the thresholds b[1..3] fetched through func_3F9480.
 * Then it drives the widget's four sub-fields and pulses its tint through
 * func_128FD0 over the gp phase D_00484580, wrapping at pi (D_0047D1FC).
 *
 * C++ virtual: lw $25,0x4C4($25) -> slot (0x4C4-8)/4 = 303,
 *              lw $25,0x4CC($25) -> slot 305.  vptr offset 0x0.
 * dsll32/dsra32 ..,16 pairs are explicit (s16) casts written at each use.
 * cvt.w.s appears in the listing as a bare .word -- it is a float->int cast.
 */
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
    virtual void s282();
    virtual void s283();
    virtual void s284();
    virtual void s285();
    virtual void s286();
    virtual void s287();
    virtual void s288();
    virtual void s289();
    virtual void s290();
    virtual void s291();
    virtual void s292();
    virtual void s293();
    virtual void s294();
    virtual void s295();
    virtual void s296();
    virtual void s297();
    virtual void s298();
    virtual void s299();
    virtual void s300();
    virtual void s301();
    virtual void s302();
    virtual s32 s303();
    virtual void s304();
    virtual s32 s305();
};

typedef struct S3 { s16 x; s16 y; s16 z; } S3;
typedef union  AU { s16 v[4]; S3 s; } AU;
typedef struct Inner2 { u8 pad00[8]; s32 f8; } Inner2;
typedef struct Inner1 { u8 pad00[0x54]; Inner2 *f54; } Inner1;
typedef struct Ctx { u8 pad00[8]; Inner1 *f8; u8 pad0C[0x18 - 0xC]; s32 f18; } Ctx;

extern "C" {
extern s16   D_00480620[4];       /* gp - 0x4B50 */
extern void *D_00484564;          /* gp - 0xC0C  */
extern s32   D_00484578;          /* gp - 0xBF8  */
extern f32   D_00484580;          /* gp - 0xBF0  */
extern f32   D_0047D1FC;          /* gp - 0x7F74 */
extern f32   D_0047D518;          /* gp - 0x7C58 */
extern f32   D_0047D53C;          /* gp - 0x7C34 */

extern Ctx *func_1FEDE0(void);
extern Ent *func_3C2820(s32 w);
extern f32  func_128FD0(f32 t);
extern s32  func_3F9480(s32 p, s32 i);
extern void func_28F810(void *p, s32 id, s32 a, s32 b);
extern void func_28F8F0(void *p, s32 id, s32 a, s32 b);
extern void func_28FBB0(void *p, s32 id, s32 a, s32 b);
extern void func_28FBF0(void *p, s32 id, s32 a, s32 b);
extern void func_28FCD0(void *p, s32 id, s32 a, s32 b);
extern void func_2905B0(void *p, s32 id, f32 a, f32 b, f32 c, f32 d);
}

extern "C" s32 normal_LeaderHudGaugeGainFlash_5084c0(void);

s32 normal_LeaderHudGaugeGainFlash_5084c0(void)
{
    Ctx *c;
    Ent *e;
    s32  n;
    s32  v;
    s32  d;
    s32  i;
    s32  a;
    s32  w;
    s32  k;
    struct BW { s32 pad; s32 b[5]; } bw;
    s32  hi;
    s32  lo;
    s16  tbl[4];
    f32  r;
    f32  s;
    f32  t;

    *(AU *)tbl = *(AU *)&D_00480620[0];
    c = func_1FEDE0();
    if (c == 0) {
        return 1;
    }
    e = func_3C2820(c->f18);
    if (e == 0) {
        return 2;
    }
    n = (s16)e->s303();
    v = e->s305();
    d = (s16)(v - D_00484578);
    for (i = 1; i <= 3; i++) {
        bw.b[i] = func_3F9480(c->f8->f54->f8, i);
    }
    hi = bw.b[(s16)n + 1];
    if (d != 0) {
        if ((s16)n == 0) {
            r = 88.0f / (f32)bw.b[1];
            a = (s16)(s32)(r * (f32)D_00484578);
            w = (s16)(s32)r;
        } else if (v == bw.b[1] || v == bw.b[2] || v == bw.b[3]) {
            a = 0;
            w = 0x58;
        } else {
            lo = bw.b[(s16)n];
            r = 88.0f;
            r = r / (f32)(hi - lo);
            a = (s16)(s32)(r * (f32)(v - lo));
            w = (s16)(s32)r;
        }
        D_00484578 = v;
        func_28FCD0(D_00484564, 0x14, (s16)a + 0x50, 0);
        func_28FBF0(D_00484564, 0x14, (s16)w, 0);
        func_28FBB0(D_00484564, 0x14, 6, 0);
        func_28F810(D_00484564, 0x14, 6, 0);
        k = (s16)((s16)n - 1);
        if (k < 0) {
            k = 0;
        }
        func_28F8F0(D_00484564, 0x14, tbl[(s16)k], 0);
        D_00484580 = 0.5f;
        s = 1.0f + func_128FD0(D_00484580);
        func_2905B0(D_00484564, 0x14, s, s, s, -1.0f);
    }
    if (D_00484580 < D_0047D1FC) {
        t = func_128FD0(D_00484580);
        if (!(t < D_0047D53C)) {
            t = D_0047D53C;
        }
        s = 1.0f + t;
        func_2905B0(D_00484564, 0x14, s, s, s, -1.0f);
    }
    D_00484580 = D_00484580 + D_0047D518;
    if (!(D_00484580 < D_0047D1FC)) {
        D_00484580 = D_0047D1FC;
        func_28FBB0(D_00484564, 0x14, 0, 0);
        func_28F810(D_00484564, 0x14, 0, 0);
    }
    return 0;
}
