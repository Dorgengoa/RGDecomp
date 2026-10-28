/* rgp:protos */
#define RGP_SELF_normal_TransMenuLayoutBuild_516e20 1
#include "port/game_protos.h"
#line 1
/* === SESSION 96 (2026-09-23): 15 BAD -> MATCH, merged, NORMAL.BIN relinked
 * BYTE-IDENTICAL at 657 units (armed: the s95 source reads DIFFERS).
 * TWO EDITS, both read off a SIMULATOR of mwcc's two scheduler passes
 * (build/wf-normal/s96/sim.py + dag.py + rblk.py; pre-RA replays every traced
 * block, post-RA uses the decompiled R5900 issue model MIPSSimulation.c
 * 0x4bf6a0/0x4bf7f0: mtc1/mov.s/lwc1 need pipe I0, so they cannot pair
 * behind an ALU op).  Replaying RETAIL's order through the post-RA picker
 * (s96/force.py) showed it needs only two list ties -- mov.s before
 * `li a3,1`, and sw 704 before sh 700 -- plus retail's register sequence.
 *   (1) func_2A5920's FLOAT PARAMETERS COME BEFORE THE s8: the call emitter
 *       evaluates arguments in PROTOTYPE order, so the 0.0f (mtc1 $f12) is
 *       created ahead of the `D_004659E8 + 1` narrowing and mov.s ahead of
 *       a2/a3.  EE assigns int and float argument registers independently, so
 *       the retype costs nothing.  Every float slot BEFORE `b` matches; the
 *       merged majority's (void *, s32, f32, f32, s32, s32) is 10 bad here
 *       (s54 measured it length-wrong only because the values were not moved).
 *   (2) D_00484708's store AFTER the bitfield and F01 stores, so the DB0
 *       address is created late and shares $2 with the F01/4659E8 webs.
 * Decks: s96/a720 (720 orders at the s95 prototype: 10 best), s96/c150 (15
 * float-slot prototypes x 4 orders: 32 MATCH). */
/* === SESSION 95 (2026-09-23): STILL 15 BAD, but the cluster's mechanism is
 * now READ, not swept ([[levers.d/mwcc-prera-pressure-scheduler]], trace
 * build/wf-normal/s95/sch/u6e20.sch.txt, block 32 pre-RA / 86 post-RA).
 * PRE-RA the block runs in pressure mode: every zero store (704, 700) scores
 * 16 with NO predecessor, so sw 704 goes first; the normal_D_00525DB0 `la` scores 17
 * and is first-in-list after the EF8 pair, so la + sw 708 go early.  Retail
 * issues every cluster store AFTER the bitfield lbu, which is the signature of
 * MAY-ALIAS edges (load -> store, latency 3).  Alias.c resolves `&D_x` casts to
 * a known object (no edge); an OUT-OF-BOUNDS offset (`(u8 *)&normal_D_00527EF8 + 9`)
 * is unresolved and DOES add edges (704/700 move behind the loads).
 * Decks s95/c1..c5 (45 arms): round trip on the bitfield (24, full address
 * register -- wrong), struct-typed groups (15, other object / LEN), bitfield
 * and F01 via EF8/EE0 offsets (15..25), each gp store via D_00484700+off x F01
 * (16 arms, 19..21).  Many new objects, none under 15.
 * ==> NEXT: cross statement order (s75's 120) with the per-store out-of-bounds
 * spellings, ranked on dist, since the order decides list position among the
 * 17-scorers and the spellings decide which stores wait for the lbu. */
/* === SESSION 93 (2026-09-22): STILL 15 BAD.  s82's NAMED-LOCAL null is
 * RE-PRICED WITH THE NAME ACTUALLY PRESENT, and it is still a null.
 * s82 wrote "mwcc folds a named local that is only COPIED OUT straight back
 * into the store ... a named local is now measured not to be it".  s93's
 * lever says why the name never existed -- a single-def local whose def is
 * copy-propagatable is folded into a compiler temp, and the fix is the
 * POINTER ROUND TRIP, which costs zero instructions
 * ([[levers.d/mwcc-propagated-temp-colouring]]).  Deck s93/g8.py:
 *     const u8 *ad;  ad = normal_D_00525DB0;  ad = (const u8 *)(s32)ad;
 *     D_00484708 = ad;
 *   w_rt        15, BYTE-IDENTICAL to base (efad6e8e)
 *   w_rt_early  15, BYTE-IDENTICAL   (the name created before func_207DF0)
 *   w_nort      15, BYTE-IDENTICAL   (s82's own arm, re-confirmed)
 *   w_rt_ord    16, and EXACTLY EQUAL to w_ord (3d2d5a70), retail's store
 *               order with no name at all
 * ==> the round trip does NOT keep a web whose value is a RELOCATABLE ADDRESS
 * CONSTANT: mwcc rematerialises `lui/addiu %hi/%lo` at the use and there is
 * nothing to colour.  That is a new BOUND on the s93 lever, not just a null
 * here -- compare [[levers.d/mwcc-propagated-temp-colouring]]'s s30 bound.
 * Everything below predates this session. */
/* === SESSION 88 (2026-09-22): STILL 15 BAD.  The DECLARATION-ORDER axis is
 * re-priced at this coat (s88/dsweep.py, 17 arms over the seven locals): TWO
 * objects, 15 and 19, base best.  Armed. */
/* === SESSION 82 (2026-09-21, SOLO): STILL 15 BAD / 315 words.  s75's NAMED
 * NEXT ARM -- "change the normal_D_00525DB0 ADDRESS EXPRESSION's dependence height,
 * not its position" -- is BUILT and NEGATIVE.  Deck build/wf-normal/s82/k1.py.
 * The arm came from this session's close on normal_BtlChgMenuWeaponGridDrawCb_503930, where the
 * last two words fell to exactly that shape: take the value out of the
 * statement, give it its own NAMED WEB, then choose where the web is first
 * assigned.  Here, 11 arms:
 *     ad_p0, ad_p1            BYTE-IDENTICAL to base      (the name FOLDS)
 *     ad_p2..p5, ad_early     16, three distinct objects
 *     ord_retail_ad           16, and == ord_retail_plain EXACTLY
 * THE PROOF THAT THE NAME IS INERT: `ord_retail_ad` (retail's emitted store
 * order, with `const u8 *ad = normal_D_00525DB0; D_00484708 = ad;`) and
 * `ord_retail_plain` (the same order, no name) are the SAME OBJECT 3d2d5a70.
 * mwcc folds a named local that is only COPIED OUT straight back into the
 * store, so the arm is not a new shape at all -- it is the statement-position
 * axis s75 already closed with 120 cells.  Armed (four new objects); the
 * control `const u8 *ad_unused;` is byte-identical.
 * ==> the lever needs the web to have a REAL USE (00503930's `pA[i]`), not a
 * copy-out.  Nothing on this unit reads normal_D_00525DB0; it only stores its
 * address.  The next arm still has to reach the DEPENDENCE, and a named local
 * is now measured not to be it. */
/* === SESSION 75 (2026-09-21, SOLO): STILL 15 BAD / 315 words.  The STORE-GROUP
 * ORDER axis is now a COMPLETE, CURRENT-COAT, ARMED NULL -- 122 arms, every
 * permutation, and it can be struck off for good.
 *
 * WHY IT WAS RE-RUN: the exhaustive sweep this file rests on is the s10 note's
 * "ALL 24 permutations of {bitfield, D_00484708, normal_D_00527F01, D_00484704} with
 * D_00484700 held last ... scores 23 or 24".  That measurement PREDATES s40's
 * `u16 id` close (23 -> 15) and s52's lui-sharing object, i.e. TWO COAT CHANGES
 * ([[levers.d/reprice-retired-units]] -- a "cannot close" verdict is a
 * measurement with a date).  s52 only re-measured ONE cell of it (retail's own
 * emitted order, 16).
 *
 * THE RE-PRICE (build/wf-normal/s75/b1.py, b1.log): ALL 120 permutations of the
 * five stores that follow the normal_D_00527EF8 call-result store, at the current coat.
 *   - 32 cells at 15 bad, 90 at 16, NOTHING under 15, no length change anywhere;
 *   - ELEVEN DISTINCT OBJECTS, so the sweep provably reaches the block and this
 *     is not a "the edit did not fire" null ([[probe-arming-proof]]);
 *   - the installed order (708, BIT, F01, 704, 700) is in the best class.
 * ==> the 15 words are NOT reachable from the order of these six statements.
 * Do not enumerate this block again.
 *
 * Ã¢Ëœâ€¦ WHAT THE RESIDUE IS, read off the object this session (it is cleaner than
 * the s10 note claims -- that note's "we swap the two registers" is STALE):
 * the register assignment is ALREADY RETAIL'S EVERYWHERE.  The bitfield result
 * is in $4 and the normal_D_00525DB0 address in $2 in both.  All 15 words are ONE
 * PERMUTATION of a 15-instruction window, 0x005170A8-0x005170EC, with an
 * IDENTICAL multiset of encodings on both sides.  The six stores come out
 *   retail  EF8, 704, F01, bitfield, 708, 700
 *   ours    EF8, 708, 704, 700, F01, bitfield
 * and the difference that generates it is WHEN the normal_D_00525DB0 address is
 * materialised: retail emits `lui/addiu` at 0x5170CC/D4 and stores at 0x5170DC
 * (LATE, after the bitfield read-modify-write); we emit them at 0x5170A0/A8 and
 * store at 0x5170B0 (EARLY, before it).  Since source order does not move it
 * (120 cells), the next arm has to change the normal_D_00525DB0 ADDRESS EXPRESSION's
 * dependence height, not its position -- s52's `(const u8 *)((u8 *)&normal_D_00527F00
 * - 0x2150)` lui-sharing spelling is the only arm that has ever touched that
 * and it is 15 on a different object (b1cfd4f2), i.e. a genuine second
 * attractor and the natural cross partner for anything found later. */
/* === SESSION 54 (2026-09-12, SOLO): STILL 15 BAD / 315 words.  s52's named
 * next arm -- cross the `normal_D_00525DB0`-as-an-offset spelling with retail's store
 * order -- is MEASURED and NEGATIVE (`J_ord_lui` is 16), and a THIRD half was
 * found and RETIRED.
 * gsig.py reports that MERGED sources declare
 *     func_2A5920(void *p, s32 n, f32 x, f32 y, s32 a, s32 b)
 * twice (normal_ShopMenuInit_50ab50, normal_ThinkMenuInit_5212b0) against our
 *     func_2A5920(void *a, s8 b, s32 c, s32 d, f32 x, f32 y)
 * -- the float and integer argument SLOTS are swapped.  Ã¢Å¡Â Ã¢Å¡Â  THE MERGED
 * MAJORITY IS WRONG FOR THIS CALL SITE: retyping alone is ONE WORD SHORT
 * (0x4e8 vs 0x4ec) and re-ordering the argument VALUES to match is TWO short
 * (0x4e4).  Our declaration is what reaches the exact length; leave it.
 * a_516e20.py, 10 arms: {sig retype} x {call-value swap} x {retail store
 * order} x {lui-sharing spelling}.  Every cell carrying the retype is
 * length-wrong; `I_lui_only` re-confirms s52's 15/b1cfd4f2 and `J_ord_lui` is
 * 16.  The 15 words are a PERMUTATION of one 15-instruction block
 * (0x005170A8-EC): every word retail has, we have, in a different order.
 */
/* === SESSION 52 (2026-09-08, SOLO): still 15 bad / 315 w.  Eight new arms on
 * the axis the s40 header said "any future arm has to reach" -- getting the
 * NEXT statement's call setup to interleave into the store block.  ALL NULL OR
 * WORSE.  Hoisting `func_2A5920`'s arguments into block-scoped locals
 * immediately above the store block (`s32 kk = D_004659E8 + 1;` alone, and
 * crossed with `f32 zz = 0.0f;` for the two float args) is BYTE-IDENTICAL to
 * the baseline (5239c4b2) -- mwcc constant/copy-propagates them back to the
 * call, so the setup's creation point does not move.  Hoisting `D_00484740`
 * instead is a different object at 16.  Retail's own store order is 16 with or
 * without the arg hoists (880eb536), re-confirming s40.
 * ONE NEW LIVE CELL, still 15: spelling `normal_D_00525DB0` as
 * `(const u8 *)((u8 *)&normal_D_00527F00 - 0x2150)` so its address shares the
 * `lui 0x52` the bitfield stores already own gives a NEW object (b1cfd4f2) at
 * the same count -- retail materialises that lui ONCE (opscan: lui 6 retail /
 * 7 ours) and this is the first arm that reaches the sharing at all.  Crossed
 * with retail's store order it is 16.  That cross is where the next arm goes. */
/* SESSION 40 (2026-09-07): 23 -> 15 bad, still exact 315/315 words.  ONE
 * TOKEN: `s32 id` -> `u16 id` in the loop head.  This retires residue 2 below
 * IN FULL (all 8 words) and the header's own "do NOT sweep further spellings,
 * the next lead has to be a mechanism" was right -- the mechanism is:
 *   Retail's guard block is
 *      addiu $3,$16,0x753F / addiu $2,$0,1 / beq $16,$2,join / andi $5,$3,0xFFFF
 *   -- the ADD *and* the u16 NARROWING are both complete before the branch,
 *   and the scheduler drops the narrowing into the delay slot.  With `s32 id`
 *   the narrowing is not part of the assignment at all: it is the CALL's
 *   argument conversion to `u16 id`, which lives INSIDE the arm.  mwcc then
 *   has nothing to sink into the delay slot, so it sinks the ADD instead --
 *   which is why every spelling that moved the *statement* was inert.  It was
 *   never the statement's position, it was the TYPE OF THE LOCAL.
 * `u16 id = (u16)(i + 0x753F)` and a function-scope `u16 id` give the SAME
 * object; a function-scope `s32 id` is byte-identical to the old baseline.
 *
 * REMAINING: 15 words, the single cluster 0x005170A8-0x005170EC, residue 1
 * below, unchanged and still pure schedule.  New measurements this session:
 *  - permscan.py (build/wf-normal/s40) says this unit is a NEAR-PERMUTATION:
 *    masking every relocatable field, only 2 of 315 words are missing from
 *    our multiset and 1 is extra, i.e. nothing is miscompiled anywhere in the
 *    unit -- the whole residue is where the instructions SIT.
 *  - the [[mwcc-float-literal-pool]]-adjacent DATA-DECLARATION axis that
 *    closed normal_LeaderHudWeaponShakeStart_507400 this session was tried here and is a LIVE but
 *    NON-IMPROVING arm: `extern Flags normal_D_00527F00[]` / `extern u8 normal_D_00527F01[]`
 *    indexed `[0]` instead of `extern const u8` written through a
 *    cast-away-const gives a DIFFERENT object at the same 15.  Combining it
 *    with retail's own emitted store order (704, 7F01, bitfield, 708, 700)
 *    reads 16, and that store order without the array form also reads 16.
 *  - retail interleaves the NEXT statement's argument setup (`mov.s $f13,$f12`,
 *    `addiu $7,$0,1`, the D_004659E8 load) INTO the store block; we emit the
 *    stores as a group and the setup after.  That is the shape any future arm
 *    has to reach, and no source order reaches it: the 24-permutation sweep in
 *    the note below is a real negative and still binds. */
/* Ã¢Å¡Â  PARKED at 23 words of 315 (1,260 bytes).  NOT in config/ocunits/normal.txt.
 *
 * 2026-08-25 (session 10): the STORE-GROUP ORDER was enumerated properly for
 * the first time, prompted by normal_HelpMenuStep_522fd0, where the same bitfield
 * store group closed on the cell a three-order sweep cannot reach.  ALL 24
 * permutations of {bitfield, D_00484708, normal_D_00527F01, D_00484704} with
 * D_00484700 held last: build/n_6e20perm.py, SIX distinct object hashes (so
 * the sweep provably reaches the block), scores 23 or 24 and nothing else.
 * The best cell -- D_00484708 FIRST, bitfield SECOND -- is what this file now
 * carries and it is one word better than the recorded park.  A MEASURED
 * NEGATIVE over the whole 24-cell space; the residue below is not statement
 * order.
 * STRUCTURE IS CORRECT: right length, call sequence identical, and every
 * n_ogap gap exact.  Two residues, both allocation/scheduling:
 *
 * 1. (16 words, 0x005170A4-0x005170EC) the gp/overlay store group around the
 *    normal_D_00527F00 bitfield.  Retail puts the bitfield result in $4 and the
 *    normal_D_00525DB0 address in $2 and emits `sh $0, -0xA70` (D_00484700) LAST;
 *    we swap the two registers and hoist that store early.  THREE source
 *    orders measured, all 24 words: bitfield first, bitfield last, and
 *    bitfield first with D_00484708 moved up.  The third does move the
 *    bitfield result into $4 (`sb $4,0x7F00`) and then misses the base
 *    register ($2 vs $3), i.e. it trades one word for another.
 *
 * 2. (8 words, 0x00517228-0x00517260) retail computes `addiu $3,$16,0x753F`
 *    ABOVE the `i != 1` guard, so the guard is a PLAIN `beq` with the `andi`
 *    sunk into its delay slot and the loop's branch-likely slot carries the
 *    id.  mwcc SINKS the computation into the arm (its only user), which
 *    costs the delay slot and made the guard `beql` duplicating the loop
 *    increment -- that was a LENGTH defect too, and hoisting the id into a
 *    named local in the loop head fixed the length but not the position.
 *    Measured and unchanged: id inline in the argument, id as a block-scope
 *    local in the loop head, and the cold-block `goto next;` form.
 *
 * Per the three-attempts rule in overlay-c-pipeline.md, do NOT sweep further
 * spellings; the next lead has to be a mechanism. */
#include "types.h"
/* normal 0x00516E20 -- the gameplay scene's widget bring-up.  1,260 bytes.
 *
 * The five `func_42C500(g, id)` blocks are written OUT, not folded into a
 * helper: retail reloads the gp pointer (`lw -0xA88($28)`) at all five uses
 * inside each block, which a helper taking the pointer by value would not do.
 *
 * `lbu / addiu $4,$0,-2 / and / andi $5,$0,1 / or / sb` on normal_D_00527F00 is a
 * ONE-BIT BITFIELD AT BIT 0 assigned 0 -- the whole insert survives because the
 * assigned value is 0; `= 1` would fold to a plain store.
 * `addiu $7, $28, -0xA70` is the ADDRESS of a gp global, i.e. &D_00484700. */
typedef struct Rec {
    u8    pad00[4];
    void *f04;
    u8    pad08[2];
    __extension__ unsigned short   fA_lo : 2;
    unsigned short   fA_hi : 14;
} __attribute__((aligned(2))) Rec;
typedef struct Obj  { u8 pad00[8]; s32 f08; } Obj;
typedef struct Flags { u8 b0 : 1; u8 rest : 7; } Flags;
typedef struct Sp40 { Obj *f00; s16 f04; s16 f06; s16 f08; s16 f0A; s16 f0C; } Sp40;
typedef struct Ent {
    s16 f00; s16 f02; s16 f04; s16 f06;
    s16 f08; s16 f0A; s16 f0C; s16 f0E;
    f32 f10; s32 f14;
    s16 f18; s16 f1A;
} Ent;

extern u8  normal_D_00527EE0[];
extern s32 normal_D_00527EF8;
extern u8  normal_D_00527F00;
extern u8  normal_D_00527F01;
extern u8  normal_D_00525DB0[];
extern u8  normal_D_005266B0[];
extern u8  normal_D_00525FE0[];
extern s32 D_004659E8;

extern Obj  *D_004846E8;
extern Obj  *D_004846EC;
extern Obj  *D_004846F0;
extern Obj  *D_004846F4;
extern Obj  *D_004846F8;
extern void *D_004846E0;
extern void *D_004846E4;
extern void *D_00484740;
extern s16   D_00484700;
extern s32   D_00484704;
extern u8 *D_00484708;
extern f32   D_0047D288;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  memcpy(void *a, const void *b, s32 c);

void normal_TransMenuLayoutBuild_516e20(void)
{
    void *g;
    Rec *r;
    void *t;
    s32 n;
    Ent *e;
    s32 i;
    Sp40 sp __attribute__((aligned(16)));

    g = GetMenuResGroup_206a40();

    r = ((Rec *)ResGroupListFindById_42c500(g, 0x20));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(D_004846E8);
    UiInitWidgetPool_290390(D_004846E8, D_004846E0, n);
    UiAddWidgets_2901d0(D_004846E8, t, 0);
    D_004846E8->f08 = 0x32D;
    UiTextStyleReset_290450();

    sp.f00 = D_004846E8;
    sp.f04 = 0x7602;
    sp.f06 = 0x7600;
    sp.f08 = 0x7603;
    sp.f0A = 0x75FA;
    sp.f0C = 0x75FF;
    MenuPanelGridAlloc_28b660(D_004846E0, &sp);

    r = ((Rec *)ResGroupListFindById_42c500(g, 0x1E));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(D_004846EC);
    UiInitWidgetPool_290390(D_004846EC, D_004846E0, n);
    UiAddWidgets_2901d0(D_004846EC, t, 0);
    D_004846EC->f08 = 0x32D;
    UiTextStyleReset_290450();

    r = ((Rec *)ResGroupListFindById_42c500(g, 0x1F));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(D_004846F0);
    UiInitWidgetPool_290390(D_004846F0, D_004846E0, n);
    UiAddWidgets_2901d0(D_004846F0, t, 0);
    D_004846F0->f08 = 0x32D;
    UiTextStyleReset_290450();

    r = ((Rec *)ResGroupListFindById_42c500(g, 0x21));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(D_004846F4);
    UiInitWidgetPool_290390(D_004846F4, D_004846E0, n);
    UiAddWidgets_2901d0(D_004846F4, t, 0);
    D_004846F4->f08 = 0x32D;
    UiTextStyleReset_290450();

    r = ((Rec *)ResGroupListFindById_42c500(g, 0x22));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(D_004846F8);
    UiInitWidgetPool_290390(D_004846F8, D_004846E0, n);
    UiAddWidgets_2901d0(D_004846F8, t, 0);
    D_004846F8->f08 = 0x32D;
    UiTextStyleReset_290450();

    t = ResGroupListFindObjById_42c010(g, 0x14);
    UiEntryListReset_28ec80(normal_D_00527EE0);
    UiEntryListAlloc_28e0c0(normal_D_00527EE0, D_004846E0, 0x60);
    UiEntryListLoad_28eb70(normal_D_00527EE0, t, D_004846E8);
    *(void **)&normal_D_00527EF8 = SceneSoundGetSlot0HandleCur_207df0();
    ((Flags *)&normal_D_00527F00)->b0 = 0;
    *(u8 *)&normal_D_00527F01 = 0;
    D_00484708 = normal_D_00525DB0;
    D_00484704 = 0;
    D_00484700 = 0;
    MenuItemGridInitMaybe_2a5920(D_00484740, D_004659E8 + 1, 0, 1);
    MenuSetPanelHandles_2a5900(D_00484740, D_004846E8, normal_D_00527EE0, &D_00484700, D_004846E4);

    UiSetWidgetsVisibleById_291110(D_004846EC, 0x84D1, 0, 1);
    UiSetWidgetAlpha_2907a0(D_004846EC, 0x84D1, 0.0f);
    UiSetWidgetsVisibleById_291110(D_004846E8, 0x7531, 0, 1);
    UiSetWidgetAlpha_2907a0(D_004846E8, 0x7531, 0.0f);
    UiSetWidgetsVisibleById_291110(D_004846E8, 0x7532, 0, 1);
    UiSetWidgetAlpha_2907a0(D_004846E8, 0x7532, 0.0f);
    UiSetWidgetsVisibleById_291110(D_004846E8, 0x7533, 0, 1);
    UiSetWidgetAlpha_2907a0(D_004846E8, 0x7533, 0.0f);
    UiSetWidgetsVisibleById_291110(D_004846E8, 0x7534, 0, 1);
    UiSetWidgetAlpha_2907a0(D_004846E8, 0x7534, 0.0f);
    UiSetWidgetsVisibleById_291110(D_004846E8, 0x75DC, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004846E8, 0x75DB, 0, 1);
    normal_TransMenuWidgetListShow_514a10(0);
    UiSetWidgetListVisible_28c120(D_004846E8, normal_D_005266B0, 0);

    if (IsTgsDemoBuild_207f20() != 0) {
        for (i = 0; i < 4; i++) {
            u16 id = i + 0x753F;
            if (i != 1) {
                UiSetWidgetColor_2905b0(D_004846E8, id, D_0047D288, D_0047D288,
                            D_0047D288, 1.0f);
            }
        }
    }
    e = ((Ent *)UiGetWidgetSprite_28fe10(D_004846E8, 0x7541, 0));
    if (e != 0) {
        if (((unsigned char)normal_TransMenuIsHunterUnlocked_5185e0()) != 0) {
            memcpy(e, normal_D_00525FE0, 0x20);
        } else {
            e->f00 = 0x1E;
            e->f02 = 5;
            e->f08 = 0xAC;
            e->f0A = 0x22;
            e->f0C = 0x14;
            e->f04 = 0x14;
            e->f0E = 0x14;
            e->f06 = 0x14;
            e->f10 = 3.0f;
            e->f14 = 0;
            e->f18 = 0x14;
            e->f1A = -1;
        }
    }
}
