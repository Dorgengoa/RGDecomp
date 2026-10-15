/* === SESSION 85 (2026-09-21, SOLO): **MATCH**, 329 words, byte-identical, and
 * NORMAL.BIN relinked byte-identical with 645 compiled units.  s84 left this
 * unit at 9 bad and called them "ONE DEFECT -- the two homed halfword cells are
 * SWAPPED"; that was right, and the fix is TWO EDITS, both on `mode`:
 *
 *     s16 mode          (was `volatile s16 mode`)
 *     if (mode)         (was `if (mode != 0)`, BOTH sites)
 *
 *  1. THE ALLOCATION RULE, measured this session (s85/b1, base + a used
 *     `volatile s16 dz` local: dz 0xBE / mode 0xBC / slot 0xBA):
 *       FRONTEND memory objects (volatile or address-taken) are allocated
 *       TOP-DOWN in REVERSE DECLARATION ORDER over the whole params-then-locals
 *       list, and BACKEND homes are allocated BELOW ALL OF THEM.
 *     A PARAMETER can therefore never sort above a later-declared one, so with
 *     `volatile s16 mode` (the last parameter) mode ALWAYS took 0xBE and slot's
 *     backend home ALWAYS fell to 0xBC -- no spelling of the HOMING could ever
 *     fix it, which is why s84's 215 pragma arms and every volatile/lvalue-cast
 *     arm read as a null.  With NEITHER parameter volatile both are BACKEND
 *     homes, and backend homes go in DECLARATION ORDER: slot 0xBE, mode 0xBC.
 *  2. WHICH REGISTER THE RELOAD TARGETS IS THE ORACLE for that distinction, and
 *     it is what closed the case: retail reads `lh $2,0xBE($29)` and then
 *     COPIES ($2 -> $30/$3/$2), i.e. always through the scratch register.  A
 *     frontend object loads STRAIGHT INTO its destination and never emits the
 *     copy -- seven read spellings ((s32), (s16), +0, via a temp, s16 locals...)
 *     gave ONE object at 326 w, exactly 3 words short = the three missing
 *     copies.  So `lh v0` + a copy NAMES a backend home and proves retail has
 *     no frontend memory object at all.
 *  3. `#pragma optimization_level 3` (s84's install) is still what makes the
 *     backend home the halfword parameters at all; without it neither homes.
 *  4. Dropping `volatile` alone is +1 w: mode's NARROWED value goes into a
 *     16-byte `sq` temp at 0xB0 that inflates the frame 0xC0 -> 0xD0.  Writing
 *     BOTH tests `if (mode)` instead of `if (mode != 0)` is what removes it --
 *     the bare test needs no materialised conversion, and `volatile` had been
 *     pinning the second test's `lh` (a volatile access cannot be hoisted)
 *     where a plain parameter lets the scheduler lift it 13 words above the
 *     `q->f2x` store block.  The 6x6 cross of the two test spellings (s85/k1)
 *     is FOUR objects; `!= 0` on EITHER site is length-wrong or mis-scheduled.
 *  => `if (x)` and `if (x != 0)` ARE NOT THE SAME OBJECT.  New board lever.
 * Decks: build/wf-normal/s85/{a1,b1,c1,d1,e1,f1,g1,h1,i1,j1,k1}.py, new tools
 * cells.py (rank arms by the TOP-OF-FRAME CELL MAP, not by `bad`) and coat.py.
 */
/* === SESSION 84 (2026-09-21, SOLO): 247 -> 9 BAD at exact 329 words, and the
 * FRAME AND SAVE SET ARE NOW RETAIL'S (192 / 10 saves / ZERO sp-locals; we had
 * 208 and a `sq v0,176(sp)` spill).  Eight installs, in order of what each was
 * worth.  Decks build/wf-normal/s84/{b1,c1,d1,e1,f1,g1,h1,i1,j1,k1,l1,m1,n1,
 * o1,p1,q1,r1}.py.  ALL NINE REMAINING WORDS ARE ONE DEFECT -- see the end.
 *
 *  1. `if (cc == 0) n = 0x3C; else n = ...clipLen(cc-1)...;`  (was: call it
 *     unconditionally and overwrite).  Retail's `bnel $2,$0,.L004EE318` SKIPS
 *     the virtual call.  This alone took the frame 208 -> 192 and killed the
 *     spill: the spill was never a `const` hoist, it was the unconditional
 *     evaluation.  (`extern s32 D_004659B0` without `const` ALSO reaches 192,
 *     -5 w -- a symptom, not the cause; do NOT drop the const, it is worse
 *     once the if/else is in.)
 *  2. `#pragma optimization_level 3`.  THE PRAGMA COLUMN WAS RE-PRICED ON THE
 *     NEW COAT and is NOT what s77 closed: level 3 alone is dist 143 against
 *     the default level-4's 250, and IT IS WHAT HOMES THE HALFWORD PARAMETERS
 *     (`sh $8,0xBC(sp)` + reloads), which no source spelling reached.
 *  3. drop the s31 `slot = (s16)slot;` -- with L3 it costs FIVE words.
 *  4. `sp = fr * (aa - bb);` BEFORE `n = (s32)((f32)bb * fr);` in the cc == 0
 *     branch (the cc != 0 branch already had retail's order).  dist 250 -> 182
 *     at EXACT LENGTH while `bad` went 247 -> 248: rank by adiff, not by count.
 *  5. `cc`'s address: a pointer REASSIGNED, not indexed --
 *         s16 *pa = (s16 *)((u8 *)a->ents + 0xA);
 *         pa = (s16 *)((u8 *)pa + slot * 16);  cc = *pa;
 *     retail computes `addiu $2,$2,0xA` SEPARATELY and loads at 0x0($2);
 *     every one-expression spelling folds the 0xA into the displacement.
 *  6. `ci = cc - 1;` named once, feeding clipStart AND clipLen (retail keeps it
 *     in $19 and copies it to $5 twice).  4+5+6 together = EXACT 329 w, 74 bad.
 *  7. `lo = flags & 0x3F;` BEFORE `hi = flags & 0x3F00;`, BOTH after the
 *     `w == 0` return.  74 -> 39.  s84/g1 measured this INERT on the pre-L3
 *     coat -- [[levers.d/reprice-retired-units]] again, 35 words.
 *  8. the ents address as a NON-COMMUTATIVE SUBTRACTION,
 *     `(Ent *)(slot * 16 - (-(s32)(u8 *)a->ents))`, 14 sites.  39 -> 25.
 *     `off + base` and `base + off` are the SAME object (mwcc normalises the
 *     load into rs) -- [[levers.d/mwcc-commutative-add-operand-order]].
 *  9. `s32 k;` declared BEFORE `s32 j;`, and the `lo` guard written
 *     `if (lo == 0) bb = aa; else bb = aa - 1;` (both sites).  25 -> 9.
 *
 * WHAT IS LEFT -- ONE DEFECT, NINE WORDS (16,17,18,26,42,78,196,252,303):
 * THE TWO HOMED HALFWORD CELLS ARE SWAPPED.  Retail `sh $8,0xBE($29)` (slot)
 * and `sh $10,0xBC($29)` (mode); ours has mode at 0xBE and slot at 0xBC, so
 * both stores and all six `lh` reloads read the wrong cell.  MEASURED NULLS on
 * this coat -- do not re-run:
 *   - `s16 mode` / `const volatile` / `s16 volatile` / `volatile u16` /
 *     `volatile s32` for mode: every one is either byte-identical or +1 word.
 *   - `*(volatile s16 *)&mode` is BYTE-IDENTICAL to the volatile parameter, so
 *     the lvalue cast homes exactly like the qualifier.
 *   - homing BOTH through the cast (s84/r1) STILL gives mode 0xBE slot 0xBC:
 *     the cell list is NOT decl order.  Ours orders by argument register
 *     DESCENDING ($10 -> 0xBE, $8 -> 0xBC); retail's is the other way round.
 *   - `volatile s16 slot` is +19 w (18 reloads) at every coat tried.
 *   - `s16 *pm = &mode; *pm != 0` is +1 word.
 *   - the WHOLE valid pragma table re-swept on this coat, x {mode volatile,
 *     plain} = 215 arms: ONE live cell, `opt_lifetimes off`, at 16 bad.
 * => the next lever is what ORDERS the homed-cell list, not what homes a
 * value.  [[levers.d/mwcc-homed-cell-decl-order]] needs a second reading.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* === SESSION 74 (2026-09-21, SOLO): 252 -> 247 BAD, exact 329 words.  A
 * TWO-EDIT CROSS whose halves are BOTH length-wrong alone, and one half is a
 * REAL BUG FIX that four sessions had priced and left on the table.
 *  1. `volatile s16 mode` (-1 word alone).  s69 measured this and moved on
 *     because the sign was wrong; it is STRUCTURALLY EXACT and that is what
 *     matters.  READ OF THE OBJECT: our park spilled the NARROWED (s16)mode
 *     (dsll32/dsra32 of $s2) into an ANONYMOUS 16-BYTE `sq`/`lq` TEMP at
 *     sp+0xC0, where retail HOMES the RAW parameter (`sh $10,0xBC($29)`) and
 *     re-narrows for free on each `lh` reload.  Under `volatile` we emit
 *     `sh $t2,0xCE(sp)` in the prologue and EXACTLY TWO `lh` reloads --
 *     retail has exactly two.  The sq/lq pair is GONE.
 *     [[levers.d/mwcc-named-home-vs-inline-spill]] (sq = temp, sh/lh = home)
 *     + [[levers.d/mwcc-readback-carries-conversion]].
 *     !! `volatile` is right for `mode` (2 uses = retail's 2 lh) and WRONG for
 *     `slot` (~16 uses vs retail's 4 lh -- s69 measured +22).  The construct
 *     is not the question; the RELOAD COUNT is.
 *  2. `id = slot + 0x39;` hoisted above the `e == 0` guard (+1 word alone).
 *     This is s54's uninitialised-`id` bug fix, retail's
 *     `addiu $16,$30,0x39` in that guard's own delay slot.  !! s54 priced the
 *     hoist at -2 and s74 re-measured it at +1 on the current coat --
 *     [[levers.d/reprice-retired-units]].  `after_lo` and `before_grd` are ONE
 *     object (247); `before_lo` 248, `after_hi` 250.
 *  ARMED: `u16 wid` is INERT on this coat (s69 had it at -1); dropping the s71
 *  `slot = (s16)slot;` self-cast is length-wrong (0x518) under the cross.
 * WHAT IS LEFT, and the object names it: ONE anonymous 16-byte `sq`/`lq` temp
 * at sp+0xB0 (stored from a `lw v0,0(v0)` and reloaded across both mode
 * blocks) is the whole frame difference -- retail 0xC0, ours 0xD0.  Kill that
 * temp and `slot`'s home fits in the pad retail uses at 0xBC/0xBE.
 * MEASURED NULL this session (build/wf-normal/s74/e1..e9,f1):
 *  - the HOMING axis for `slot` is now closed from THREE directions: a def in
 *    a second basic block (every extra `slot = (s16)slot;` is LENGTH-WRONG --
 *    the self-cast is a RE-NARROW, not a home; s69 had named this as THE
 *    untried arm), a LIVE address-take (`s16 *ps = &slot;` read back through
 *    the pointer: 0x578, +21, and WHICH regions use `*ps` is fully inert --
 *    14 arms, TWO objects), and `volatile` (+22, s69).
 *  - opposite-signed length levers, all mapped monotonically: naming
 *    `(u8 *)a->ents` -20 w (16-site map), naming `a->win` +6, a named
 *    `o16 = slot * 16` ~-2 per site over 15 sites.  Their best cross with the
 *    homing is 0x52c (+2) and it is a FLOOR over a 32-cell map.
 */
/* === SESSION 71 (2026-09-21, SOLO): 257 -> 252, exact 329 words; alignment
 * distance 185 -> 147 on ONE edit: `slot = (s16)slot;` (a redundant
 * self-cast) at the top of the `mode != 0` block -- retail re-narrows slot
 * there.  READ OF THE HOMES: retail's `sh t0,0xBE / sh t2,0xBC` are most likely
 * REGISTER-PRESSURE SPILLS -- retail uses all nine callee-saved registers
 * (s0-s8), holding id, lo, hi, slot*16, e, a, idx, w and a re-read slot.
 * Dead address-takes (`ps = &slot`, `(void)&mode`) and dead re-defs in the
 * early exit are optimised away (byte-identical); s54's `id` move is still
 * 2 short in every placement, and a named `o16 = slot * 16` is +1..-2.
 * Next: match the LIVE SET, not the spelling. */
/* === SESSION 69 (2026-09-20, SOLO): STILL 257 BAD / 329 words, no install.
 * s54's two-edit cross ("make `slot`/`mode` read back from memory, THEN move
 * `id` up") was attacked on the PARAMETER-DECLARATION axis for the first time.
 * Retail HOMES both s16 parameters in the prologue (`sh $8,0xBE($29)`,
 * `sh $10,0xBC($29)`) and re-reads `slot` with `lh` four times and `mode`
 * twice; we keep them in two callee-saved registers and pay dsll32/dsra32.
 * MEASURED, all against the 329-word / 257-bad baseline:
 *   volatile s16 mode        -1 word (0x520)   <- the only useful single arm
 *   volatile s16 slot       +22 words (0x57c)  <- re-reads at EVERY use, dead
 *   volatile both           +21 words (0x578)
 *   u16 wid (arg 2)          -1 word (0x520)   <- retail's entry andi $5,$5,0xFFFF
 *   volatile mode + u16 wid  -2 words (0x51c)
 *   + u16 slot               -6 words;  volatile mode + u16 slot  -5 words
 *   s16 idx (arg 6)          +1 word  (0x528)
 * ==> `volatile` is NOT retail's construct for `slot`: it reloads at EVERY use
 * where retail reloads once per region.  Per the s84 refinement in
 * levers.d/mwcc-named-home-vs-inline-spill.md, what HOMES a local is having a
 * DEF IN A SECOND BASIC BLOCK -- not `volatile`, not being named.  That is the
 * untried arm for `slot`.  !! Note every arm above has the WRONG SIGN: s54
 * needs the homing to be length-NEUTRAL so that moving `id` up (which is 2
 * words SHORT on its own) can be paid for, and all of these are short too.
 * Sweeps: build/wf-normal/s69/p_ee080a.py, p_ee080b.py
 */
/* SESSION 65: both `i < 6` loop bounds spelled `i <= 5` -- [[at-compare-class]]
 * for retail's `slti $1,$4,0x6` / `slti $1,$5,0x6`.  259 -> 257 bad at the same
 * 329 words, and atscan.py prints no slti row for this unit any more.  The
 * remaining `slt $1,$6,$4` (a REGISTER-bound compare) is still unfound.
 */
/* === SESSION 54 (2026-09-12, SOLO): 259 BAD / 329 words.  A REAL SOURCE
 * DEFECT is named (found by build/wf-normal/s54/uninit.py) and PRICED.
 * `id` is READ UNINITIALISED at `func_28FCD0(a->win, id, -1, 0)` inside the
 * `e == 0` early exit and only ASSIGNED ~40 lines later.  Retail computes it
 * BEFORE that guard and puts it in the guard's own delay slot:
 *   004EE0F4 andi  $18,$16,0x3F      lo = flags & 0x3F     <- lo BEFORE hi
 *   004EE0F8 andi  $17,$16,0x3F00    hi = flags & 0x3F00
 *   004EE0FC daddu $30,$2,$0         slot, re-read from its 0xBE($29) home
 *   004EE100 bnez  $20,.L004EE128    if (e != 0)
 *   004EE104  addiu $16,$30,0x39     id = slot + 0x39
 * âš  BUT MOVING IT UP IS 2 WORDS SHORT (0x51c vs 0x524) in all three
 * placements measured (a_4ee080.py: id after `lo`, `lo` before `hi` as well,
 * `id` before `lo`); keeping BOTH assignments is 5 short.  Exactly the
 * normal_FieldHudRadarReset_4f17c0 situation -- the bug is currently PAYING for words we
 * are missing elsewhere, so it is a two-edit cross
 * ([[levers.d/two-edit-cross-beats-count-ranking]]).
 * WHERE THE OTHER TWO WORDS ARE: opscan says `lh 8->2, dsll32 0->3,
 * dsra32 0->3, lq 9->11, sq 9->11`.  Retail HOMES the two s16 parameters
 * (`sh $8,0xBE($29)`, `sh $10,0xBC($29)` in the prologue) and RE-READS them
 * with `lh` eight times; the read-back carries the sign extension for free
 * ([[levers.d/mwcc-readback-carries-conversion]]).  We keep `slot`/`mode` in
 * registers -- TWO MORE callee-saved registers than retail -- and pay three
 * explicit `dsll32`/`dsra32` pairs for the narrowing instead.
 * â‡’ NEXT: make `slot`/`mode` read back from memory (or otherwise spend the
 * two callee-saved registers retail does not), THEN move `id` up.
 */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_id_L140_T188_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 327 words, ? bad   after: 329 words, 262 bad   (retail 329 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `E_seedthen_L199_els` from the seed/else deck (mkelse31.py)
 *   before: 322 words, ? bad   after: 327 words, ? bad   (retail 329 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
#pragma optimization_level 3
/* normal 0x004EE080 -- FRESH, session 31 lane a2.
 * Binds a timeline/gauge widget: resolves window `wid` in `a`, clears the
 * slot's decoration bytes, picks the lowest set bit of the low 6 flag bits,
 * lays out two 4-short boxes in the record's 0x40-byte entry `idx`, then
 * either drives the animation clip (virtual slots 34/35) or the object's own
 * frame counters (virtual slots 22/23).
 *
 * `jalr $25` x5 with `lw $25,0x0($20)` -- C++ virtual, vptr at offset 0,
 * first virtual at vtable +0x08, so 0x60/0x64/0x90/0x94 are indices
 * 22/23/34/35.
 * D_004659B0 is a MAIN-image int outside the gp window -- lui/lwc1 + cvt.s.w
 * is mwcc's `(f32)someIntGlobal`.
 * The ents[] accesses are written with the operand order m2c transcribed:
 * `off + (u8*)base` gives `addu $2,$off,$base`, `(u8*)base + off` the reverse,
 * and retail contains BOTH in this one function. */

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
    virtual s32 curFrame();               /* 22 -> vtable +0x60 */
    virtual s32 frameCount();             /* 23 -> vtable +0x64 */
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
    virtual s32 clipStart(s32 i);         /* 34 -> vtable +0x90 */
    virtual s32 clipLen(s32 i);           /* 35 -> vtable +0x94 */
};

typedef struct Ent {
    s32 f00;
    f32 f04;
    s16 f08;
    s16 f0A;
    s16 f0C;
    u8  f0E;
    u8  f0F;
} Ent;

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x20 - 0x10];
    s16 f20;
    s16 f22;
    s16 f24;
    s16 f26;
    s16 f28;
    s16 f2A;
    s16 f2C;
    s16 f2E;
    u8  pad30[0x40 - 0x30];
} Box;

typedef struct Rec {
    u8   pad00[0x20];
    Box *f20;
} Rec;

typedef struct Ctx {
    u8   pad00[0x14];
    u8   win[0xEC - 0x14];
    Ent *ents;
} Ctx;

extern const s32 D_004659B0;

extern "C" f32   func_13C010(void);
extern "C" void  func_28FCD0(const void *w, u16 id, s32 a, s32 b);
extern "C" Rec  *func_290460(const void *w, u16 id);
extern "C" void  func_2905B0(const void *w, u16 id, f32 a, f32 b, f32 c, f32 d);
extern "C" void  func_2907A0(const void *w, u16 id, f32 a);
extern "C" void  func_291110(const void *w, u16 id, s32 a, s32 b);

extern "C" s32 normal_MenuBattleEndWeaponSlotSetupMaybe_4ee080(Ctx *a, s32 wid, Obj *e, s32 flags, s16 slot,
                                   s32 idx, s16 mode);

s32 normal_MenuBattleEndWeaponSlotSetupMaybe_4ee080(Ctx *a, s32 wid, Obj *e, s32 flags, s16 slot,
                        s32 idx, s16 mode)
{
    Rec *r;
    Box *w;
    Box *q;
    s32  lo;
    s32  hi;
    s32  id;
    s32  off;
    s32  n;
    s32  i;
    s32  k;
    s32  j;
    s32  aa;
    s32  bb;
    s32  cc;
    s32  ci;
    f32  fr;
    f32  sp;

    r = func_290460(a->win, wid);
    if (r == 0) {
        return 2;
    }
    w = r->f20;
    if (w == 0) {
        return 3;
    }
    lo = flags & 0x3F;
    hi = flags & 0x3F00;
    id = slot + 0x39;
    if (e == 0) {
        w[1].f00 = -1;
        func_28FCD0(a->win, id, -1, 0);
        return 1;
    }
    if (mode) {
        ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0C = 0;
        ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0A = 0;
        ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0E = 0;
        ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0F = 0;
        if (lo != 0) {
            for (i = 0; i <= 5; i++) {
                if (lo & (1 << i)) {
                    ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0A = i;
                    break;
                }
            }
        }
        if (hi != 0) {
            if (hi == 0x3F00) {
                if (lo != 0) {
                    ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0F = 1;
                } else {
                    ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0F = 2;
                    ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0A = 0xFF;
                }
            } else if (lo != 0) {
                if (lo & (hi >> 8)) {
                    ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0E = 1;
                }
            } else if (!(hi & 0x100)) {
                ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0A = 0;
            } else {
                n = (s32)(5.0f * func_13C010());
                k = 0;
                for (j = 1; j <= 5; j++) {
                    if (!(hi & (1 << (j + 8)))) {
                        ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0A = j;
                        if (!(k < n)) {
                            break;
                        }
                        k++;
                    }
                }
            }
        }
    }
    off = idx * 0x6F;
    q = &w[idx];
    q->f00 = (s16)(off + 0x21);
    q->f02 = 0x1C;
    q->f08 = 0xC;
    q->f0A = 0x56;
    q->f0C = 0x48;
    q->f04 = 0x48;
    q->f0E = 8;
    q->f06 = 8;
    {
        s16 *pa = (s16 *)((u8 *)a->ents + 0xA);
        pa = (s16 *)((u8 *)pa + slot * 16);
        cc = *pa;
    }
    if (cc == 0) {
        n = 0x3C;
    } else {
        n = (s32)(60.0f * ((f32)e->clipLen(cc - 1) / (f32)D_004659B0));
    }
    q->f20 = (s16)(off + 0x28);
    q->f22 = 0x1C;
    q->f28 = 0x1A;
    q->f2A = 0x64;
    q->f24 = (s16)n;
    q->f2C = 0xA;
    q->f2E = 6;
    q->f26 = 6;
    if (mode) {
        cc = ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f0A;
        if (cc == 0) {
            aa = e->curFrame();
            if (lo == 0) {
                bb = aa;
            } else {
                bb = aa - 1;
            }
            k = e->frameCount();
            if (k > 0) {
                fr = 60.0f / (f32)k;
            } else {
                fr = 0.0f;
            }
            sp = fr * (f32)(aa - bb);
            n = (s32)((f32)bb * fr);
            func_291110(a->win, id, 0, 1);
            func_28FCD0(a->win, id, -1, 0);
        } else {
            ci = cc - 1;
            aa = e->clipStart(ci);
            if (lo == 0) {
                bb = aa;
            } else {
                bb = aa - 1;
            }
            e->clipLen(ci);
            fr = 60.0f / (f32)D_004659B0;
            sp = fr * (f32)(aa - bb);
            n = (s32)((f32)bb * fr);
            func_291110(a->win, id, 1, 1);
            func_2907A0(a->win, id, 0.0f);
            func_2905B0(a->win, id, 1.0f, 1.0f, 1.0f, -1.0f);
        }
        ((Ent *)((u8 *)a->ents + slot * 16))->f00 = 0;
        ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f04 = sp;
        ((Ent *)(slot * 16 - (-(s32)(u8 *)a->ents)))->f08 = (s16)n;
    }
    return 0;
}
