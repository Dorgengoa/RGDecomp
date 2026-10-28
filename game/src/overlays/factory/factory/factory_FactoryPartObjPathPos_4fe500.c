/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjPathPos_4fe500 1
#include "port/game_protos.h"
#line 1
/* ====================================================================
 * SESSION 41 (2026-09-02), tag fg41.  CLOSED -- 2 bad -> BYTE-IDENTICAL,
 * 64 words, md5 529de9546762, reproduced twice in one armed run with the
 * committed pre-session source (git show HEAD:) reading its recorded
 * e61539ae7509 / 2 bad in between.  Arming pair held in every run:
 * factory_FactoryStep_5069e0 = MATCH, factory_FactoryRectFrameCorner_509f10 = bad 11 / md5
 * 977182cbe9b7.
 *
 * THE LEVER, carried across from this unit's OWN same-class sibling:
 * factory_FactoryGridRotatePoint_4fe820's residue A (documented in that file as "the SAME
 * CLASS as 004fe500's residue") was closed in session 23 by making the null
 * checks ONE `||` CHAIN WITH ONE `return`.  MECHANISM: mwcc branch-THREADS
 * only the FIRST predecessor of a shared `return K` block -- chaining it
 * straight to the epilogue and duplicating the block's constant into a
 * branch-LIKELY delay slot -- and leaves every later predecessor as a plain
 * branch + nop, which is retail.  That note sat in the sibling for eighteen
 * sessions and was never carried here.
 *
 * Here `d < 0` was the FIRST predecessor of the shared -1 block at
 * 0x004FE568, so mwcc threaded it (`bltzl a3,0x4FE5E0` + duplicated
 * `addiu v0,-1`) where retail keeps `bltz a3,0x4FE568` + nop.  Folding the
 * ENCLOSING `tr != 0` guard into the SAME chain puts a predecessor ahead of
 * `d < 0` and demotes it to the plain branch.
 *
 * MEASURED THIS SESSION, one armed run (the position in the chain IS the
 * discriminator, and it is the only thing that varies across these four):
 *   E1  `tr == 0 || d < 0 || a->f64 <= d`   -> MATCH        <-- installed
 *   E2  `d < 0 || a->f64 <= d || tr == 0`   -> 6 bad   (d first, still threaded)
 *   E3  `d < 0 || tr == 0 || a->f64 <= d`   -> 2 bad   (d first, baseline)
 *   E4  `tr` kept as its OWN `if`           -> +2 words, len 0x108 vs 0x100
 * E4 RE-DERIVES the recorded "flattening the nest (+2 words)" null exactly --
 * and shows what every earlier cell held FIXED: the guard GROUPING.  ~20
 * recorded cells (s23 fz23a/fz23j, s37 F1-F5, s39's re-test, s40's 92-cell
 * knob sweep) varied guard polarity, splitting, goto-to-join, `else` arms,
 * hoisting and pragmas -- never WHICH DISJUNCTS SHARE ONE `||` CHAIN.
 * The s23 verdict "it is not source shape, not goto, not guard polarity, not
 * splitting" is now RETIRED: it is source shape, one level up.
 ==================================================================== */

#include "types.h"

/* factory.bin overlay, 0x004FE500 -- 64 words, EXACT LENGTH, BYTE-IDENTICAL.
 *
 * WHAT MOVED (2026-08-31): naming the element -- `it = &a->f10[c];` with `it`
 * declared BEFORE `tr` -- flipped the register pair at 0x4FE5A8/0x4FE5B4 the
 * right way round (retail lw $2,0x10($20) + sll $3,$18,6; the inline
 * `a->f10[c].f20` spelling gives lw $3 + sll $2).  `(a->f10 + c)->f20` and
 * `(&a->f10[c])->f20` are BOTH the baseline object -- it is the NAMED LOCAL
 * that pays, not the pointer arithmetic.
 *
 * WHAT CLOSED IT (2026-09-02, session 41): the guard grouping -- see the
 * banner at the top of this file.
 */

typedef struct Item {
    u8    pad00[0x20];
    void *f20;
    u8    pad24[0x1C];
} Item;                                         /* 0x40 */

typedef struct Track { u8 pad00[0x14]; } Track;

typedef struct Ctx {
    u8     pad00[0x6];
    s16    f06;
    u8     pad08[0x4];
    s16    f0C;
    u8     pad0E[0x2];
    Item  *f10;
    u8     pad14[0x44];
    void  *f58;
    u8     pad5C[0x4];
    Track *f60;
    s32    f64;
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryPartObjPathPos_4fe500(Ctx *a, void *out, s32 c, s32 d, s32 e)
{
    u8 q[0x10] __attribute__((aligned(16)));
    u8 m[0x40] __attribute__((aligned(16)));
    Item  *it;
    Track *tr;
    s32 n;

    if (c < 0 || a->f0C <= c) {
        return -1;
    }
    tr = a->f60;
    if (tr == 0 || d < 0 || a->f64 <= d) {
        return -1;
    }
    n = a->f06 * 30;
    if (factory_FactoryPartDefPathLerp_4ff710(&tr[d], q, e, n, a->f58) == 0) {
        return -1;
    }
    it = &a->f10[c];
    NodeCalcWorldMatrixThunk_186130(it->f20, m);
    MatMulPoint_1cb8e0(out, m, q);
    return e >= n;
}
