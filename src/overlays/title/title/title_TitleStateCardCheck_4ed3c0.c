#include "types.h"

/* title.bin overlay, 0x004ED3C0 -- the save/load slot state machine.
 *
 * Driven by the s16 state at gp-0xF50 (D_00484220) with a two-entry record
 * array D_004F19F0 (0x20 bytes each) holding the per-slot save headers.
 *
 * The dispatch is a compare CHAIN, not a jump table -- the values are 0..6
 * plus 0x3E8/0x3E9, too sparse for one -- so the source case order is the
 * REVERSE of the tested order (0x3E8, 0x3E9, 6, 5, 2, 4, 1, 3, 0).  The
 * `beql $3,$2,.L004ED790` delay slot carries `lw $4,-0xF48($28)`, a CASE
 * BODY's load, which is the switch/if-chain discriminator.
 *
 * D_004F1A0C and D_004F1A2C are entry 0 and entry 1's +0x1C word, but the
 * reference materialises each with its own %hi/%lo, so the source names them
 * as separate objects.  They are declared as UNSIZED ARRAYS: they sit at
 * 0x4F1A0C, far outside the gp window 0x47D170..0x48D170, so a plain 4-byte
 * extern would take %gp_rel and die at LINK time -- and `const` is not
 * available here because they are written.  An incomplete array type is never
 * small data, which buys the same %hi/%lo without the const.
 *
 * BYTE-IDENTICAL (session 9; sessions 3f-8 left it parked at len -2 with a
 * two-axis negative).  The close came from the worked-example census
 * (scripts/t_census.py): EventPlayerIsIdle_250ba0 is the ONE matched unit with the
 * cond/nop/b/nop shape on an ADJACENT taken edge, and reading it gave the
 * mechanism -- see item 2 below and the inline comments.
 *
 * 1. FOUR WORDS, SOLVED: the `ok` flag.  Retail sets `addiu $16,$0,1` in
 *    func_37BAB0's delay slot, compares `func_37B8C0()` against it, and then
 *    tests `beql $16,$0,.L004ED788` -- a test of a provably-constant 1 that
 *    costs the beql, its delay-slot `addiu $2,$0,0x3E9`, and the separate
 *    `b/sh` block that constant feeds.  THE FIX IS A SECOND REACHING
 *    DEFINITION: one redundant `ok = 1` inside either arm of the
 *    `func_37B8C0() == ok` test.  mwcc's constant propagation gives up when a
 *    variable has two definitions EVEN THOUGH BOTH ARE THE SAME CONSTANT, and
 *    it then keeps the value in a callee-saved register and emits the
 *    provably-false test.  Nothing about the storage class reaches it:
 *    `s32`, `u8`, `register`, `volatile s32` (that one goes to a STACK SLOT,
 *    which is worse), passing it as an argument, `< 1` for `== 0` and a
 *    guarded `if (g) ok = 1;` before the calls are all measured and all fold.
 *    A 12-variant probe TU settled it in one build.
 *    ⇒ Generalises: when retail tests something you can prove constant, give
 *    the variable a second assignment rather than reaching for a storage class.
 * 2. THE EMPTY `if` ARM, SOLVED (session 9): retail emits
 *    `bnez $2,.L004ED5CC / nop / b .L004ED640 / nop` -- the body is BRANCHED
 *    TO and the skip arm is a jump-only block.  46 syntactic spellings
 *    collapsed it to one inverted `beqzl` because a block that is BORN a
 *    `goto` is branch-threaded away.  A block that BECOMES jump-only during
 *    optimisation survives: the redundant `ok = 1;` before `goto joined;`
 *    is deleted by dead-store elimination AFTER layout, leaving the naked
 *    `b` (EventPlayerIsIdle_250ba0: same mechanism via a CSE-emptied `return 1`).
 *    Two more layout facts finished the function: the `ok == 0` arm is a
 *    SEPARATE cold-block copy at the end of the case (okbad:, not shared
 *    with bad:), and the case-6 func_376B20 guard falls through into the
 *    6-arm (polarity flip).
 *
 * WHAT DID MOVE IT, all structural and all worth reusing:
 *  - the two arms of the `func_37B8C0() == ok` test are NOT the same code:
 *    one computes the destination address BEFORE the two calls and the other
 *    AFTER.  Written identically, mwcc merges the blocks and TWO CALLS
 *    disappear -- which `ogap.py` catches instantly as a call-count mismatch.
 *  - the guard chain before the 0xC9/0xCB/0xCA dispatch is the shared-goto
 *    recipe: four guards `goto bad`, and `bad` sits PHYSICALLY BETWEEN the
 *    guards and the body, which then needs its own label.  That reproduced
 *    retail exactly, including the last guard inverting to `blezl` (branch
 *    INTO the body) and its delay slot carrying the body's `addiu $2,$0,0x1`.
 *  - `D_00484224 != 1` had to be written `== 1` with the arms swapped;
 *    retail branches AWAY on `!=`, so the `== 1` arm is the fall-through.
 *  - the slot local is `s32`, not `s8`.  `lb` already sign-extends; an `s8`
 *    local makes mwcc re-normalise with `dsll32`/`dsra32` (2 words).
 */

typedef struct Rec_title_FUN_004ed3c0 {
    u8 pad000[0x1C];
    s32 field01C;                  /* +0x1C */
} Rec_title_FUN_004ed3c0;

typedef struct Sys_title_FUN_004ed3c0 {
    u8 pad000[0x20];
    u8 bit0 : 1;
    u8 bit1 : 1;
} Sys_title_FUN_004ed3c0;

typedef struct Pl_title_FUN_004ed3c0 {
    u8 pad000[0x4EC];
    s16 field4EC;                  /* +0x4EC */
} Pl_title_FUN_004ed3c0;

typedef struct Blk_title_FUN_004ed3c0 {
    s32 field000;
    s32 field004;
    s32 field008;
    u8 pad00C[0xA4];
} Blk_title_FUN_004ed3c0;          /* 0xB0 -- frame 0xE0 with 0x30 of saves */

extern s16 D_00484220;             /* gp-0xF50, the state */
extern s8 D_00484224;              /* gp-0xF4C, the slot */
extern s32 D_00484228;             /* gp-0xF48, the mode */
extern void *D_00484174;           /* gp-0xFFC */
extern void *D_004841E0;           /* gp-0xF90 */
extern Sys_title_FUN_004ed3c0 *D_004841E8;   /* gp-0xF88 */
extern s32 D_004841FC;             /* gp-0xF74 */
extern s32 D_00484200;             /* gp-0xF70 */
extern const u8 D_004B2570;

extern Rec_title_FUN_004ed3c0 D_004F19F0[];
extern Rec_title_FUN_004ed3c0 D_004F1A10[];
extern s32 D_004F1A0C[];
extern s32 D_004F1A2C[];

extern void func_1319A8(void *dst, void *src, s32 n);
extern s32 func_1839F0(const void *a, s32 b);
extern s32 func_1CF6C0(void *a);
extern void func_1CF730(void *a, s32 b, f32 x, f32 y, f32 z);
extern void *func_1F5BE0(void);
extern void func_28AA00(void *p);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void func_373110(void *a, s32 b);
extern s32 func_3733D0(void *a);
extern void func_375A10(void *a, s32 b);
extern void func_3761D0(void *a);
extern s32 func_376220(void *a, s32 b);
extern u8 func_376280(s32 a, s32 b);
extern void func_376B20(s32 a);
extern void func_376BF0(s32 a, void *b, void *c);
extern void func_377180(void *a);
extern u8 func_37B8C0(void);
extern s32 func_37B920(void);
extern s32 func_37B950(void);
extern u8 func_37B9B0(s32 a);
extern s32 func_37BAA0(void);
extern s32 func_37BAB0(void);
extern void func_37BAC0(s32 a);
extern void func_37BB70(void);
extern void title_TitleSceneOverlayModeOff_4eaa00(void);
extern void title_TitleSceneOverlayModeOn_4eaa40(void);
extern void title_TitleAnySaveExists_4ed380(void);
extern void title_TitleLoadYesNoCursorBob_4edc00(s32 a, s32 b, s32 c);
extern void title_TitleLoadShowMsg_4eeb60(s32 a);
extern void title_TitleSaveSysInit_4ef2b0(void);
extern Pl_title_FUN_004ed3c0 *title_TitleGetSaveCtx_4ef380(void);
extern void title_TitleSetNoAnalogPause_4f13b0(s32 a);

s32 title_TitleStateCardCheck_4ed3c0(void *unused, s32 first)
{
    Blk_title_FUN_004ed3c0 blk;
    Rec_title_FUN_004ed3c0 *e;
    Pl_title_FUN_004ed3c0 *p;
    s32 ok;
    s32 h;
    s32 r1;
    s32 r2;
    s32 i;
    s32 slot;
    s32 *q;

    if (first != 0) {
        title_TitleSceneOverlayModeOn_4eaa40();
        D_00484220 = 0;
        D_00484224 = 0;
        func_3761D0(&D_004F19F0[0]);
        D_004F1A0C[0] = 0;
        func_3761D0(&D_004F1A10[0]);
        D_004F1A2C[0] = 0;
        title_TitleSaveSysInit_4ef2b0();
        func_37BAC0(0);
        title_TitleLoadShowMsg_4eeb60(0xC8);
        title_TitleSetNoAnalogPause_4f13b0(1);
        return 1;
    }
    func_37BAC0(0);
    switch (D_00484220) {
    case 0:
    case 3:
        slot = D_00484224;
        e = &D_004F19F0[slot];
        func_3761D0(e);
        e->field01C = 0;
        slot = D_00484224;
        p = title_TitleGetSaveCtx_4ef380();
        if (slot >= 0 && slot < 2) {
            p->field4EC = slot;
        }
        func_375A10(title_TitleGetSaveCtx_4ef380(), 0);
        D_00484220 = D_00484220 + 1;
        break;
    case 1:
    case 4:
        if (func_37BAA0() != 0) {
            if (func_37B9B0(0) != 0 && func_37B950() != 0) {
                func_37B8C0();
            }
            func_375A10(title_TitleGetSaveCtx_4ef380(), 3);
            D_00484220 = D_00484220 + 1;
        }
        break;
    case 2:
    case 5:
        if (func_37BAA0() != 0) {
            ok = 1;
            h = func_37BAB0();
            func_1319A8(&D_004F19F0[D_00484224], (void *)h, 0x1C);
            if (func_376280(h, 0) != 0) {
                goto have;
            }
            /* REDUNDANT -- ok is already 1.  The dead second definition is
             * what keeps this block from being branch-threaded into the
             * beqz: mwcc lays [ok=1; b joined], DSE deletes the store, and
             * the naked `b` survives as retail's `bnez / nop / b / nop`
             * (EventPlayerIsIdle_250ba0 is the matched worked example; a bare
             * `goto` here is threaded and the 4-word form collapses). */
            ok = 1;
            goto joined;
have:
            if (func_37B950() != 0) {
                if (func_37B8C0() == ok) {
                    D_004F1A0C[D_00484224 * 8] = func_3733D0(title_TitleGetSaveCtx_4ef380());
                    /* A SECOND REACHING DEFINITION, and it is what stops mwcc
                     * folding `ok` to the constant 1.  Retail keeps `ok` in
                     * $16, copies it to $2 for this compare, and still emits
                     * the provably-false `beql $16,$0` test below -- 4 words
                     * that no storage class or spelling of a single-definition
                     * local reproduces.  A probe TU settled it: one redundant
                     * `ok = 1` inside EITHER arm of this test gives the
                     * variable two definitions and mwcc stops propagating,
                     * even though both definitions are the same constant. */
                    ok = 1;
                } else {
                    /* the address is computed BEFORE the two calls in this arm
                     * and AFTER them in the other -- that asymmetry is what
                     * stops mwcc merging the blocks, and retail emits both
                     * call pairs. */
                    q = &D_004F1A0C[D_00484224 * 8];
                    *q = func_3733D0(title_TitleGetSaveCtx_4ef380());
                }
            }
joined:
            if (ok == 0) {
                goto okbad;
            } else if (D_00484224 == 1) {
                D_00484228 = 1;
                D_00484220 = 6;
                h = func_37B920();
                r1 = func_376220(&D_004F19F0[0], h);
                r2 = func_376220(&D_004F1A10[0], h);
                if (r1 == 0) {
                    goto bad;
                }
                if (r2 == 0) {
                    goto bad;
                }
                if (D_004F1A0C[0] > 0) {
                    goto bad;
                }
                if (D_004F1A2C[0] <= 0) {
                    goto good;
                }
bad:
                D_00484220 = 0x3E9;
                goto casedone;
good:
                {
                    if (r1 == 1 && r2 == 1) {
                        title_TitleLoadShowMsg_4eeb60(0xC9);
                    } else if (r1 == 2 && r2 == 2) {
                        title_TitleLoadShowMsg_4eeb60(0xCB);
                    } else {
                        func_28AA00(&blk);
                        if (r1 == 2) {
                            blk.field000 = 1;
                        }
                        if (r2 == 2) {
                            blk.field000 = 2;
                        }
                        blk.field008 = func_37B920();
                        func_376BF0(0xCA, D_00484174, &blk);
                    }
                    title_TitleLoadYesNoCursorBob_4edc00(D_00484228, 1, 1);
                    title_TitleGetSaveCtx_4ef380()->field4EC = 0;
                }
casedone: ;
            } else {
                D_00484224 = 1;
                D_00484220 = 3;
            }
            break;
            /* The ok==0 arm is this SEPARATE copy at the end of the case --
             * cold-block layout, NOT shared with bad: (retail keeps both
             * copies; the beql at `joined` absorbs this block's li into its
             * delay slot and lands on the sh). */
okbad:
            D_00484220 = 0x3E9;
        }
        break;
    case 6:
        title_TitleLoadYesNoCursorBob_4edc00(D_00484228, 0, 1);
        if (D_004841E8->bit1 == 0) {
            func_377180(&D_00484228);
            if (func_1839F0(&D_004B2570, D_00484200) != 0 ||
                (func_1839F0(&D_004B2570, D_004841FC) != 0 && D_00484228 == 1)) {
                if (func_1839F0(&D_004B2570, D_00484200) != 0) {
                    func_376B20(6);
                } else {
                    func_376B20(5);
                }
                title_TitleLoadShowMsg_4eeb60(0xC8);
                title_TitleLoadYesNoCursorBob_4edc00(D_00484228, 0, 0);
                D_00484220 = 0;
                D_00484224 = 0;
                func_3761D0(&D_004F19F0[0]);
                D_004F1A0C[0] = 0;
                func_3761D0(&D_004F1A10[0]);
                D_004F1A2C[0] = 0;
            } else if (func_1839F0(&D_004B2570, D_004841FC) != 0) {
                title_TitleLoadYesNoCursorBob_4edc00(D_00484228, 0, 0);
                func_376B20(5);
                D_00484220 = 0x3E9;
            }
        }
        break;
    case 0x3E9:
        func_1CF730(func_1F5BE0(), 0xA, 0.0f, 0.0f, 0.0f);
        D_00484220 = 0x3E8;
        break;
    case 0x3E8:
        if (func_1CF6C0(func_1F5BE0()) != 0) {
            title_TitleLoadShowMsg_4eeb60(-1);
            title_TitleLoadYesNoCursorBob_4edc00(D_00484228, 0, 0);
            func_37BB70();
            title_TitleSceneOverlayModeOff_4eaa00();
            title_TitleAnySaveExists_4ed380();
            i = 0;
            do {
                func_373110(&D_004F19F0[i], i);
                i = i + 1;
            } while (i < 2);
            title_TitleSetNoAnalogPause_4f13b0(0);
            func_28EDE0(D_004841E0, 4, 1);
        }
        break;
    }
    return 1;
}
