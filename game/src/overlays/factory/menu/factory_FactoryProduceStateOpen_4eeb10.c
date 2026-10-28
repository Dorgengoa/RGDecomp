/* rgp:protos */
#define RGP_SELF_factory_FactoryProduceStateOpen_4eeb10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EEB10 -- 116 B / 29 words, 2 branches, 3 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy01.  TWIN of
 * factory_FUN_004EEAA0 over the other latch flag.
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
 * Same SWITCH cell as the twin.  Here it is the 0x8C handle that lives across
 * func_290010 / factory_FactoryProduceOpen_4f77a0, so 0x8C takes $16 and 0x84 rides the
 * `beqz $5` delay slot -- which register is callee-saved follows from WHICH
 * field is used after the call, while the EMISSION order of the two loads is
 * the reverse of source order (assign 0x84 first).
 * `factory_FactoryProduceOpen_4f77a0` is passed the GLOBAL, re-read as `lw $4,-0x710($28)`,
 * not the named local.
 */

typedef struct Panel {
    u8    pad00[0x84];
    void *f84;                                  /* +0x84 */
    u8    pad88[0x4];
    void *f8C;                                  /* +0x8C */
} Panel;

extern Panel *D_00484A60;                       /* _gp - 0x710 */
extern s32    D_00484B50;                       /* _gp - 0x620 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryProduceStateOpen_4eeb10(s32 unused, s32 start)
{
    void *win;
    void *hud;

    win = D_00484A60->f84;
    hud = D_00484A60->f8C;
    if (start != 0) {
        UiSetWidgetVisible_290010(win, 0x86, 1, -1);
        factory_FactoryProduceOpen_4f77a0(D_00484A60);
        D_00484B50 = 0;
    }
    switch (D_00484B50) {
    case 0:
        D_00484B50 = -1;
        StateMachineSetState_28ede0(hud, 0x89F8, 0);
        break;
    }
    return 1;
}
