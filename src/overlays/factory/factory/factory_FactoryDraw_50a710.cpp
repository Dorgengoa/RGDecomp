#pragma divbyzerocheck on
#include "types.h"

/* ** SESSION 51 (2026-09-03), tag fg51: 6 BAD -> BYTE-IDENTICAL, 849 words,
 * object md5 4fb994aba890.  Armed in every batch with the cmp-verified
 * identity (f28909d0088c / 6), 005069e0 = MATCH / 1a0e9c68216b and
 * 00500450 = 2 / 409c28db0188, and the recorded-live delivery cell
 * `#pragma opt_common_subs off` (893 w / 2bad72aac5e3) reproduced in all three
 * runs.  s50's whole map table (N1/D1/N2/B1) was re-derived exactly first.
 *
 * ★★★★★★★ THE CLOSE IS ONE EDIT: each half of the sp100 copy goes through a
 * one-member WRAPPER STRUCT round the pair, not through the pair type itself.
 *
 *     typedef struct F2 { f32 a, b; } F2;
 *     typedef struct W2 { F2 p; } W2;            <- the wrapper
 *     *(W2 *)&sp100[0] = *(W2 *)&D_00480E20;
 *     *(W2 *)&sp100[2] = *(W2 *)&D_00480E28;
 *
 * WHY IT IS A DIFFERENT OBJECT FROM `*(F2 *)&sp100[0] = ...`, which is what
 * s43/s50 measured: a TOP-LEVEL 8-byte aggregate assignment is emitted
 * MEMBER-WISE, `L S L S`; a NESTED aggregate member is emitted as a BLOCK,
 * `L L S S`.  Wrapping the pair in a struct demotes it to a member and buys
 * the block form.  Retail's window is two overlapped block pairs:
 *
 *     retail            L0 L1 S0 L2 S1 L3 S2 S3   rot f0 f2 f1 f0
 *     W2 + W2  (M3)     the same -- MATCH
 *     F2 + W2  (M4)     2 bad: `sll v0,a0,1` and L1 transposed at 163/164
 *     W2 + F2  (M2)  =  W2 + two scalars (M1) = F2+F2 = elementwise:
 *                       L0 S0 L1 L2 L3 S1 S2 S3   f0 f2 f1 f0    9
 *     F3 + scalar (the s43 tree)
 *                       L0 L1 S0 S1 L2 L3 S2 S3   f2 f1 f1 f0    6
 *     struct P2 { F2 p; F2 q; } (one statement)
 *                       L0 L1 S0 S1 L2 L3 S2 S3   f1 f0 f1 f0    6
 *     F4 flat 4-copy    L0 L1 S0 S1 L2 S2 L3 S3   f1 f0 f0 f0    8
 * The SECOND pair's wrapper carries the lever (9 -> 2); the FIRST pair's
 * wrapper is worth nothing on its own (M1 = M2 = the elementwise object) and
 * closes the last two words only once the second one is there.  ⚠ THE BAD
 * COUNT AND THE MAP DISAGREED THE WHOLE WAY: the 6-bad tree has the WRONG FPR
 * rotation and the 9-bad elementwise family has RETAIL'S -- the ladder to the
 * match runs 9 -> 2 -> 0 THROUGH the worse-scoring arm.
 *
 * WHAT ALSO HAD TO BE TRUE (re-derived off the objects this session, and it is
 * why every "chain after the copy" arm was structurally excluded before it was
 * scored): retail keeps the chain's memory input `lw v1,684(s4)` at idx 162,
 * ABOVE L0, with the product `sll/addu/sll/addu` issuing one op per slot
 * INSIDE the window and `addiu v0,zero,16` (the `f2C8 == 0x10` constant) at
 * 172.  That happens only when `temp_22 = (Row *)(arg0->f2AC + temp_4 * 0xC);`
 * stays BEFORE the copy AND no new named local is introduced for the base:
 * moving the chain after sinks the `lw` below the window, and any extra local
 * (s50's `base_2AC`, or re-using temp_22 as its own base) flips temp_4 from a0
 * to v1 and shows up as `bltzl v1` at 160.
 *
 * MEASURED DEAD THIS SESSION, DO NOT RE-RUN (12 arms, batch 1):
 *   - a typed `Row *f2AC` field with `&arg0->f2AC[temp_4]` is BYTE-IDENTICAL
 *     to the untyped chain at BOTH positions (before = the 9 object, after =
 *     the 14 object) -- it does NOT keep the load above the window;
 *   - the cons read folded into the chain statement
 *     (`temp_4_2 = (temp_22 = ...)->r06;`) hoists the `lh` INTO the window: 14;
 *   - the compare constant through a named `s32 k16 = 0x10` local: INERT;
 *   - 0050a180's transplant (volatile sp100 + whole 4-copy + chain before)
 *     gives the flat-F4 window, not a180's, and costs 6 more words at the
 *     case-0x10 stores: 14;
 *   - re-using temp_22 as its own base (no new local) is still e8b133a0c4bd/12,
 *     i.e. identical to s50's `base_2AC` -- the a0<->v1 flip is not about the
 *     NAME, it is about the extra assignment.
 * And the nesting sweep itself (batch 2): `{f32 a,b; F2 q;}` = the P2 object 6;
 * `{F2 p; f32 c,d;}` = flat F4 8; `{f32 a; F2 m; f32 d;}` 10; `{F3 t; f32 d;}`
 * 11; `{f32 a; F3 t;}` = elementwise 9; `struct W4 { F4 v; }` 10;
 * `struct W3 { F3 t; }` + scalar 11; W2+W2 with the chain AFTER 14.
 * See [[factory-session51-levers]], [[mwcc-float-table-struct-copy]].
 */


/* ** SESSION 50 (2026-09-03), tags fg50/fg50b: STILL 6 BAD / f28909d0088c, tree
 * UNCHANGED.  47 arms in 5 batches (build/fg50/logs/s50_a710_b{1..5}.log), every
 * batch with the cmp-verified identity, 005069e0 MATCH, 00500450 = 2 /
 * 409c28db0188 as the second arming unit (00509f10 was under sweep and CLOSED
 * this session), and the recorded-live deliveries `#pragma opt_common_subs off`
 * (893 w) / the s43 4-copy (36c45ddf14f8 / 8) reproduced.
 *
 * THE CLASS WAS CRACKED ON 00509f10, NOT HERE.  build/fg50/s50/winscreen.py
 * over all 2,284 retail listings: retail's two-in-flight window
 * `L0 L1 S0 L2 S1 L3 S2 S3` with foreign instructions inside exists in exactly
 * THREE places -- 00509f10, this sp100 site, and MERGED factory_FactoryRectFrameEdge_50a180
 * (its `ty = row * 0x18` chain sits inside the window, from source that writes
 * the product NEXT TO the copy).  00509f10 closed on a 2+2 SPLIT of the copy
 * plus the product statement written IMMEDIATELY AFTER the copy.
 *
 * ON THIS SITE THE TRANSFER IS HALF-LIVE (maps read with winread.py, anchors =
 * the four lwc1 defs; 'rot' = the FPR each load takes):
 *     tree 3+1                     L0 L1 S0 S1 L2 L3 S2 S3   f2 f1 f1 f0    6
 *     2+2 = elementwise (b8939d51767c)  L0 S0 L1 L2 L3 S1 S2 S3   f0 f2 f1 f0    9
 *     chain AFTER the copy (2+2 = elem = 1+1+2 = 2+1+1 = 1+2+1, ONE object
 *       7bd7d0fb0ba6)              L0 L1 S0 L2 L3 S1 S2 S3   f0 f2 f1 f0   14
 *       -- the chain interleaves as retail's does, BUT the f2AC base `lw`
 *       (part of the same statement) sinks BELOW the window (retail: idx 162,
 *       above L0) and temp_4/base swap a0 <-> v1;
 *     `base_2AC = arg0->f2AC` BEFORE the copy, chain after (2+2 = 3+1 = elem,
 *       ONE object e8b133a0c4bd)   L0 L1 S0 S1 L2 L3 S2 S3   f1 f0 f1 f0   12
 *       -- the base load is back at 162 but the a0 <-> v1 swap stays, and the
 *       declaration slot of base_2AC (before/after temp_4, first of all, first
 *       scalar) is INERT (5 cells, one object);
 *     4-copy with the chain after 17 / with the base local 14; 1+3 17; 2+2
 *       reversed 18; scalar element first 13 / 18; chain BETWEEN the pairs 14.
 *     volatile on sp100 is NOT inert here (the case-0x10 `sp100[k].i` stores
 *       share the array): 2+2/elem/1+1+2/2+1+1/1+2+1 all c8c01cc6f238 / 15,
 *       3+1 12 (= s44), 1+3 18; `*(volatile F2 *)` casts do not compile as C++.
 * Reading: the bad count and the map DISAGREE -- the 6-bad tree has the wrong
 * rotation, the 9/14/12 arms have retail's.  What retail has that no arm
 * reaches is the f2AC load ABOVE the window from a statement whose product
 * chain issues INSIDE it, with temp_4 kept in a0.  Next: an arm that keeps
 * `arg0->f2AC` in the SAME statement as the chain (so the load hoists) while
 * the statement follows the copy -- e.g. a `Row *` typed field with the chain
 * as an array subscript, or the CONS reads folded into the chain statement.
 * See [[factory-session50-levers]].
 */

/* ** SESSION 43 (2026-09-02), tag fg43: 69 -> 6 BAD, EXACT LENGTH (849 w),
 * object md5 f28909d0088c, armed in EVERY run (005069e0 = MATCH / 1a0e9c68216b,
 * 00509f10 = bad 11 / 977182cbe9b7).  resid2.py: struct 8 -> 6, regonly
 * 64 -> 2.  STILL OPEN -- NOT in config/ocunits/factory.txt, so it does not
 * link and the board is untouched at 399/409.
 * Ladder, every rung with a cmp-verified identity arm AND a delivery control
 * (`#pragma opt_common_subs off` = 893 w) in the SAME run:
 *     95 (s40) -> 69 (s42) -> 52 -> 14 -> 8 -> 6 (s43)
 *
 * ★★★★★★★ 4. THE 64 REGISTER-ONLY CELLS WERE A 3-CYCLE, AND s42's "THE GPR
 * DECLARATION AXIS IS DEAD" WAS MEASURED ON THE WRONG SEVEN DECLARATIONS.
 * cells2.py names the three webs off the object:
 *     web                                     m2c name(s)        retail  ours
 *     func_141B00 result + 12 call arguments  temp_2_7 (line 536)  $18    $17
 *     the switch state + the sp158 counter    var_16_2, var_16_3   $16    $18
 *     the Ent* / Part* chain + its counter      var_17, var_17_2/_3  $17    $16
 * s42 swept all 21 pairwise swaps of temp_16/17/18/19, var_21, temp_22/23 --
 * NOT ONE of the six variables the residue names.  Applying
 * [[mwcc-fpr-decl-order-highest-first]]'s GROUP rule to the integer side, with
 * each group made CONTIGUOUS and the groups ordered DESCENDING by retail's
 * register ($18, $17, $16):
 *     temp_2_7 | var_17_2 var_17_3 var_17 | var_16_3 var_16_2   ->   14
 * and the two halves are separable and each is real on its own:
 *     var_17_* before var_16_*  (3-cycle -> PAIR)        69 -> 52
 *     temp_2_7 before var_17_*  (the PAIR settles)       52 -> 14
 * The single pairwise swap temp_2_7 <-> var_17_2 reaches the SAME object as
 * the full group move (both 14 / e957b0e1b307), which is 004f2d50's recorded
 * "a PAIR has exactly one swap, so declaration order settles it" -- and its
 * warning that declaration order alone is a no-op ON A 3-CYCLE is exactly why
 * s42's sweep read dead.  Turn the cycle into a pair FIRST.
 * ⚠ temp_2_4 (line 450) is a DIFFERENT web from temp_2_7 -- there are two
 *   func_141B00 blocks in two switch arms; temp_2_4 is $17 in BOTH builds and
 *   its position is INERT (one object over three group orders).
 * ⚠ temp_18 is NOT the handle: every move of it is worse (62/69/79/86), and
 *   grouping it with temp_2_7 is a regression (69 vs 52).
 *
 * ★★★★★★ 5. THE `lui` PAIR RULE (edit 2 above) FIRES A SECOND TIME, at a
 * DIFFERENT site: the case-11 spD0 block, 0x0050AE4C-0x0050AE60, was a pure
 * v0<->v1 swap.  Writing the three 0x43580000 stores BEFORE the 0x43000000
 * store is 14 -> 8 and closes the region.  Every order leaving spD0[3] first
 * is 14; (1,2,0,3) and (2,0,1,3) are 11; (0,1,2,3) and (0,3,1,2) are one
 * object at 8.  ⚠ NAMING the constants in a chosen order is byte-identical to
 * the baseline (2 cells) -- only the STORE order gives a constant its birth.
 *
 * ★★★★★ 6. THE STRUCT COPY WANTS A 3+1 SPLIT HERE, NOT A 4-COPY.
 *     *(F3 *)&sp100[0] = *(F3 *)&D_00480E20;
 *     sp100[3].f = D_00480E2C;
 * is 8 -> 6.  [[mwcc-float-table-struct-copy]] has never swept the SPLIT of
 * the aggregate; its 42 nulls are all whole-copy spellings.  Measured here:
 * 4-copy 8, 3+1 6, 1+3 18->13, 2+2 12, 1+2+1 / 2+1+1 / 1+1+2 all one object
 * at 9, elementwise 9, load-all-then-store-all breaks the length (+8 w).
 *
 * WHAT IS LEFT AT 6 -- 0x0050A99C..0x0050A9BC, a caller-saved FPR interleave.
 * The instruction MULTISET is identical; only the order and two registers are:
 *     retail  L0 $f0  L1 $f2  S0 $f0  L2 $f1  S1 $f2   (two loads in flight)
 *     ours    L0 $f2  L1 $f1  S0 $f2  S1 $f1  L2 $f1
 * Retail's $f0,$f2,$f1,$f0 is exactly the sequence
 * [[mwcc-float-table-struct-copy]] documents for a correct 4-element table.
 * THREE AXES MEASURED DEAD AT THIS BASELINE, do not re-run:
 *   - statement POSITION of the copy relative to the temp_22 address
 *     arithmetic and its three consumers: 12 orders, every one 8..18;
 *   - the caller-saved float declaration groups temp_f0* /
 *     temp_f1* / temp_f2* / temp_f3: 12 group orders, ALL BYTE-IDENTICAL to the baseline, with the
 *     893-word delivery control live in the same run.  This RE-DERIVES s42's
 *     inherited null at a baseline where this region is the ONLY residue, and
 *     confirms that file's "a single-use name is forwarded before allocation";
 *   - the element ORDER inside the copy: 7 elementwise permutations plus two
 *     singleton spellings, nine distinct objects, all 10..16.
 */

/* ** SESSION 42 (2026-09-02), tag fg42: 95 -> 69 BAD, EXACT LENGTH (849 w),
 * object md5 97281281c8d1, armed in every run (005069e0 = MATCH / 1a0e9c68216b,
 * 00509f10 = bad 11 / 977182cbe9b7).  resid2.py: struct 20 -> 8, regonly
 * 76 -> 64.  STILL OPEN.  The PRE42 control reproduced s40's recorded
 * 5da812dc0ed7 / 95 in the same run, and `#pragma opt_common_subs off`
 * reproduced s40's recorded 893 w as the delivery control.
 *
 * THREE EDITS, ALL FROM MECHANISMS A MERGED SIBLING ALREADY RECORDS:
 *
 * 1. [[mwcc-float-table-struct-copy]] -- sp100's four CONSECUTIVE gp f32
 *    externs are ONE STRUCT COPY THROUGH A CAST, not four element stores:
 *        *(F4 *)sp100 = *(F4 *)&D_00480E20;
 *    95 -> 94 alone.  ⚠ THE SCOPE CONDITION IS REAL: the same cast applied to
 *    ALL FIVE sites (sp110/spF0/spE0/spD0) is 123 bad -- those four schedule
 *    correctly elementwise and the cast BREAKS them.  Cast only the site whose
 *    load/store interleave is actually wrong.
 *
 * 2. The region at 0x0050A9E8-0x0050A9F4 was the two `lui` constants
 *    materialised in SOURCE order.  Retail materialises 0x42000000 before
 *    0x43000000, so write sp100[1]/[2] (0x42000000) BEFORE sp100[3]
 *    (0x43000000).  95 -> 89 alone; with edit 1, 88.  That region is CLOSED.
 *
 * 3. ★★★★★★ [[mwcc-fpr-decl-order-highest-first]], and the lattice is COMPLETE.
 *    m2c names each float local after RETAIL's register, so the declaration
 *    GROUPS are already labelled with their target: order them DESCENDING.
 *    Relative order of the temp_f20* / temp_f21* / temp_f22* groups, all six
 *    permutations measured on top of edits 1+2:
 *        f22,f21,f20  ->  69   <- retail, and it is the strict reversal
 *        f22,f20,f21  ->  76
 *        f20,f22,f21  ->  77
 *        f20,f21,f22  ->  88   (the pre-session order)
 *        f21,f22,f20  ->  89
 *        f21,f20,f22  ->  91
 *    Moving the WHOLE GROUP beats moving one declaration (77 vs 81 for
 *    temp_f22 alone).  The temp_f0* / temp_f1* / temp_f2* groups' positions are
 *    INERT (3 cells, one object).  This closed BOTH FPR regions (7-10).
 *
 * WHAT IS LEFT (69 bad): ONE structural region, 0x0050A9A0-0x0050A9C8, and it
 * is a SOFTWARE-PIPELINE mismatch, not a shape error.  Retail issues
 *     L0 L1 S0 L2 S1 L3 S2 S3      (two loads in flight throughout)
 * and the struct copy gets us to
 *     L0 L1 S0 S1 L2 S2 L3 S3      (two in flight, then one)
 * so ours reuses $f0 where retail rotates $f0/$f2/$f1/$f0.  Note
 * [[mwcc-volatile-access-site-pin]] is REFUTED against a pipelined window --
 * do not spend a pin here.  Plus 64 register-only cells, 34 of them `daddu`.
 *
 * ⚠ MEASURED NULL, 28 cells, DO NOT RE-RUN: the GPR declaration axis at this
 * baseline.  All 21 PAIRWISE SWAPS of the callee-saved integer declarations
 * (temp_16/17/18/19, var_21, temp_22/23) are inert except temp_17<->temp_18
 * (79), temp_18<->temp_19 (77), temp_19<->var_21 (86) and temp_19<->temp_22
 * (100) -- every live cell is WORSE.  A true identity arm reproduced 69 in the
 * same run.  And GROUPING the integer locals by register (the move that pays
 * on the floats) is a LARGE REGRESSION -- 129/131 bad, best group order 108.
 * The interleaved integer declaration order is load-bearing; the float rule
 * does NOT transfer to the GPRs on this unit.
 */

/* ** SESSION 40 (2026-09-02), tag fg40: 548 -> 95 BAD, EXACT LENGTH (849 w),
 * and the `jtbl fallback ... refusing to guess` note is GONE -- the compiled
 * jump table now occurs in retail's image.  Object md5 5da812dc0ed7, armed
 * (005069e0 = MATCH, 00509f10 = bad 11 / md5 977182cbe9b7 in the same run).
 * Register-blind decomposition (build/fg40/resid2.py): struct 98 -> 20,
 * regonly 99 -> 76.  NOT byte-identical, so this unit is still OPEN.
 *
 * THE ONE EDIT: the factory_FactoryRectFrameDraw_50a4c0 prototype declares its two trailing
 * INTEGER parameters AFTER all six FLOAT parameters, and the eight call sites
 * are permuted to match.  This is REGISTER-NEUTRAL -- integer arguments fill
 * a0-a3,t0 and float arguments fill $f12-$f17 from two INDEPENDENT counters --
 * so it changes ONLY the order mwcc emits the argument-setup moves, which is
 * exactly the defect that dominated this draft.  Closed the sibling
 * factory_FactoryRectFrameDraw_50a4c0 outright the same session.  [[factory-session40-levers]]
 *
 * THE LATTICE IS SHARP AND WAS SWEPT (13 register-neutral interleavings, one
 * armed run, build/fg40/mk_a710k.py -- k_i = how many floats precede the i-th
 * int): it collapses to exactly TWO objects.  BOTH trailing ints (a3 and t0)
 * after all six floats => 95 / exact length; any other placement => 848 words
 * (-1, a hazard nop retail keeps and we fill) or the old baseline.  k1..k3 are
 * entirely INERT.
 *
 * WHAT IS LEFT (build/fg40/blocks.py): only SIX real structural rows, all in
 * 0x0050A9A4-0x0050A9F4 -- the `lwc1 $f2,-17228(gp)` load sits 4 slots late,
 * and `sw v0,256(sp)` / `daddu s0,s5` / `lui 0x4300` are transposed.  Regions
 * 7-10 and the 76 remaining cells are FPR/GPR ALLOCATION ($f22 vs $f21, and 34
 * daddu), not shape.  MEASURED NULL this session: `const` on the gp float
 * externs ([[factory-gp-load-placement]], s23's 005013f0 cell) -- +12 w on the
 * D_0047D* group, +20 on D_00480E*, +32 on both; it is the WRONG direction
 * here.  Also null: inlining `temp_sh` at the first call site (3 arms, all
 * byte-identical -- mwcc forwards a 1-def/1-use local), and both polarities of
 * all 46 codegen pragmas (92 arms, build/fg40/knob.py: 85 inert, 7 live and
 * ALL of them strictly worse -- schedule off 971 w, opt_repositioncode on 868,
 * peephole off 926, opt_common_subs off 893, floatsp32 off 801).
 */


#ifndef NULL
#define NULL 0
#endif

extern f32 D_0047D278;
extern f32 D_0047D288;
extern f32 D_0047D7C4;
extern f32 D_0047D7E0;
extern f32 D_0047D85C;
extern f32 D_00480E10;
extern f32 D_00480E14;
extern f32 D_00480E18;
extern f32 D_00480E1C;
extern f32 D_00480E20;
extern f32 D_00480E24;
extern f32 D_00480E28;
extern f32 D_00480E2C;
extern f32 D_00480E30;
extern f32 D_00480E34;
extern f32 D_00480E38;
extern f32 D_00480E3C;
extern f32 D_00480E40;
extern f32 D_00480E44;
extern f32 D_00480E48;
extern f32 D_00480E4C;
extern f32 D_00480E50;
extern f32 D_00480E54;
extern f32 D_00480E58;
extern f32 D_00480E5C;

/* mwcc's C++ front end PARSES AND DROPS __attribute__((aligned(16))); the one
   spelling that reaches lq/sq from C++ is the GNU MODE attribute (measured on
   the sibling unit factory_FactoryCameraUpdate_5050c0). */
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct VF { f32 x; f32 y; f32 z; f32 w; } VF;
typedef union  V4 { u128 q; VF v; } V4;
typedef struct F4 { f32 a, b, c, d; } F4;
typedef struct F3 { f32 a, b, c; } F3;
typedef struct F2 { f32 a, b; } F2;
typedef struct W2 { F2 p; } W2;
typedef struct Q16 { u32 w[4]; } Q16;

/* the 6-byte map cell -- f04 is u16, tested only with & 0x8000
   (same shape as the closed unit factory_FactoryGridRectIsFree_502d90). */
typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;

/* the entity handed back by factory_FactoryGridPartGroupAt_502b20 / _00504080.
   its 0x4 field is compared == 0xD with a SIGNED lh. */
typedef struct Ent {
    u8  pad00[0x4];
    s16 e04;
} Ent;

/* the 0xC-byte row record at f2AC: field 0 is a POINTER (lw). */
typedef struct Row {
    Cell *r00;
    u8    pad04[0x2];
    s16   r06;
    s16   r08;
} Row;

/* the 0x40-byte sub-object at arg0 + 0xE0, four of them. */
typedef struct Part {
    u8  pad00[0x4];
    s16 p04;
    u8  pad06[0x2];
    s16 p08;
    u8  pad0A[0x8];
    s16 p12;
    u8  pad14[0xC];
    f32 p20;
    f32 p24;
    f32 p28;
    u8  pad2C[0x4];
    s16 p30;
    u8  pad32[0x2];
    s16 p34;
    u8  pad36[0xA];
} Part;

/* the out-parameter handed to factory_FactoryMarkerUpdate_4ea160.  ONE aggregate: as five
   scalars only the first is address-taken and mwcc DEAD-STORE-ELIMINATES the
   other four (levers.d/m2c-address-taken-aggregate). */
typedef struct Anim {
    f32 a00;
    f32 a04;
    f32 a08;
    s32 a0C;
    s16 a10;
    u8  pad12[0xE];
} Anim;

/* `lw $25,0x1B0($4)` / `lw $25,0x24($25)` / `jalr $25` is a C++ VIRTUAL CALL.
   vptr offset K=0x1B0 => 0x1B0 bytes of data members before the first virtual.
   slot 0x24 = 8 + 4*7 => m24 is the 7th (0-based) declared virtual. */
class Obj {
public:
    u8   pad000[0x180];
    V4   o180;
    u8   pad190[0x20];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void m24();
};

/* `lw $25,0xC0($2)` / `lw $25,0xA8($25)` => K=0xC0, slot 0xA8 = 8+4*40. */
class Cam {
public:
    u8   pad00[0xC0];
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    virtual void c4();
    virtual void c5();
    virtual void c6();
    virtual void c7();
    virtual void c8();
    virtual void c9();
    virtual void c10();
    virtual void c11();
    virtual void c12();
    virtual void c13();
    virtual void c14();
    virtual void c15();
    virtual void c16();
    virtual void c17();
    virtual void c18();
    virtual void c19();
    virtual void c20();
    virtual void c21();
    virtual void c22();
    virtual void c23();
    virtual void c24();
    virtual void c25();
    virtual void c26();
    virtual void c27();
    virtual void c28();
    virtual void c29();
    virtual void c30();
    virtual void c31();
    virtual void c32();
    virtual void c33();
    virtual void c34();
    virtual void c35();
    virtual void c36();
    virtual void c37();
    virtual void c38();
    virtual void mA4(Q16 *o);
    virtual void mA8(Q16 *o);
};
typedef struct Root { u8 pad0000[0x4344]; s32 r4344; } Root;

typedef struct S S;
struct S {
    u8   pad000[0x58];
    Obj *f58;
    u8   pad05C[0x8];
    s32  f64;
    u8   pad068[0x238];
    s32  f2A0;
    s16  f2A4;
    s16  f2A6;
    u8   pad2A8[0x4];
    s32  f2AC;
    u8   pad2B0[0x18];
    s32  f2C8;
    u8   pad2CC[0x4];
    s32  f2D0;
    u8   pad2D4[0x10];
    s16  f2E4;
    u8   pad2E6[0x2];
    s16  f2E8;
    u8   pad2EA[0x4];
    s16  f2EE;
    s16  f2F0;
    u8   pad2F2[0x8];
    s16  f2FA;
    s16  f2FC;
    u8   pad2FE[0x2];
    s16  f300;
    u8   pad302[0x5E];
    f32  f360;
    u8   pad364[0x4];
    f32  f368;
    u8   pad36C[0x14];
    f32  f380;
    u8   pad384[0x4];
    f32  f388;
};

/* MAIN-image float at %hi/%lo, NOT small data.  The INCOMPLETE
   ARRAY is the match form -- levers.d/factory-gp-load-placement. */
extern f32 D_0045B080[];
/* likewise: declared as a scalar it lands in small data and retail's
   `lui %hi / addiu %lo` pair collapses to one gp-relative addiu. */
extern u8 D_0050D7A8[];

extern "C" {
s32   factory_FactoryMarkerUpdate_4ea160(void *, s16, s64, s32);
s32   factory_FactoryPartFootprintRect_502760(void *, s16 *, void *, s32, f32, f32);
s32   factory_FactoryPartHitTestCell_502970(void *, s32, s32, void *, s16 *, s32);
Ent  *factory_FactoryGridPartGroupAt_502b20(void *, s32, s32);
f32   factory_FactoryGridCellCenterZ_503730(void *, s32);
f32   factory_FactoryGridCellCenterX_503760(void *, s32);
f32   factory_FactoryFineGridCellCenterZ_503790(void *, s32);
f32   factory_FactoryFineGridCellCenterX_5037c0(void *, s32);
Cell *factory_FactoryGridCellAt_5037f0(void *, s32, s32);
Cell *factory_FactoryFineGridCellAt_503880(void *, s32, s32);
s32   factory_FactoryGridRowFromZ_503f00(void *, f32);
s32   factory_FactoryGridColFromX_503f60(void *, f32);
s32   factory_FactoryFineGridRowFromZ_503fc0(void *, f32);
s32   factory_FactoryFineGridColFromX_504020(void *, f32);
Ent  *factory_FactoryPartGroupFindById_504080(void *, s32);
s32   factory_FactoryRectFrameDraw_50a4c0(void *, s32, s32, f32, f32, f32, f32, f32, f32, s32, void *);
s32   func_13E2F0(s32, s32);
s32   func_13E3E0(s32, s32);
s32   func_13E400(s32, s32);
s32   func_13E430(s32, s32);
s32   func_13E460(s32, s32);
s32   func_13E4D0(s32, s32);
s32   func_13E4F0(s32, s32);
s32   func_13E500(s32, s32);
s32   func_13EE40(s32, s32, s32, s32, s32);
s32   func_13F060(s32, f32, f32, f32);
s32   func_13F5B0(s32);
s32   func_13F730(s32, s32);
s32   func_1418C0(s32, s32, f32);
s32   func_141A20(s32);
s32   func_141B00(s32);
s32   func_151110(void *, void *);
s32   func_159FB0(s32, void *, s32);
s32   func_15DE40();
s32   func_15DE80();
Cam  *func_1C3BC0(void *, s32);
s32   func_1CBD00(void *, void *, void *);
Root *func_1F5BE0();
}

extern "C" void factory_FactoryDraw_50a710( struct S *arg0){
    s16 sp158[4];
    Q16 sp140;
    Q16 sp130;
    Q16 sp120;
    union { f32 f; s32 i; } sp110[4];
    union { f32 f; s32 i; } sp100[4];
    union { f32 f; s32 i; } spF0[4];
    union { f32 f; s32 i; } spE0[4];
    union { f32 f; s32 i; } spD0[4];
    Anim spB0;
    V4   spA0;
    Cam  *temp_2_2;
    s32 temp_16;
    s32 temp_2_3;
    Obj  *temp_18;
    s32 temp_17_4;
    s32 temp_19;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f22_3;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f21_3;
    f32 temp_f21_4;
    f32 temp_f21_5;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f20_4;
    f32 temp_f20_5;
    f32 temp_f20_6;
    f32 temp_f20_7;
    f32 temp_f20_8;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f3;
    s32 temp_sh;
    s32 temp_16_2;
    s32 temp_16_3;
    s32 temp_16_4;
    s32 temp_16_5;
    s32 temp_16_6;
    s32 temp_16_7;
    s32 temp_17;
    s32 temp_17_2;
    s32 temp_17_3;
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_4;
    s32 temp_2_4;
    s32 temp_2_7;
    s32 var_17_2;
    Part *var_17_3;
    Ent  *var_17;
    s32 var_16_3;
    s32 var_16_2;
    s32 var_21;
    s32 var_21_2;
    s32 var_21_3;
    s32 var_16;
    s32 temp_2_6;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_3_4;
    s32 var_16_4;
    s32 ok;
    s32 ok_2;
    s32 ok_3;
    Row  *temp_22;
    Cell *temp_23;
    Root *temp_2;
    Cell *temp_2_5;
    Ent  *temp_2_8;
    Ent  *temp_2_9;
    Ent  *temp_2_10;
    Cell *temp_2_11;
    Cell *temp_4_3;
    Obj  *temp_4_5;
    temp_19 = func_15DE80();
    temp_16 = func_15DE40();
    temp_2 = func_1F5BE0();
    temp_2_2 = func_1C3BC0(temp_2, temp_2->r4344);
    temp_2_2->mA8(&sp140);
    temp_2_2->mA4(&sp130);
    func_1CBD00(&sp120, &sp140, &sp130);
    temp_3 = arg0->f2C8;
    switch (temp_3) {                               /* switch 1 */
    case 15:                                        /* switch 1 */
    case 16:                                        /* switch 1 */
        func_1418C0(temp_19, 0x2A4, 1.0f);
        temp_2_3 = func_159FB0(temp_16, D_0050D7A8, 0x2A4);
        if (temp_2_3 != 0) {
            temp_2_4 = func_141B00(temp_19);
            func_13E400(temp_2_4, 1);
            func_13E3E0(temp_2_4, 1);
            func_13E2F0(temp_2_4, 1);
            func_13E500(temp_2_4, 1);
            func_13E4F0(temp_2_4, 1);
            func_13E4D0(temp_2_4, 1);
            func_13E430(temp_2_4, 0);
            func_13E460(temp_2_4, 1);
            func_13F730(temp_2_4, 0);
            func_13EE40(temp_2_4, 0, 0x80, 0, 0x80);
            func_13F060(temp_2_4, 0.0f, 0.0f, -1.0f);
            func_13F5B0(temp_2_4);
            if ((arg0->f2D0 & 1) == 0) {
                temp_2_5 = factory_FactoryFineGridCellAt_503880(arg0, arg0->f2EE, arg0->f2F0);
                if (temp_2_5 != NULL) {
                    ok = (((temp_2_5->f04 & 0x8000) != 0) ^ 1);
                    if ((ok != 0) && (temp_2_5->f00 >= 0)) {
                        sp110[0].f = D_00480E10;
                        sp110[1].f = D_00480E14;
                        sp110[2].f = D_00480E18;
                        sp110[3].f = D_00480E1C;
                        temp_f20_4 = factory_FactoryFineGridCellCenterX_5037c0(arg0, arg0->f2EE);
                        temp_f0_4 = factory_FactoryFineGridCellCenterZ_503790(arg0, arg0->f2F0);
                        temp_sh = (s32) arg0->f64 >> 2;
                        temp_f2_3 = D_0045B080[0];
                        factory_FactoryRectFrameDraw_50a4c0(arg0, temp_2_4, temp_2_3, 0.5f * temp_f2_3, temp_f20_4 - temp_f2_3, temp_f0_4 - temp_f2_3, temp_f20_4 + temp_f2_3, temp_f0_4 + temp_f2_3, 1.0f, temp_sh, sp110);
                    }
                }
            } else {
                temp_4 = arg0->f300;
                if (temp_4 >= 0) {
                    temp_22 = (Row *)(arg0->f2AC + (temp_4 * 0xC));
                    *(W2 *)&sp100[0] = *(W2 *)&D_00480E20;
                    *(W2 *)&sp100[2] = *(W2 *)&D_00480E28;
                    temp_4_2 = temp_22->r06;
                    var_21 = temp_22->r08;
                    var_16 = temp_4_2;
                    if (arg0->f2C8 == 0x10) {
                        sp100[0].i = 0x43580000;
                        var_16 = var_21;
                        var_21 = temp_4_2;
                        sp100[1].i = 0x42000000;
                        sp100[2].i = 0x42000000;
                        sp100[3].i = 0x43000000;
                    }
                    temp_f2 = D_0045B080[0];
                    temp_f22 = D_0047D288 * temp_f2;
                    temp_f21 = D_0047D7C4 * temp_f2;
                    while (var_16 < var_21) {
                        temp_23 = temp_22->r00 + var_16;
                        temp_f20 = factory_FactoryFineGridCellCenterX_5037c0(arg0, temp_23->f00);
                        temp_f0 = factory_FactoryFineGridCellCenterZ_503790(arg0, temp_23->f02);
                        factory_FactoryRectFrameDraw_50a4c0(arg0, temp_2_4, temp_2_3, temp_f21, temp_f20 - temp_f22, temp_f0 - temp_f22, temp_f20 + temp_f22, temp_f0 + temp_f22, D_0047D278, (s32) arg0->f64 >> 2, sp100);
                        var_16 += 1;
                    }
                }
                spF0[0].f = D_00480E30;
                spF0[1].f = D_00480E34;
                spF0[2].f = D_00480E38;
                spF0[3].f = D_00480E3C;
                temp_f20_2 = factory_FactoryFineGridCellCenterX_5037c0(arg0, arg0->f2FA);
                temp_f0_2 = factory_FactoryFineGridCellCenterZ_503790(arg0, arg0->f2FC);
                temp_f2_2 = D_0045B080[0];
                temp_f21_2 = 0.5f * temp_f2_2;
                factory_FactoryRectFrameDraw_50a4c0(arg0, temp_2_4, temp_2_3, temp_f21_2, temp_f20_2 - temp_f2_2, temp_f0_2 - temp_f2_2, temp_f20_2 + temp_f2_2, temp_f0_2 + temp_f2_2, 1.0f, (s32) arg0->f64 >> 2, spF0);
                if (arg0->f2C8 == 0x12) {
                    spE0[0].f = D_00480E40;
                    spE0[1].f = D_00480E44;
                    spE0[2].f = D_00480E48;
                    spE0[3].f = D_00480E4C;
                    temp_f20_3 = factory_FactoryFineGridCellCenterX_5037c0(arg0, arg0->f2EE);
                    temp_f0_3 = factory_FactoryFineGridCellCenterZ_503790(arg0, arg0->f2F0);
                    temp_f1 = D_0045B080[0];
                    factory_FactoryRectFrameDraw_50a4c0(arg0, temp_2_4, temp_2_3, temp_f21_2, temp_f20_3 - temp_f1, temp_f0_3 - temp_f1, temp_f20_3 + temp_f1, temp_f0_3 + temp_f1, 1.0f, (s32) arg0->f64 >> 2, spE0);
                }
            }
            func_141A20(temp_19);
        }
        break;
    case 11:                                        /* switch 1 */
    case 17:                                        /* switch 1 */
    case 18:                                        /* switch 1 */
    case 19:                                        /* switch 1 */
        func_1418C0(temp_19, 0x2A4, 1.0f);
        temp_2_6 = func_159FB0(temp_16, D_0050D7A8, 0x2A4);
        if (temp_2_6 != 0) {
            temp_2_7 = func_141B00(temp_19);
            func_13E400(temp_2_7, 1);
            func_13E3E0(temp_2_7, 1);
            func_13E2F0(temp_2_7, 1);
            func_13E500(temp_2_7, 1);
            func_13E4F0(temp_2_7, 1);
            func_13E4D0(temp_2_7, 1);
            func_13E430(temp_2_7, 0);
            func_13E460(temp_2_7, 1);
            func_13F730(temp_2_7, 0);
            func_13EE40(temp_2_7, 0, 0x80, 0, 0x80);
            func_13F060(temp_2_7, 0.0f, 0.0f, -1.0f);
            func_13F5B0(temp_2_7);
            var_16_2 = 0;
            var_17 = factory_FactoryPartGroupFindById_504080(arg0, arg0->f2E8);
            spD0[0].f = D_00480E50;
            spD0[1].f = D_00480E54;
            spD0[2].f = D_00480E58;
            spD0[3].f = D_00480E5C;
            temp_3_2 = arg0->f2C8;
            switch (temp_3_2) {                     /* switch 2; irregular */
            case 17:                                /* switch 2 */
                spD0[2].i = 0x43580000;
                spD0[0].i = 0x42000000;
                spD0[3].i = 0x43000000;
                spD0[1].i = 0x42000000;
                break;
            case 19:                                /* switch 2 */
                if (var_17 == NULL) {
                    temp_16_2 = factory_FactoryGridColFromX_503f60(arg0, arg0->f360);
                    temp_2_9 = factory_FactoryGridPartGroupAt_502b20(arg0, temp_16_2, factory_FactoryGridRowFromZ_503f00(arg0, arg0->f368));
                    var_17 = temp_2_9;
                    if (temp_2_9 != NULL) {
                        var_16_2 = 1;
                    } else {
                        var_16_2 = 3;
                    }
                }
                spD0[0].i = 0;
                spD0[1].i = 0x43400000;
                spD0[2].i = 0;
                spD0[3].i = 0x43000000;
                break;
            case 18:                                /* switch 2 */
                if (var_17 == NULL) {
                    temp_16_3 = factory_FactoryGridColFromX_503f60(arg0, arg0->f360);
                    temp_2_10 = factory_FactoryGridPartGroupAt_502b20(arg0, temp_16_3, factory_FactoryGridRowFromZ_503f00(arg0, arg0->f368));
                    var_17 = temp_2_10;
                    if (temp_2_10 != NULL) {
                        var_16_2 = 1;
                    } else {
                        var_16_2 = 3;
                    }
                }
                if (arg0->f300 >= 0) {
                    var_16_2 = 2;
                }
                spD0[0].i = 0x43580000;
                spD0[1].i = 0x42000000;
                spD0[3].i = 0x43000000;
                spD0[2].i = 0x42000000;
                break;
            case 11:                                /* switch 2 */
                temp_17 = factory_FactoryGridColFromX_503f60(arg0, arg0->f360);
                temp_2_8 = factory_FactoryGridPartGroupAt_502b20(arg0, temp_17, factory_FactoryGridRowFromZ_503f00(arg0, arg0->f368));
                var_17 = temp_2_8;
                if (temp_2_8 != NULL) {
                    if (temp_2_8->e04 != 0xD) {
                        var_16_2 = 4;
                    } else {
                        var_16_2 = 1;
                    }
                }
                spD0[0].i = 0x43580000;
                spD0[1].i = 0x43580000;
                spD0[2].i = 0x43580000;
                spD0[3].i = 0x43000000;
                break;
            }
            switch (var_16_2) {                     /* switch 3; irregular */
            case 0:                                 /* switch 3 */
                if (factory_FactoryPartFootprintRect_502760(arg0, sp158, var_17, arg0->f2E4, arg0->f380, arg0->f388) != 0) {
                    var_16_3 = sp158[1];
                    temp_f2_7 = D_0045B080[0];
                    temp_f21_4 = D_0047D85C * temp_f2_7;
                    temp_f20_8 = D_0047D7E0 * temp_f2_7;
                    while (sp158[3] >= var_16_3) {
                        var_21_3 = sp158[0];
                        while (sp158[2] >= var_21_3) {
                            if (factory_FactoryPartHitTestCell_502970(arg0, var_21_3, var_16_3, var_17, sp158, arg0->f2E4) != 0) {
                                temp_f22_3 = factory_FactoryGridCellCenterX_503760(arg0, var_21_3) - (arg0->f380 - arg0->f360);
                                temp_f0_7 = factory_FactoryGridCellCenterZ_503730(arg0, var_16_3) - (arg0->f388 - arg0->f368);
                                factory_FactoryRectFrameDraw_50a4c0(arg0, temp_2_7, temp_2_6, temp_f20_8, temp_f22_3 - temp_f21_4, temp_f0_7 - temp_f21_4, temp_f22_3 + temp_f21_4, temp_f0_7 + temp_f21_4, 1.0f, (s32) arg0->f64 >> 2, spD0);
                            }
                            var_21_3 += 1;
                        }
                        var_16_3 += 1;
                    }
                }
                break;
            case 1:                                 /* switch 3 */
                temp_16_6 = factory_FactoryGridColFromX_503f60(arg0, arg0->f360);
                temp_2_11 = factory_FactoryGridCellAt_5037f0(arg0, temp_16_6, factory_FactoryGridRowFromZ_503f00(arg0, arg0->f368));
                if (temp_2_11 != NULL) {
                    ok_2 = (((temp_2_11->f04 & 0x8000) != 0) ^ 1);
                    if ((ok_2 != 0) && (temp_2_11->f00 >= 0) && (temp_2_11->f02 >= 0)) {
                        var_21_2 = 0;
                        temp_f2_6 = D_0045B080[0];
                        temp_f22_2 = D_0047D85C * temp_f2_6;
                        temp_f21_3 = D_0047D7E0 * temp_f2_6;
                        while (var_21_2 < arg0->f2A6) {
                            var_17_2 = 0;
                            while (var_17_2 < arg0->f2A4) {
                                temp_4_3 = (Cell *)arg0->f2A0 + (var_21_2 * arg0->f2A4) + var_17_2;
                                if (temp_4_3 != NULL) {
                                    ok_3 = (((temp_4_3->f04 & 0x8000) != 0) ^ 1);
                                    if ((ok_3 != 0) && (temp_4_3->f00 == temp_2_11->f00) && (temp_4_3->f02 == temp_2_11->f02)) {
                                        temp_f20_7 = factory_FactoryGridCellCenterX_503760(arg0, var_17_2);
                                        temp_f0_6 = factory_FactoryGridCellCenterZ_503730(arg0, var_21_2);
                                        factory_FactoryRectFrameDraw_50a4c0(arg0, temp_2_7, temp_2_6, temp_f21_3, temp_f20_7 - temp_f22_2, temp_f0_6 - temp_f22_2, temp_f20_7 + temp_f22_2, temp_f0_6 + temp_f22_2, 1.0f, (s32) arg0->f64 >> 2, spD0);
                                    }
                                }
                                var_17_2 += 1;
                            }
                            var_21_2 += 1;
                        }
                    }
                }
                break;
            case 2:                                 /* switch 3 */
                spD0[0].i = 0x43580000;
                spD0[1].i = 0x42000000;
                spD0[3].i = 0x43000000;
                spD0[2].i = 0x42000000;
                temp_16_5 = factory_FactoryFineGridColFromX_504020(arg0, arg0->f380);
                temp_17_3 = factory_FactoryFineGridRowFromZ_503fc0(arg0, arg0->f388);
                temp_f20_6 = factory_FactoryFineGridCellCenterX_5037c0(arg0, temp_16_5) - (arg0->f380 - arg0->f360);
                temp_f0_5 = factory_FactoryFineGridCellCenterZ_503790(arg0, temp_17_3) - (arg0->f388 - arg0->f368);
                temp_f2_5 = D_0045B080[0];
                factory_FactoryRectFrameDraw_50a4c0(arg0, temp_2_7, temp_2_6, 0.5f * temp_f2_5, temp_f20_6 - temp_f2_5, temp_f0_5 - temp_f2_5, temp_f20_6 + temp_f2_5, temp_f0_5 + temp_f2_5, 1.0f, (s32) arg0->f64 >> 2, spD0);
                break;
            case 3:                                 /* switch 3 */
                temp_16_4 = factory_FactoryGridColFromX_503f60(arg0, arg0->f380);
                temp_17_2 = factory_FactoryGridRowFromZ_503f00(arg0, arg0->f388);
                temp_f20_5 = factory_FactoryGridCellCenterX_503760(arg0, temp_16_4) - (arg0->f380 - arg0->f360);
                temp_f3 = factory_FactoryGridCellCenterZ_503730(arg0, temp_17_2) - (arg0->f388 - arg0->f368);
                temp_f2_4 = D_0045B080[0];
                temp_f1_2 = D_0047D85C * temp_f2_4;
                factory_FactoryRectFrameDraw_50a4c0(arg0, temp_2_7, temp_2_6, D_0047D7E0 * temp_f2_4, temp_f20_5 - temp_f1_2, temp_f3 - temp_f1_2, temp_f20_5 + temp_f1_2, temp_f3 + temp_f1_2, 1.0f, (s32) arg0->f64 >> 2, spD0);
                break;
            }
            func_141A20(temp_19);
        }
        break;
    case 14:                                        /* switch 1 */
        var_17_3 = (Part *)((u8 *)arg0 + 0xE0);
        var_16_4 = 0;
        do {
            temp_4_4 = var_17_3->p04;
            if ((temp_4_4 >= 0) && (var_17_3->p12 >= 0)) {
                spB0.a00 = var_17_3->p20;
                spB0.a04 = var_17_3->p24;
                spB0.a08 = var_17_3->p28;
                spB0.a0C = temp_4_4;
                spB0.a10 = var_17_3->p30;
                factory_FactoryMarkerUpdate_4ea160(&spB0, var_17_3->p08, (s16) (var_17_3->p34 / 30), 1);
            }
            var_16_4 += 1;
            var_17_3 += 1;
        } while (var_16_4 < 4);
        break;
    }
    temp_3_4 = arg0->f2C8;
    switch (temp_3_4) {                             /* switch 4 */
    case 15:                                        /* switch 4 */
    case 16:                                        /* switch 4 */
        func_1418C0(temp_19, 0x2A4, 1.0f);
        temp_4_5 = arg0->f58;
        if (temp_4_5 != NULL) {
            temp_4_5->m24();
        }
        break;
    case 11:                                        /* switch 4 */
    case 17:                                        /* switch 4 */
    case 18:                                        /* switch 4 */
    case 19:                                        /* switch 4 */
        func_1418C0(temp_19, 0x2A4, 1.0f);
        temp_18 = arg0->f58;
        spA0 = temp_18->o180;
        temp_17_4 = factory_FactoryGridColFromX_503f60(arg0, arg0->f380);
        temp_16_7 = factory_FactoryGridRowFromZ_503f00(arg0, arg0->f388);
        spA0.v.x = factory_FactoryGridCellCenterX_503760(arg0, temp_17_4) - (arg0->f380 - arg0->f360);
        spA0.v.z = factory_FactoryGridCellCenterZ_503730(arg0, temp_16_7) - (arg0->f388 - arg0->f368);
        func_151110(temp_18, &spA0);
        if (temp_18 != NULL) {
            temp_18->m24();
        }
        break;
    }
}
