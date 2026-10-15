/* === SESSION 71 (2026-09-21, SOLO): 195 bad -> MATCH.  Read against the
 * listing (build/wf-normal/s71/c1..c8.py):
 *  - `found = 0;` back to right before the loop (s31's move deck had put it
 *    before func_28F510), `found = 1;` AFTER the func_291110 call (retail puts
 *    it in the `b` delay slot), `u8 found` DECLARED FIRST (fixes the i/found
 *    s1/s2 swap -- decl order of ctx was inert, found's was not).
 *  - `if (b == 0)` / `if (found == 0)` (retail re-masks both u8s); `!a` for a.
 *  - `arr[t]` / `v[t]` without s31's `(u32)` index casts.
 *  - `D_00484574 = 0;` before func_291110(0x13,0,1) (its delay slot);
 *    `i <= 3` for the `$at` loop bound; `s32 pos` (pos narrows twice).
 *  - frame: `s16 arr[4]; s32 v[3];` in THAT order -- v is only 3 long (i=1..3
 *    stores v[i-1]) and is NOT 16-aligned in retail (sp+0x78, arr sp+0x88).
 *    This is s44's "8-byte frame shift".
 *  - `s32 t = (s16)ob->m303();` and `(s16)t` at v[], the `> 0` test and
 *    v[t - 1]: retail re-narrows t after the v loop and shares t*4.
 *  - the arr fill is an 8-byte STRUCT COPY `*(S4 *)arr = *(S4 *)D_00480628;`
 *    -- emitted 0,1,2,3 unrotated; all 24 elementwise orders are rotated.
 * Everything below predates this session. */
/* === SESSION 53 (2026-09-08, SOLO): STILL 195 / 305.  MEASURED NEGATIVE, and
 * it retires s44's own suggested arm.  The sibling normal_LeaderHudGaugeGainFlash_5084c0 CLOSED
 * this session on four levers and ALL FOUR ARE NULLS HERE
 * (build/wf-normal/s53/a_507ff0.py, 8 arms):
 *   - the two-word pad wrapper `struct VW { s32 pad[2]; s32 v[4]; }` that s44
 *     wrote down for the 8-byte v[] shift: a NEW OBJECT (29ca3769) at the SAME
 *     195.  The one-word pad is likewise new (e7f7cf14) and likewise 195.
 *   - `*(AU *)arr = *(AU *)&D_00480628[0];` (the 4-element union cast that
 *     paid 7 words on the sibling): 196, one WORSE.  The 3+1 split is INERT.
 *   - splitting the 88.0f numerator into its own assignment (the sibling's
 *     last four words): a new object at 195, and 196 when crossed with A.
 * WHY IT DOES NOT TRANSFER: this unit's census is NINETY substitutions,
 * dominated by `s1>s3`/`s3>s1` -- a whole-function CALLEE-SAVED PERMUTATION
 * ([[mwcc-callee-saved-creation-order]]), not a local frame or FPR fact.  The
 * frame and fill levers move the object without moving the count because
 * everything downstream is renamed anyway.  ⚠ DO NOT re-run the sibling's
 * levers here; fix the callee-saved colouring FIRST, then re-sweep them
 * ([[two-edit-cross-beats-count-ranking]] -- a recorded null must be re-swept
 * after any coat change).
 */
/* SESSION 44 (SOLO): 195 bad / 305 words.  The new struct-field-offset screen
 * (build/wf-normal/s44/offscan.py) flags `0x6C: retail 0 -> ours 2`,
 * `0x74: 2 -> 0`, `0x70: 0 -> 1`, `0x78: 1 -> 0` -- the local `s32 v[4]` sits
 * at $sp+0x74 in retail and $sp+0x6C in ours, an EIGHT-byte frame shift that
 * displaces every access through it (`sw $2,0x74($3)` / `lw $20,0x78($2)` /
 * `lw $3,0x78($29)` / `lw $4,0x74($3)` against our 0x6C/0x70/0x70/0x6C).
 * spscan.py cannot see the ones reached through `$3 = $sp + i*4`.
 * Same class as normal_LeaderHudGaugeGainFlash_5084c0 (a FOUR-byte shift of its `b[5]`); read
 * that unit's header first, it carries the 17-arm frame probe. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_found_L412_T411_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 304 words, ? bad   after: 305 words, 217 bad   (retail 305 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `I_allu32_idx` from the index-cast deck (mkidx31.py)
 *   before: 300 words, ? bad   after: 304 words, ? bad   (retail 305 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x00507FF0 -- the battle-result / gauge HUD builder.  1232 bytes,
 * 308 instructions.  Written fresh in s31 (lane a6).
 *
 * jalr $25 x5 => C++ virtual dispatch, vptr at offset 0, slot = 8 + 4*N.
 * Slots used: 0x4C0 (idx 302), 0x4C4 (303), 0x4CC (305), 0x4DC (309).
 *
 * Stack model: s32 v[4] and s16 arr[4] adjacent at the top of the frame.
 * The store loop writes v[i-1] for i=1..3 and the reads are v[t] / v[t-1],
 * arr[t] / arr[t-1] -- the -1 folds into the load displacement (0x74 vs 0x78,
 * 0x86 vs 0x88), which is what retail shows.
 */
struct Obj {
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
    virtual s32 m302();
    virtual s32 m303();
    virtual void s304();
    virtual s32 m305();
    virtual void s306();
    virtual void s307();
    virtual void s308();
    virtual s32 m309();
};

typedef struct C2 { u8 pad000[8]; void *f008; } C2;
typedef struct C1 { u8 pad000[0x54]; C2 *f054; } C1;
typedef struct Ctx {
    u8    pad000[8];
    C1   *f008;
    u8    pad00C[4];
    void *f010;
    u8    pad014[4];
    void *f018;
    u8    pad01C[4];
    void *f020;
} Ctx;

typedef struct Box { u8 pad000[4]; const void *f004; u8 pad008[4]; u32 f00C; } Box;

extern "C" const s32 D_00526498[];

extern "C" void *D_00484564;          /* gp - 0xC0C  */
extern "C" s32   D_00484574;          /* gp - 0xBFC  */
extern "C" s16   D_00480628[4];       /* gp - 0x4B48 */

extern "C" Ctx  *func_1FEDE0(void);
extern "C" Obj  *func_3C2820(void *a);
extern "C" Obj  *func_3C2FB0(void *a, s32 i);
extern "C" s32   func_3C2010(void *a, s32 b, s32 c);
extern "C" s32   func_3C1C20(void *a, s32 b, s32 c);
extern "C" u8    func_3CCD70(void *a, s32 b);
extern "C" s32   func_3A38E0(void *a);
extern "C" s32   func_3F9480(void *a, s32 i);
extern "C" void  func_2905B0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d);
extern "C" void  func_28F510(void *w, u16 id, s32 a, s32 b);
extern "C" void  func_291110(void *w, u16 id, s32 a, s32 b);
extern "C" Box  *func_28F620(void *w, u16 id, s32 a);
extern "C" void  func_28F8F0(void *w, u16 id, s16 a, s32 b);
extern "C" void  func_28F930(void *w, u16 id, s16 a, s32 b);
extern "C" void  func_28FBF0(void *w, u16 id, s16 a, s32 b);
extern "C" void  func_28F850(void *w, u16 id, s16 a, s32 b);
extern "C" s32   normal_LeaderHudGaugeLevelPulse_508820(void);
extern "C" s32   normal_LeaderHudGaugeGainFlash_5084c0(void);

typedef struct S4 { s16 a[4]; } S4;
extern "C" s32 normal_LeaderHudGaugeLevelRefresh_507ff0(void);

s32 normal_LeaderHudGaugeLevelRefresh_507ff0(void)
{
    u8 found;
    Ctx *ctx;
    Obj *ob;
    Obj *e;
    Box *bx;
    void *p;
    s16 arr[4];
    s32 v[3];
    s32 i;
    s32 cur;
    s32 rank;
    s32 hi;
    s32 lo;
    s16 n;
    s32 t;
    s32 pos;
    u8 a;
    u8 b;

    ctx = func_1FEDE0();
    if (ctx == 0) {
        return 0;
    }
    ob = func_3C2820(ctx->f018);
    if (ob == 0) {
        return 0;
    }
    a = ob->m302();
    b = func_3CCD70(ctx->f010, 0x3ED);
    func_2905B0(D_00484564, 0x10, 1.0f, 1.0f, 1.0f, -1.0f);
    func_28F510(D_00484564, 0x10, 0, 0);
    if (b == 0) {
        func_291110(D_00484564, 0x10, 0, 1);
        return 0;
    }
    p = ctx->f018;
    n = func_3C2010(p, 1, 1) + func_3C1C20(p, 1, 1);
    found = 0;
    for (i = 0; i < n; i++) {
        e = func_3C2FB0(ctx->f018, i);
        if (e != 0) {
            if (e->m302()) {
                func_291110(D_00484564, 0x10, 1, 1);
                found = 1;
                break;
            }
        }
    }
    if (found == 0) {
        func_291110(D_00484564, 0x10, 0, 1);
        return 0;
    }
    if (!a || func_3A38E0(ctx->f020) == 0) {
        bx = func_28F620(D_00484564, 0x10, 0);
        bx->f004 = D_00526498;
        bx->f00C = 0xFF181840;
        func_2905B0(D_00484564, 0x10, 0.5f, 0.5f, 0.5f, -1.0f);
    }
    t = (s16)ob->m303();
    *(S4 *)arr = *(S4 *)D_00480628;
    func_28F8F0(D_00484564, 0x12, arr[t], 0);
    cur = ob->m305();
    rank = ob->m309();
    for (i = 1; i <= 3; i++) {
        v[i - 1] = func_3F9480(ctx->f008->f054->f008, i);
    }
    hi = v[(s16)t];
    if ((s16)t > 0) {
        func_291110(D_00484564, 0x13, 1, 1);
        func_28F930(D_00484564, 0x13, rank * 20, 0);
        func_28FBF0(D_00484564, 0x11, 0x58, 0);
        func_28F850(D_00484564, 0x11, 0x58, 0);
        func_28F8F0(D_00484564, 0x11, arr[t - 1], 0);
    } else {
        D_00484574 = 0;
        func_291110(D_00484564, 0x13, 0, 1);
        func_28FBF0(D_00484564, 0x11, 0, 0);
        func_28F850(D_00484564, 0x11, 0, 0);
    }
    if (cur == 0 || cur == v[0] || cur == v[1] || cur == v[2]) {
        func_28FBF0(D_00484564, 0x12, 0, 0);
        func_28F850(D_00484564, 0x12, 0, 0);
    } else {
        if (t == 0) {
            pos = (s16)(88.0f / (f32)v[0] * (f32)cur);
        } else {
            lo = v[(s16)t - 1];
            pos = (s16)(88.0f / (f32)(hi - lo) * (f32)(cur - lo));
        }
        func_28FBF0(D_00484564, 0x12, pos, 0);
        func_28F850(D_00484564, 0x12, 0x58, 0);
    }
    normal_LeaderHudGaugeLevelPulse_508820();
    normal_LeaderHudGaugeGainFlash_5084c0();
    return 1;
}
