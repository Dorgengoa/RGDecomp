/* rgp:protos */
#define RGP_SELF_factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0 1
#include "port/game_protos.h"
#line 1
/* ** SESSION 43 (2026-09-02), tag fg43: 6 bad -> BYTE-IDENTICAL, 41 words,
 * md5 e3a3dc7d0430.  Armed run (005069e0 = MATCH / 1a0e9c68216b, 00509f10 =
 * bad 11 / 977182cbe9b7); the cmp-verified identity arm reproduced the
 * recorded 6 bad / ab6ac6ef947f in the same run.
 *
 * ★★★★★★★ THE CLOSE: THIS FUNCTION HAS THREE PARAMETERS AND PASSES THEM
 * STRAIGHT THROUGH.  It was written `(void)`, and that -- not any allocation
 * property -- is the whole residue.
 *
 *     u8 factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0(void *u, s32 n, s32 *ids)
 *     ... r = factory_FactoryMergeInputsMatchType2Maybe_4f4c60(u, n, ids);   (and 004f4a10, 004f47d0)
 *
 * [[merged-callee-signature-oracle]] -- a MERGED definition is ground truth,
 * and here FOUR of them agree, on both sides of this function:
 *   callees (all MERGED, all byte-identical to retail, all three-parameter)
 *     u8 factory_FactoryMergeInputsMatchType2Maybe_4f4c60(void *u, s32 unused, s32 *ids)
 *     u8 factory_FactoryMergeInputsMatchType3Maybe_4f4a10(void *unused, s32 n, s32 *ids)
 *     u8 factory_FactoryMergeInputsMatchType4Maybe_4f47d0(void *u, s32 n, s32 *ids)
 *   caller (MERGED) factory_FactoryMergeInputsMatchBlueprintMaybe_4e9f40:
 *     extern s32 factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0(void *o, s32 a, s32 b);
 *     return factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0(D_00484A60, a, b);
 *
 * AND THE OBJECT SAID SO ALL ALONG.  In retail's 41 words: all three `jal`
 * delay slots are `nop` (idx 28/32/36), so retail marshals NOTHING for the
 * calls -- only possible if the arguments are already home in $4/$5/$6.
 * Retail never writes $4/$5/$6 anywhere in the body.  And retail puts the
 * switch discriminant `t` in **a3 ($7)** -- the first caller-saved register
 * NOT holding a parameter -- where ours put it in **a0 ($4)**, the lowest free
 * one.  scan.py: a0<->a3 explains 6 of 6.
 *
 * ⇒ WHY 58 RECORDED CELLS MISSED IT.  The recorded bound -- "t NEVER rises
 * above $4; mwcc gives this caller-saved temp the lowest free register and no
 * source form raises it" -- is TRUE, and is not the obstacle.  Every one of
 * those 58 cells HELD THE PARAMETER LIST EMPTY, so $4 was always free.  You do
 * not raise the temp; you make the low registers UNAVAILABLE by giving the
 * function the parameters it actually has.  Same reading as
 * [[factory-unused-first-parameter]], measured live on this overlay: ask which
 * VALUE is keeping the parameter register alive, not which spelling picks the
 * register.
 *
 * CONTROLS AND SCOPE, measured in the same run:
 *   A3 -- parameters DECLARED on this function but NOT passed to the callees
 *         (their externs left at `(void)`): byte-identical to the 6-bad
 *         baseline.  So the lever is the PASS-THROUGH reaching the callees,
 *         not the arity of this function alone.
 *   A2 -- third parameter spelled `s32 ids` instead of `s32 *ids`: the SAME
 *         object.  The pointer-vs-integer spelling is free here; `s32 *ids` is
 *         kept because that is what the three merged callees declare.
 *   The `u8` return type and the `extern s32` callee returns are HELD FIXED --
 *         they are what produce the four `andi v0,..,255` narrowing words,
 *         which already matched.
 */

#include "types.h"

/* SESSION 23, lane fz23j -- 6 bad, EXACT LENGTH, UNCHANGED.  Two more cells on
 * the `t lives in $4, retail $7` residue, both MEASURED INERT (each object
 * byte-identical to the 45-cell baseline):
 *  - `t = *(volatile s16 *)&s->f02;` -- the access-site volatile cast that
 *    defeats forward-substitution elsewhere on this image is INERT here.  It
 *    does not even promote t out of the expression-temp pool (contrast
 *    004f0f30, where the same construct moves the value to $8).
 *  - making the switch value the FOURTH PARAMETER:
 *    `u8 factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0(s32 a0, s32 a1, s32 a2, s32 t)` with the body
 *    unchanged.  t stays in $4.  Assigning `t = s->f02` kills the incoming
 *    parameter, so mwcc re-allocates it as a fresh temp -- a parameter cannot
 *    plant a value in $7 unless the INCOMING value is the one used.
 * 47 measured cells, still one live object.
 */

/* factory.bin overlay, 0x004F6AF0 -- 41 words, EXACT LENGTH, 6 bad.  PARKED.
 *
 * RESIDUE: ONE register.  `t` lives in $4 for us and in $7 for retail; every
 * one of the six bad words is that substitution and nothing else --
 *   0x4F6B10 lh   $4,0x2($2)      vs  lh   $7,0x2($2)
 *   0x4F6B20 beq  $4,$3,+0x16     vs  beq  $7,$3,+0x16
 *   0x4F6B2C beq  $4,$3,+0x0F     vs  beq  $7,$3,+0x0F
 *   0x4F6B38 beq  $4,$3,+0x08     vs  beq  $7,$3,+0x08
 *   0x4F6B44 beql $4,$3,+0x10     vs  beql $7,$3,+0x10
 *   0x4F6B4C beql $4,$0,+0x0E     vs  beql $7,$0,+0x0E
 * The compare chain order (4,3,2,1,0), the two `beql`s, the merged `andi
 * $2,$3,0xFF` delay slots and the arm addresses are all already correct.
 *
 * DECLARATION ORDER IS A MEASURED NULL HERE.  All 24 permutations of
 * `Ctx *c / s16 t / Sub *s / u8 r` produce ONE object, byte-identical to the
 * baseline.  So do: `s32 t`, `int t`, dropping `t` and switching on `s->f02`,
 * moving `r = 0` before `t = s->f02`, declaring `t` in an inner block,
 * returning `r` instead of a literal 0 from the null checks, and adding 1-5
 * unused `s32`/`void *` PARAMETERS (the "argument registers are reserved so
 * the temp starts at $7" theory is REFUTED: param1..param5 are all the
 * baseline object).  Pragmas `scheduling off`, `optimize_for_size on`,
 * `opt_dead_assignments off`, `opt_propagation off`, `global_optimizer off`,
 * `opt_lifetimes off` are all inert too.
 * WORSE / LENGTH-BREAKING: `s32 r` (13 bad); an if/else chain (-1 word);
 * merged `case 0: case 1:` labels (+3); `u8 r = 0` initializer (+1);
 * nesting the null checks instead of early-returning (+1); `peephole off`
 * (+5); `opt_common_subs off` (+1).
 * 45 measured cells, 1 live object.  This is not a source-shape axis.
 */

/* ** SESSION 35 (2026-09-02): STILL 6, EXACT LENGTH.  11 new cells; 58 total.
 * ★★ THE MECHANISM IS NOW STATED AS A BOUND, NOT A LIST OF NULLS:
 * `t` NEVER RISES ABOVE $4.  Ten of eleven arms leave it in $4 with the
 * baseline object (md5 ab6ac6ef947f); the only arm that moved it at all moved
 * it DOWN to $3.  mwcc gives this caller-saved temp the LOWEST FREE register
 * and no source form raises it, so every "make room below t" idea is dead.
 *
 * ⇒ THE REGISTER-RESERVATION THEORY IS NOW REFUTED ON CALLEE ARITY TOO, not
 * just on this function's own parameters (which the note above already
 * refuted).  Giving all three callees ONE parameter keeps `t` in $4 (9 bad,
 * exact length); giving them THREE keeps it in $4 (+4 words); giving only
 * factory_FactoryMergeInputsMatchType2Maybe_4f4c60 three keeps it in $4 (+1 word); dropping the prototypes
 * to `extern s32 f();` is byte-identical.  So retail's $7 does NOT come from
 * argument registers being reserved by a call.
 * ALSO INERT (baseline object): the second-def / round-trip family that fires
 * elsewhere on this image -- `t = (s16)t;`, `t = t + 0;`, `t = (s16)(s32)t;`,
 * `t = t | 0;` after the load.  So [[mwcc-propagated-temp-colouring]]'s round
 * trip does NOT reach this web.
 * WORSE: `volatile s16 t;` as a DECLARATION (+2 words, 33 bad -- distinct from
 * the access-site cast above, which is inert); three USED parameters (+3
 * words); an extra live temp `g` competing for the register (+5 words, and it
 * takes `t` DOWN to $3, the only movement ever observed on this web).
 * Retail's $7 means three more caller-saved values were coloured before `t`;
 * nothing in this function's source can create them.
 */

typedef struct Sub {
    u8  pad00[0x2];
    s16 f02;
} Sub;

typedef struct Ctx {
    u8   pad00[0x70];
    Sub *f70;
} Ctx;

extern Ctx *D_00484A48;                         /* _gp - 0x728 */

/*rgp*/
/*rgp*/
/*rgp*/

u8 factory_FactoryMergeInputsMatchByTypeMaybe_4f6af0(void *u, s32 n, s32 *ids)
{
    Ctx *c;
    s16  t;
    Sub *s;
    u8   r;

    c = D_00484A48;
    if (c == 0) {
        return 0;
    }
    s = c->f70;
    if (s == 0) {
        return 0;
    }
    t = s->f02;
    r = 0;
    switch (t) {
    case 0:
        r = 1;
        break;
    case 1:
        r = 1;
        break;
    case 2:
        r = ((unsigned char)factory_FactoryMergeInputsMatchType2Maybe_4f4c60(u, n, ids));
        break;
    case 3:
        r = ((unsigned char)factory_FactoryMergeInputsMatchType3Maybe_4f4a10(u, n, ids));
        break;
    case 4:
        r = ((unsigned char)factory_FactoryMergeInputsMatchType4Maybe_4f47d0(u, n, ids));
        break;
    }
    return r;
}
