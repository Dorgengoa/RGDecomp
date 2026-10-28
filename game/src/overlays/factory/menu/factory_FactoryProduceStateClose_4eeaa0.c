/* rgp:protos */
#define RGP_SELF_factory_FactoryProduceStateClose_4eeaa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EEAA0 -- 108 B / 27 words, 2 branches, 2 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy01.
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
 * This member is the SWITCH cell and the one that proved the key: `beql $2,$0`
 * INTO the body with the body's own `addiu $2,$0,-1` annulled, then
 * `b <tail> / ld $31, 0x10` on the default fall-through.  The early-return and
 * empty-else spellings are the two negatives recorded above, both measured
 * here and on the twin 004EEB10.
 *
 * * Both context fields are read into locals BEFORE the `start` guard, and
 *   mwcc emits the two loads in REVERSE source order -- declare/assign 0x84
 *   FIRST to get retail's `lw $4,0x8C` ahead of the `lw $16,0x84` that rides
 *   the (non-likely, always-executed) `beqz $5` delay slot.
 * * 0x84 is the handle that lives across func_28EDE0, so it takes $16.
 */

typedef struct Panel {
    u8    pad00[0x84];
    void *f84;                                  /* +0x84 */
    u8    pad88[0x4];
    void *f8C;                                  /* +0x8C */
} Panel;

extern Panel *D_00484A60;                       /* _gp - 0x710 */
extern s32    D_00484B54;                       /* _gp - 0x61C */

/*rgp*/
/*rgp*/

s32 factory_FactoryProduceStateClose_4eeaa0(s32 unused, s32 start)
{
    void *win;
    void *hud;

    win = D_00484A60->f84;
    hud = D_00484A60->f8C;
    if (start != 0) {
        D_00484B54 = 0;
    }
    switch (D_00484B54) {
    case 0:
        D_00484B54 = -1;
        StateMachineSetState_28ede0(hud, 0x88CC, 0);
        UiSetWidgetVisible_290010(win, 0x86, 0, -1);
        break;
    }
    return 1;
}
