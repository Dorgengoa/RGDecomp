#include "types.h"

/* factory.bin overlay, 0x004EEF20 -- 88 B / 22 words, 1 branch, 2 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy01 seed batch.
 *
THE FAMILY KEY, measured this lane (tag fy01) over five members.  The two
 * `ld $31` sites are NOT two source `return` statements tail-merged.  There is
 * always exactly ONE trailing `return K`; what varies is the BLOCK LAYOUT, and
 * the listing tells you which of two constructs produced it:
 *
 *   NO `b` to the shared tail -- the guard branches straight to it (`beql`
 *   /`bnel` PAST the body, the annulled slot holding `ld $31`):
 *       -> `if (cond) { body } return K;`        [004EF530, 004EEF20]
 *       -> or `if (c) {A} else {B} return K;`    [004EEA40]
 *
 *   A `b <tail>` WITH `ld $31` in its delay slot, and the guard `beql`-ing
 *   INTO the body with the body's own first instruction annulled:
 *       -> `switch (v) { case K0: body; break; } return K;`
 *                                                [004EEAA0, 004EEB10]
 *
 * TWO MEASURED NEGATIVES, both at the RIGHT LENGTH or one word off:
 *   * an explicit early `return K;` guard gives the right LAYOUT but inverts
 *     the epilogue pair -- it duplicates `addiu $2,$0,K` and leaves `ld $31`
 *     leading the shared tail, i.e. exactly 3 bad words (and on a unit with no
 *     callee-saved register, 004EF530, it is 2 words LONG instead);
 *   * an empty then-arm with the body in an `else` is INERT -- mwcc folds it
 *     back to the plain `if`, one word SHORT (no `b`).
 *
 * This member is the guarded-body cell: no `b`, so ONE trailing `return 1`.
 * `addiu $2,$2,-1 / sltiu $1,$2,2` is mwcc's range fold of the `||` join
 * `mode == 1 || mode == 2` -- the factory `||` lever.  The call result must be
 * NAMED, otherwise the compare has no value to destroy in place.
 * The global is RE-LOADED for the body (`lw $2,-0x728($28)` twice) because $2
 * is caller-saved across func_28E170: two separate `D_00484A48->` reads in
 * source, not one named local.  `ori $5,$0,0x88FE` is a plain `s32` id in
 * [0x8000,0xFFFF].
 */

typedef struct Ctx {
    u8    pad00[0x84];
    void *f84;                                  /* +0x84 */
    void *f88;                                  /* +0x88 */
} Ctx;

extern const u8 D_004B2570[];
extern Ctx     *D_00484A48;                     /* _gp - 0x728 */

extern s32  func_28E170(const void *a, const void *b, s32 c, s32 d);
extern void func_28EDE0(void *ctx, s32 id, s32 a);

s32 factory_FactoryBlueprintViewTick_4eef20(void)
{
    s32 mode;

    mode = func_28E170(D_00484A48->f84, D_004B2570, 0, 0);
    if ((mode == 1) || (mode == 2)) {
        func_28EDE0(D_00484A48->f88, 0x88FE, 0);
    }
    return 1;
}
