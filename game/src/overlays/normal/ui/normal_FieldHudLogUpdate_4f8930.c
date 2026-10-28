/* rgp:protos */
#define RGP_SELF_normal_FieldHudLogUpdate_4f8930 1
#include "port/game_protos.h"
#line 1
/* === SESSION 78 (2026-09-21, SOLO): ** MATCH ** -- 246/246 words, 0 bad,
 * from 16 bad unmoved since session 37.  FOUR EDITS, ALL THE SAME LEVER, and
 * the lever is NOT an address SPELLING -- s37/s38/s44 were right that every
 * rewrite of `&o->f3C8[X]` (index cast, pointer cast, byte offset, reversed
 * textual operand order, a named pointer, a named index) canonicalises onto
 * ONE object.  What mwcc does NOT canonicalise is a variable that is
 * ASSIGNED TWICE: give the index its own statement and then REASSIGN the
 * same variable to add the base.  Each of the four `&o->f3C8[X]` sites then
 * picks its own operand order, and retail does not want the same one at all
 * four:
 *     r = (Rec *)(idx * (s32)sizeof(Rec));        <- index alone
 *     r = (Rec *)((s8 *)r + (s32)o->f3C8);        <- INDEX first  (0x004F89C8)
 *     r = (Rec *)(o->f3CD * (s32)sizeof(Rec));
 *     r = (Rec *)((s8 *)r + (s32)o->f3C8);        <- INDEX first  (0x004F8BD8)
 *     r = (Rec *)o->f3C8;                          <- BASE alone
 *     r = (Rec *)((s8 *)r + i * (s32)sizeof(Rec)); <- BASE  first  (cluster C)
 *     q = (s16 *)(o->f3CD * (s32)sizeof(Rec));
 *     p = (s8 *)o->f3C8 + 0x70;                    <- the +0x70 BIAS ON THE BASE
 *     q = (s16 *)(p + (s32)q);                     <- BASE  first  (0x004F8B74)
 * s44's cluster-(B) screen read the mechanism exactly right ("retail has ONE
 * address value and READS THROUGH IT, mwcc forward-substitutes and folds
 * +0x70 into the displacement") -- biasing the BASE is what makes retail's
 * `lh $2,0x0($3)` appear.  Order of the three q statements matters: `p`
 * assigned BETWEEN the two `q` statements is MATCH, `p` first is 9 bad.
 * Cluster C is a pure $2/$3 creation-order transposition and only the
 * base-alone-then-reassign form reaches it (16 -> 9 -> 1 -> MATCH).
 * !! `#pragma opt_dead_assignments off` is a REGRESSION on this unit at both
 * coats (23 bad at the baseline, 16 at the 9-bad coat) -- the s72 cross does
 * NOT apply here; the two-assignment shape does not need it.
 * Decks: build/wf-normal/s78/j1..j9, k1.
 */
/* SESSION 44 (n44j, SOLO): 16 bad / 246 words, UNMOVED, 12 more arms.
 * The new struct-field-offset screen (build/wf-normal/s44/offscan.py) reads
 * cluster (B) off exactly -- `0x0: retail 3 -> ours 2`, `0x70: retail 3 ->
 * ours 4`: retail performs ONE MORE access at displacement 0 and ONE FEWER at
 * 0x70, i.e. it has ONE address value (`q`) and READS THROUGH IT, while mwcc
 * forward-substitutes our `q` into the read and folds +0x70 into the
 * displacement.  s37/s38 tried the ASSOCIATION and a named temp for the
 * VALUE; this session tried pinning the POINTER WEB, which is the mechanism
 * the screen names.  ALL TWELVE COLLAPSE ONTO THE BASELINE OBJECT (fddcd2a5):
 * `q = (s16 *)(s32)q;` ([[levers.d/mwcc-propagated-temp-colouring]]), `q`
 * derived from a named `Rec *rq`, `&o->f3C8[(u32)o->f3CD].f070` (the index
 * cast), `(s8 *)o->f3C8 + 0x70 + ...` both unparenthesised and parenthesised,
 * either crossed with the web pin, a hoisted `idx` local, and
 * `(u8 *)&o->f3C8[o->f3CD] + 0x70`.  A `volatile` read at the `*q == 0` site
 * is 18 bad; volatile at two or three sites is LENGTH-WRONG (+1).
 * => The q-address SPELLING is now an exhaustively measured null: mwcc
 * canonicalises every form of it.  Whatever reaches cluster (B) is not an
 * address expression. */
/* SESSION 38 (n38a): re-confirmed the 16-bad/246-word baseline from n37f
 * unchanged, then spent the 3-round-trip cap on the (B)/(C) clusters per
 * n37f's own "untried" suggestions. All three tried spellings are NULL --
 * do not re-run them:
 *   1. Hoisting `r = &o->f3C8[o->f3CD];` from AFTER the `for(m...)` decrement
 *      loop to BEFORE it (same statements, no merge with `q`, semantically
 *      safe since `r` is only a pointer, not a cached value) -- this is NOT
 *      inert, it is a REGRESSION: length changes from 0x3d8 to 0x3b4 words
 *      (nscore prints `?` bad, "len 0x3b4 vs 0x3d8"). Reverted immediately.
 *   2. Giving cluster-(C)'s render loop (`for(i=0;i<5;i++){r=&o->f3C8[i];...}`)
 *      its OWN dedicated loop counter `ii` instead of reusing the
 *      function-wide `i` (the header's tried list only covered a dedicated
 *      POINTER `r2`, not a dedicated counter) -- BYTE-IDENTICAL, confirmed
 *      via --verbose: same 16 differing words at the exact same 16
 *      addresses as the baseline (0x004F89C8, 0x004F8B64-78, 0x004F8BD8,
 *      0x004F8C50-68, 0x004F8CE8).
 *   3. Folding the loop's `k += 1;` body statement into the for-loop's own
 *      post-expression (`for (i=0;i<5;i++,k+=1)`) instead of a separate
 *      trailing statement -- also BYTE-IDENTICAL, same 16 words/addresses.
 * Left the file in the exact n37f state (verified 16 bad / 246 words
 * before ending session). Confirms clusters (A)/(B)/(C) are canonicalisation
 * / scheduler residue as n37f suspected; the vreg-creation-source-position
 * lever ([[mwcc-vreg-creation-source-position]]) does NOT reach cluster (B)
 * by simple statement reordering (it regresses length instead), and simple
 * loop-counter-identity variations do not reach cluster (C). Next session
 * should try a genuinely different axis, not another reorder/rename of the
 * same statements -- e.g. the whole `if(*q==0){...}` block's larger
 * restructure n37f flagged as its last untried idea (moving the `for(m...)`
 * loop to a different position relative to the WHOLE q/r block, not just
 * relative to r alone), or attacking cluster (C) via
 * [[mwcc-loop-counter-priority]] with a genuinely different counter TYPE
 * (not just a different name) for `k`. */
/* SESSION 37 (n37f), first real residue diagnosis of this unit.
 *   before: 246 words, 25 bad   after: 246 words, 16 bad   (retail 246 words)
 * Fix: `if (r->f074 * -0x1A >= r->f072)` -> `if (r->f072 <= r->f074 * -0x1A)`.
 * Textually flipping that one comparison's operand order changed which
 * physical register mwcc picks for the two preceding `lh` loads (f074/f072)
 * and the `slt`, closing 9 of the then-25 bad words in one edit. See the
 * bottom of this file for the full residue classification and the (many)
 * spellings that were tried and came back byte-IDENTICAL (inert) on the
 * three remaining clusters -- do not re-run them.
 * Re-score with build/wf-normal/s33/nscore.py (or later), not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `B_comp_L157_bol` from the boolean/compound deck (mkbool31.py)
 *   before: 246 words, 29 bad   after: 246 words, 25 bad   (retail 246 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
#include "types.h"
/* normal 0x004F8930 -- the 5-slot scrolling message ticker.  o->f3C8 is a ring
 * of five 0x76-byte records (a 0x70-byte string plus three s16 counters);
 * f3CD is the head, f3CE the population.  The `\n` scan counts embedded line
 * breaks to size the box, then the five widget slots are re-placed.
 * The 0x1A / -0x1A products are the classic shift/sub expansions.
 * The `& ~1 | 1` byte at entry+6 is a one-bit BITFIELD store: `and` against a
 * register-held -2 (not `andi`) plus a `daddiu`-materialised 1. */

typedef struct Rec {
    s8  text[0x70];
    s16 f070;
    s16 f072;
    s16 f074;
} Rec;                                  /* 0x76 */

typedef struct Ent {
    u8 pad000[6];
    u8 b0 : 1;
    u8 b1 : 7;
} Ent;

typedef struct Holder {
    u8  pad000[0x42];
    s16 f042;
} Holder;

typedef struct Stage {
    u8      pad000[0x244];
    Holder *f244;
} Stage;

typedef struct Ctx {
    u8     pad000[0x20];
    Stage *f020;
} Ctx;

typedef struct Hnd {
    u8  pad000[4];
    s32 f004;
} Hnd;

typedef struct Obj {
    u8   pad000[0x378];
    s16  f378;
    u8   pad37A[0x3C8 - 0x37A];
    Rec *f3C8;
    s8   f3CC;
    s8   f3CD;
    s8   f3CE;
    u8   pad3CF[1];
    s8   f3D0;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudLogUpdate_4f8930(Obj *o)
{
    Ctx    *ctx;
    s32     i;
    Holder *obj;
    Ent    *e;
    Rec    *r;
    s16    *q;
    s8     *p;
    Hnd    *h;
    s8      c;
    s32     n;
    s32     idx;
    s32     base;
    s32     j;
    s32     m;
    u16     k;

    if (o->f378 != 0) {
        if (o->f3CC != 0) {
            ctx = ((Ctx *)GetGameData_1fede0());
            if (ctx != NULL) {
                obj = ctx->f020->f244;
                if (obj != NULL) {
                    n = o->f3CE;
                    base = 0;
                    if (n != 0) {
                        idx = o->f3CD + ((s8)n - 1);
                        if (idx >= 5) {
                            idx -= 5;
                        }
                        r = (Rec *)(idx * (s32)sizeof(Rec));
                        r = (Rec *)((s8 *)r + (s32)o->f3C8);
                        base = r->f072 + r->f074 * 0x1A;
                    }
                    if ((s8)n < 5) {
                        for (i = 0; i < obj->f042; i++) {
                            e = ((Ent *)CharaEventLogGetEntry_3a62b0(obj, i));
                            if (e == NULL) {
                                continue;
                            }
                            if (e->b0 != 0) {
                                continue;
                            }
                            e->b0 = 1;
                            j = o->f3CD + o->f3CE;
                            if (j >= 5) {
                                j -= 5;
                            }
                            CharaEventLogEntryFormat_3a6a30(e, &o->f3C8[j]);
                            o->f3C8[j].f072 = base + 0x1A;
                            o->f3C8[j].f074 = 0;
                            o->f3D0 = 5;
                            p = o->f3C8[j].text;
                            while ((c = *p) != 0) {
                                if (c == 0x5C && p[1] == 0x6E) {
                                    p++;
                                    o->f3C8[j].f074 = o->f3C8[j].f074 + 1;
                                }
                                p++;
                            }
                            o->f3C8[(u32)j].f070 = o->f3C8[(u32)j].f074 * 5 + 0x1E;
                            o->f3CE = o->f3CE + 1;
                            break;
                        }
                    }
                    if (o->f3CE > 0) {
                        q = (s16 *)(o->f3CD * (s32)sizeof(Rec));
                        p = (s8 *)o->f3C8 + 0x70;
                        q = (s16 *)(p + (s32)q);
                        if (*q == 0) {
                            for (m = 0; m < 5; m++) {
                                o->f3C8[m].f072 = o->f3C8[m].f072 - 4;
                            }
                            r = (Rec *)(o->f3CD * (s32)sizeof(Rec));
                            r = (Rec *)((s8 *)r + (s32)o->f3C8);
                            if (r->f072 <= r->f074 * -0x1A) {
                                r->f070 = -1;
                                o->f3CE = o->f3CE - 1;
                                if (o->f3CD >= 4) {
                                    o->f3CD = 0;
                                } else {
                                    o->f3CD = o->f3CD + 1;
                                }
                            }
                        } else if (*q > 0) {
                            *q = *q - 1;
                        }
                    }
                    k = 0x7A;
                    for (i = 0; i < 5; i++) {
                        r = (Rec *)o->f3C8;
                        r = (Rec *)((s8 *)r + i * (s32)sizeof(Rec));
                        if (r->f070 >= 0) {
                            UiSetWidgetPos_290f60(o, k, 0, r->f072);
                            h = ((Hnd *)UiGetWidgetText_28f620(o, k, 0));
                            h->f004 = (s32)&o->f3C8[i];
                            UiSetWidgetAlpha_2907a0(o, k, 1.0f);
                        } else {
                            UiSetWidgetAlpha_2907a0(o, k, 0.0f);
                        }
                        k += 1;
                    }
                }
            }
        }
    }
}

/* SESSION 37 (n37f) residue notes, at 16 bad / 246 words.
 *
 * Verified ALREADY MATCHING (no work needed, contrary to what the file
 * header used to imply nobody had checked):
 *   - the `& ~1 | 1` bitfield store on Ent.b0 (0xE8-0x108) -- byte-identical.
 *   - the `r->f072 + r->f074 * 0x1A` shift/sub expansion for 0x1A -- identical.
 *   - the `r->f074 * -0x1A` shift/sub expansion for -0x1A -- identical
 *     (only the ADDRESS computation feeding it, not the multiply, was bad).
 *   - every mod-5 ring-index wraparound (`if (idx>=5) idx-=5;` and the
 *     `o->f3CD>=4` wrap) -- these are plain compare+subtract in RETAIL TOO,
 *     not a division-by-constant idiom. Nothing to fix here.
 *   - the fresh `&o->f3C8[i]` recompute for `h->f004` inside the render
 *     loop -- matches (mwcc does NOT CSE it against the loop's `r`, as
 *     [[mwcc-member-address-no-cse]] predicts, and retail does the same).
 *
 * Remaining 16 bad fall into 3 clusters, all inside the record-address
 * (`&o->f3C8[X]`, stride 0x76) computation itself:
 *
 * (A) 1 word, 0x004F89C8 and again 0x004F8BD8: the FINAL `addu` of the
 *     idx*0x76 + base sequence has operands transposed (`addu rd,off,base`
 *     in retail vs `addu rd,base,off` in ours) -- same registers, same
 *     value, different rs/rt. Tried and BYTE-IDENTICAL (inert) on both
 *     occurrences: `(Rec*)((s8*)o->f3C8 - (-(idx*(s32)sizeof(Rec))))` (the
 *     non-commutative rewrite from [[mwcc-commutative-add-operand-order]]),
 *     `idx + o->f3C8` (reversed textual operand order), and the plain
 *     `(Rec*)(idx*(s32)sizeof(Rec) + (s8*)o->f3C8)` cast form. mwcc
 *     canonicalises `arr[i]`-shaped address adds before this point is
 *     reachable from C -- this looks like the same "below the source
 *     language" class ix23 found on insect, and the call-result escape
 *     hatch that lever documents does not apply here (neither operand is
 *     a call). PARKED as source-unreachable; do not re-try plain operand
 *     reordering here.
 *
 * (B) 7 words, 0x004F8B64-0x004F8B78: computing `q = &o->f3C8[o->f3CD].f070`.
 *     Retail interleaves the `+0x70` field-offset add into the MIDDLE of
 *     the idx*0x76 shift/sub chain (folding it into the base pointer
 *     before the multiply finishes), then reads `*q` via that same
 *     register at offset 0. Ours computes the full record pointer first,
 *     then adds +0x70 in a separate trailing `addiu` that is used ONLY for
 *     the later `*q = *q-1` write -- the READ instead re-derives the
 *     address as `record_ptr + 0x70` (an equivalent but differently-coded
 *     value). Tried and BYTE-IDENTICAL: interleaving the `+0x70` textually
 *     early (`(s8*)o->f3C8 + 0x70 + o->f3CD*sizeof(Rec)`), splitting it
 *     into two statements (`p = (s8*)o->f3C8+0x70; q = (s16*)(p + ...)` --
 *     this one was NOT inert, it REGRESSED to 28 bad, reverted), changing
 *     q's declared type to `Rec *` and using `q->f070` (changes LENGTH,
 *     reverted), and forcing the read through a named temp
 *     (`qv = *q; if (qv==0) ...`, inert). Untried: nothing obviously left
 *     in this family; likely the same canonicalisation as (A) but for a
 *     member-of-indexed-element address. Someone with more session budget
 *     could try restructuring the WHOLE `if(*q==0){...} else if(*q>0)`
 *     block's statement order (e.g. moving the `for(m...)` loop before or
 *     after the q read) since that changes register PRESSURE at the q
 *     site, but a first attempt at merging q's computation with the
 *     later `r = &o->f3C8[o->f3CD]` (reusing one pointer for both) changed
 *     the function's LENGTH (0x3d4/0x3d8 vs 0x3d8 in two different arms)
 *     and was reverted without a working variant found.
 *
 * (C) 8 words, 0x004F8C50-0x004F8C68 plus the loop-rotated re-fetch at
 *     0x004F8CE8: inside `for (i=0;i<5;i++) { r=&o->f3C8[i]; ... }`, the
 *     `lw` of `o->f3C8` and the idx*0x76 shift/sub-chain temp land in
 *     SWAPPED physical registers vs retail (retail keeps the lw result in
 *     $3 and chains in $2; ours keeps lw in $2(v0) and chains in $3(v1)),
 *     even though the FINAL address register matches ($3/v1) and the
 *     loop-rotated first-iteration hoist ("sll $2,$18,4 before the loop,
 *     recomputed at the bottom for the next iteration") is structurally
 *     present in both. Tried and BYTE-IDENTICAL: moving `r=&o->f3C8[i]`
 *     inside the `if` guard and reading `o->f3C8[i].f070` directly for the
 *     condition instead, flipping the guard to `if (0 <= r->f070)`, and
 *     giving the loop its OWN dedicated pointer local (`Rec *r2`) instead
 *     of reusing the function-wide `r`. All three produced the identical
 *     object to the baseline. PARKED alongside (A); this smells like the
 *     same class, just inside a rotated loop.
 *
 * â‡’ The ONE real lever found this session was flipping a `>=` comparison's
 *   textual operand order (`a >= b` -> `b <= a`) on a two-LOAD compare --
 *   it moved which register mwcc assigns to each of the two preceding
 *   loads. That fixed cluster's siblings (A)/(C) are pure address-add
 *   operand transpositions/register swaps with NO comparison attached, and
 *   every operand-order and cast-form spelling tried on those came back
 *   inert -- they look like genuine canonicalisation below the C source,
 *   not a spelling gap. Whoever picks this up next should look for a
 *   DIFFERENT lever family (e.g. scheduling-driven, per
 *   [[mwcc-vreg-creation-source-position]] / loop-rotation specific
 *   tricks) rather than more operand permutations on the address adds
 *   themselves.
 */
