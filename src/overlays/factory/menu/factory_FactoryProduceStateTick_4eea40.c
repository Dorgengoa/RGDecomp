#include "types.h"

/* factory.bin overlay, 0x004EEA40 -- 88 B / 22 words, 1 branch, 3 calls.
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
 * This member is the if/else cell: BOTH arms are calls, there is ONE trailing
 * `return 1`, and the duplicated `ld $31` rides the `b` out of the then-arm.
 * `bnel $2,$3` carries `lw $4,-0x710($28)` in the annulled slot -- the
 * else-arm's argument -- so both arms pass the same global, written once each.
 * `D_004B2570` is outside the gp window; `extern const u8 []` gives the
 * `lui 0x4B / addiu 0x2570` pair (spelling from factory_FactoryMenuOpen_4ec5e0).
 */

typedef struct Panel {
    u8    pad00[0x88];
    void *f88;                                  /* +0x88 */
} Panel;

extern const u8 D_004B2570[];
extern Panel   *D_00484A60;                     /* _gp - 0x710 */

extern s32  func_28E170(const void *a, const void *b, s32 c, s32 d);
extern void factory_FactoryProduceResultStep_4f7100(Panel *o);
extern void factory_FactoryProducePollResult_4f74d0(Panel *o);

s32 factory_FactoryProduceStateTick_4eea40(void)
{
    if (func_28E170(D_00484A60->f88, D_004B2570, 0, 0) == 1) {
        factory_FactoryProduceResultStep_4f7100(D_00484A60);
    } else {
        factory_FactoryProducePollResult_4f74d0(D_00484A60);
    }
    return 1;
}
