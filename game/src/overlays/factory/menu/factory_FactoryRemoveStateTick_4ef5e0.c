/* rgp:protos */
#define RGP_SELF_factory_FactoryRemoveStateTick_4ef5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EF5E0 -- the factory scene's per-frame tick for one
 * phase of the parts window.  532 bytes / 133 words.  ONE WORD SHORT (0x210 vs
 * 0x214); the whole structure otherwise lines up.  Residue note at the bottom.
 *
 * * The first integer parameter is NEVER touched: entry is `lw $2,-0x71C($28)`
 * and the guard is `beqz $5`, so the flag is PARAMETER TWO.  Nothing in the
 * overlay `jal`s here -- it is reached from a dispatch table.
 *
 * * `D_00484A54` is re-read at EVERY use; a call may store to it.  Only the
 * three field loads at the top and the two inside one call-free region CSE.
 *
 * ** THE `||` FOLD.  `ok = (t == 1 || t == 2 || t == 3)` compiles to
 * `addiu $2,$2,-1 / sltiu $6,$2,3` -- a RANGE CHECK, 20 words shorter than
 * retail.  Measured INERT against the fold: operand order (3,2,1 and 2,1,3),
 * C++ `bool`, `(t==1||t==2)||t==3`.  A `switch` does NOT fold (it emits the
 * chain with the ARMS REVERSED -- write the cases descending to get 1,2,3) and
 * neither does an explicit if/else-if chain, which is what retail is.
 *
 * ** The chain writes an INTERMEDIATE `c` and `ok` is its NEGATION: `beql
 * $2,$0` at 0x004EF660 takes the branch (leaving $5 = 1) when the chain
 * produced 0.  `c = ok` in the arms is literal -- retail's arms are
 * `daddu $2,$5,$0`, a copy of ok's register, not a fresh `1`.  `u8 c` is
 * load-bearing: `s32 c` is two words short.
 *
 * * `func_28E170`'s third parameter is `s32`, NOT `u8`: that is what forces the
 * `andi $6,$5,0xFF` PAIR at 0x004EF664/0x66C (the u8 -> int promotion,
 * duplicated by the branch-likely).  Declaring it `u8` loses both words.
 *
 * * `if (c)` / `if (ok)`, never `!= 0`: the `!= 0` TOKEN costs an `andi`
 * ([[mwcc-daddiu-unsigned-narrow]]).
 *
 * * RE-CONFIRMED from factory_FactoryBlueprintConfirm_4fb840: SPLIT THE CALL OUT OF A STORE WHOSE
 * LVALUE CONTAINS IT.  `*func_367EC0() = 1;` puts `addiu $18,$0,1` in the jal's
 * DELAY SLOT, which forces a THIRD callee-saved register and a 0x40 frame;
 * `j = func_367EC0(); *j = 1;` leaves the slot empty, materialises the 1 after
 * the call and drops the frame back to retail's 0x30.  Worth three words.
 *
 * ! RESIDUE, one word: retail has `andi $3,$2,0xFF` at 0x004EF63C -- the u8 `t`
 * copied out of the `lbu` register into a second one, because retail's `lbu`
 * lands in $2 and $2 is then wanted for the compare constants.  Ours puts the
 * constant in $2 and the `lbu` in $3, so no copy is needed.  Retail makes the
 * same copy in the second block (`andi $5,$3,0xFF`, free in a delay slot).
 * INERT against it: all six declaration-order permutations of the locals;
 * `ok = 1` before vs after the load; reading `D_00484A54->f64` directly at each
 * compare instead of via `t`; `t` as u16; `t` as s32 with `(u8)t` at each
 * compare; `t = field & 0xFF`; `(u8)field`; an intermediate `s32 tw`; a second
 * u8 local `k = t` for the 2nd/3rd compares; a `static u8` accessor (NOT
 * inlined -- costs 0x20 bytes).
 *
 * Also still wrong at exact positions: the three head loads schedule as
 * f68/f70/f6C instead of retail's f70/f6C/f68, and the early `return 1` puts
 * the value in the `b`'s delay slot where retail puts `ld $31` there.
 *
 * D_004B2570 is outside the gp window (_gp 0x00485170 +/- 0x8000) so it is a
 * const incomplete array and takes %hi/%lo.
 */

/* ** SESSION 23 (lane fz23c): THE ONE-WORD LENGTH GAP IS CLOSED.  133 words =
 * retail's 0x214, 13 bad.  The word is bought by giving the raw field read an
 * INT-typed local `tw` and narrowing it to the u8 `t` INSIDE THE ELSE BRANCH:
 *     tw = D_00484A54->f64;  ok = 1;
 *     if (tw == 1) c = ok; else { t = (u8)tw; if (t == 2) ... }
 * `t = (u8)tw` is a REGISTER-TO-REGISTER u8 narrow and that IS retail's
 * `andi $3,$2,0xFF` at 0x004EF63C.  The rule underneath: mwcc emits `andi
 * rD,rS,0xFF` for EVERY assignment to a u8 local whose source is a register of
 * another type (`ok = 1` is `andi $3,$6,0xFF`), but NOT for u8-local <- u8-local
 * (`c = ok` is `daddu`), and NOT when the u8 local can be coalesced onto the
 * `lbu` destination itself.  The SAME edit makes the second block (0x004EF690)
 * byte-identical: its copy lands free in retail's `bnel` delay slot.
 *
 * ! RESIDUE, 13 words, three independent groups:
 *   (1) 0x004EF5F4/F8/FC/600 -- the three head loads schedule f68/f70/f6C where
 *       retail is f70/f6C/f68 (retail puts `lw $17,0x68` in the beqz delay slot).
 *   (2) 0x004EF624/628/62C/63C -- a pure $2<->$3 swap in BLOCK ONE ONLY: retail
 *       lbu->$2 and the compare constant->$3, ours the reverse, so our andi is
 *       `andi $3,$3,0xFF` instead of `andi $3,$2,0xFF`.  $2 is shared with `c`
 *       in both builds; whichever web is created first takes $2.  Reading it as
 *       "retail's raw is an anonymous CSE temp, not a named local" is REFUTED:
 *       spelling block 1 as `if (D_00484A54->f64 == 1) {..} else { t =
 *       D_00484A54->f64; ..}` coalesces the copy away and LOSES the word again
 *       (back to 0x210).  MEASURED INERT: declaring `tw` LAST in the local list.
 *   (3) 0x004EF6DC/6F4/6F8/7DC/7E0 -- the epilogue orders `addiu $2,$0,1` before
 *       `ld $31,0x20($29)`; retail is `ld $31` then `addiu $2`, and its early
 *       `return 1` branches to the second of the two labels.  Try a result
 *       variable / tail-merge spelling next.
 */

/* ** SESSION 35 (2026-09-02): BYTE-IDENTICAL, 4 -> 0, 133 words.  MERGED.
 * THE WHOLE EDIT IS ONE STATEMENT MOVE: `ok = 1;` goes ABOVE
 * `tw = D_00484A54->f64;` instead of below it.  That closes residue group (2),
 * the $2<->$3 swap between the `lbu` and the compare constant -- the last of
 * the three groups this file tracked.
 *
 *   baseline  addiu $2,$0,1 / lbu $3,0x64($4) / bne $3,$2 / .. / andi $3,$3
 *   landed    addiu $3,$0,1 / lbu $2,0x64($4) / bne $2,$3 / .. / andi $3,$2
 *
 * ★★ THE LEVER, AND IT IS THE "SHORT-LIVED CONSTANT RANKS LAST" CLASS:
 * the class is REACHABLE, but NOT by touching the constant.  Session 34 proved
 * a constant CANNOT be named into a web (`f32 half`, `s32 neg`, both
 * declaration positions, byte-identical on this image).  What moves it is the
 * STATEMENT ORDER OF AN UNRELATED NEIGHBOUR: which assignment OPENS the block
 * decides which of the two short-lived webs takes $2.  With the load opening
 * the block the compare constant takes $2 and `t` narrows IN PLACE
 * (`andi $3,$3,0xFF`); with `ok = 1;` opening it the load takes $2 and `t`
 * narrows OUT of it (`andi $3,$2,0xFF`), which is retail.  `ok` itself is $5 in
 * both arms -- it is pre-coloured toward its later argument slot and is not
 * competing for $2 at all.  So the handle on a constant-vs-value colouring
 * defect is the THIRD statement standing next to them.
 *
 * ⚠⚠ THIS CELL WAS RECORDED INERT IN THIS VERY FILE.  Session 23 measured
 * "`ok = 1` before vs after the load" against the 13-BAD baseline, where it was
 * byte-identical; two later groups closed underneath it, and at the 4-bad
 * baseline the SAME cell is worth the unit.  An inert cell is inert AT A
 * BASELINE, not forever -- RE-SWEEP A FILE'S OWN RECORDED NULLS after any
 * neighbouring group closes.
 *
 * MEASURED NULL at the 4-bad baseline, all byte-identical to that baseline
 * (10 cells, one object): `1 == tw` reversed compare; `(s32)1` on the constant;
 * `u32 tw`; `t` declared before `tw`; `tw` declared last; a second local `tw2`
 * for the r==2 block; `t = (u8)(tw & 0xFF)`; `t = (u8)(tw + 0)`; the
 * propagated-temp round trip `tw = (s32)(u32)tw;`; the second-def `tw = tw;`.
 * Inverting the guard is 13.  So NAMING, TYPE, DECLARATION ORDER and SECOND-DEF
 * are all dead here and STATEMENT ORDER was the whole axis.
 */

/* ** SESSION 23 (lane fz23i): 13 -> 9 bad, 133 words.  RESIDUE GROUP (1), the
 * three head loads, is CLOSED, and the rule that closed it is general:
 *   ** THE PRE-BRANCH BLOCK IS EMITTED AS A ROTATE-LEFT OF STATEMENT ORDER --
 *   the FIRST statement's instruction is the one that lands in the branch's
 *   DELAY SLOT and the rest follow in source order.
 * Measured at three points on this block:
 *   source (w,v)     -> emitted v, beqz, [w]        (2 loads, 2 bad)
 *   source (w,u,v)   -> emitted u, v, beqz, [w]     (3 loads, 3 bad)
 *   source (v,w,u)   -> emitted w, u, beqz, [v]     = RETAIL, 0 bad
 * The third load `u` is the call argument `D_00484A54->f6C` given its own local
 * so it is HOISTED ABOVE the guard the way retail hoists it; without that local
 * the arg load stays inside the if-body and only two loads can be ordered.
 * $16=w and $17=v are STABLE across all three arms -- the callee-saved colouring
 * here follows DEATH order (w dies last, at 0x004EF7CC), NOT statement order, so
 * the rotation is free of allocation side-effects on this unit.
 *
 * ! RESIDUE, 9 words, two groups, both PARKED:
 *   (2) 0x004EF624/628/62C/63C -- the $2<->$3 swap between the `lbu` and the
 *       compare constant.  This is one instance of a WIDER CLASS seen three
 *       times this session (also both open blocks of factory_FactoryPartPlace_5013f0):
 *       RETAIL RANKS A SHORT-LIVED CONSTANT **LAST** among the live temps and
 *       ours ranks it **FIRST**, so retail's constant takes $4/$5 while the
 *       long-lived values keep $2/$3, and ours is the other way round.  No
 *       source spelling found that reorders it.  The instruction SEQUENCE is
 *       identical in both builds -- only the colouring differs.
 *   (3) 0x004EF6DC/6F4/6F8/7DC/7E0 -- the tail block is ours [addiu $2,$0,1]
 *       [ld $31] and retail [ld $31][addiu $2,$0,1]; both then fill the two
 *       incoming `b` delay slots from the block's FIRST instruction and bump
 *       the target by one, so the whole 5-word group is the ORDER OF THOSE TWO
 *       INSTRUCTIONS and nothing else.  Retail also leaves 0x004EF6F8 a `nop`
 *       (it declines to fill that one), ours fills it.
 *
 */
/* ** SESSION 23 (lane fz23l): 9 -> 4 bad, 133 words.  RESIDUE GROUP (3), the
 * five epilogue words, is CLOSED by ONE TOKEN and the rule is GENERAL:
 *   ** WITH ONE `return` STATEMENT mwcc MATERIALISES THE VALUE INSIDE THE
 *   EPILOGUE, AFTER `ld $31`.  WITH TWO `return 1;` STATEMENTS the two value
 *   sites TAIL-MERGE into a BODY block that is placed BEFORE the epilogue, so
 *   the block reads [addiu $2,$0,1][ld $31] and BOTH incoming `b`s get their
 *   delay slots filled from it.
 * The fix: the early exit becomes `goto done;` and the single `done: return 1;`
 * sits at the end.  That restores retail's [ld $31][addiu $2,$0,1] AND retail's
 * "only ONE predecessor threads" pattern -- 0x004EF6F4 goes back to `b .L7DC`
 * with a nop, 0x004EF6D8 keeps `b .L7E0` with `ld $31` in the slot.
 * SCREEN, run over this image and armed: [ld $31][addiu $2,$0,K] is retail's
 * DOMINANT epilogue (18 files) and [addiu $2][ld $31] the exception (1 file,
 * factory_FactoryMenuStateExit_4ebce0, whose body ends in a store the scheduler filled with).
 *
 * ! RESIDUE, 4 words, ONE group -- 0x004EF624/628/62C/63C, the $2<->$3 swap
 *   between the block-1 `lbu` and its compare constant.  Both builds use TWO
 *   registers: a SHORT slot (const1, then const2/const3, then `c`) and a LONG
 *   slot (the other).  Retail puts `tw` in the SHORT slot $2 and const1 in $3;
 *   ours is the reverse, so our narrow is `andi $3,$3,0xFF` in place where
 *   retail needs `andi $3,$2,0xFF`.  Block 2 (0x004EF690) is byte-identical in
 *   both because $2 is already held by `r` there.
 *   MEASURED INERT THIS SESSION, do not re-sweep: `s32 tw;` declared FIRST in
 *   the local list (byte-identical); the YODA form `if (1 == tw)` on the first
 *   compare (byte-identical -- operand order does NOT reorder web creation
 *   here).  Both are on top of the file's earlier list.
 */
typedef struct Obj {
    u8    pad00[0x64];
    u8    f64;
    u8    pad65[0x3];
    void *f68;
    void *f6C;
    void *f70;
} Obj;

typedef struct Ent {
    u8    pad00[0x70];
    void *f70;
    u8    pad74[0x1C];
    u8    f90;
} Ent;

extern Obj *D_00484A54;                         /* _gp - 0x71C */
extern Ent *D_00484A48;                         /* _gp - 0x728 */

extern u8 D_004B2570[];

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

s32 factory_FactoryRemoveStateTick_4ef5e0(void *self, s32 flag)
{
    void *v;
    void *w;
    void *u;
    s32   tw;
    u8    t;
    u8    ok;
    s32   r;
    s32  *j;
    u8    c;

    v = D_00484A54->f68;
    w = D_00484A54->f70;
    u = D_00484A54->f6C;
    if (flag != 0) {
        UiEntryListSelectByTag_28ea90(u, 0x8908, 1);
    }
    factory_FactoryRemoveNop_4fc8c0();
    factory_FactoryRemoveShowPartInfo_4fc620(D_00484A54);
    ok = 1;
    tw = D_00484A54->f64;
    if (tw == 1) {
        c = ok;
    } else {
        t = (u8)tw;
        if (t == 2) {
            c = ok;
        } else if (t == 3) {
            c = ok;
        } else {
            c = 0;
        }
    }
    if (c) {
        ok = 0;
    }
    r = MenuGridCursorInput_28e170(D_00484A54->f6C, D_004B2570, ok, 0);
    if (r == 2) {
        tw = D_00484A54->f64;
        if (tw == 1) {
            ok = 1;
        } else {
            t = (u8)tw;
            if (t == 2) {
                ok = 1;
            } else if (t == 3) {
                ok = 1;
            } else {
                ok = 0;
            }
        }
        if (ok) {
            factory_FactoryRemoveDialogAnswer_4fc8d0(D_00484A54, -1);
            goto done;
        }
    }
    if (r == 1) {
        factory_FactoryRemoveDialogConfirm_4fcb60(D_00484A54);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x80) != 0 && D_00484A54->f64 == 0) {
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
        j = ((s32 *)FactoryGetRequestPtr_367ec0());
        *j = 1;
        D_00484A48->f90 = 3;
        if (D_00484A48->f70 != 0) {
            StateMachineSetState_28ede0(w, 0x88F4, 0);
        } else {
            StateMachineSetState_28ede0(w, 0x88D6, 0);
        }
        UiFadeWidgetAlpha_290690(v, 0x53, 0.0f, -0.125f, -1.0f);
    } else if (factory_FactoryRemoveWaitRequest_4fcc50(D_00484A54) != 0) {
        StateMachineSetState_28ede0(w, 0x8958, 0);
    }
done:
    return 1;
}
