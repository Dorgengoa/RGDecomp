#include "types.h"
/* insect 0x0050FC50 -- 140 bytes.  Three null guards, and their SHAPES fix the
 * layout:
 *   a -> `beqz` into a shared cold block,
 *   b -> `beql` straight to the epilogue with `daddu $2,$0,$0` annulled,
 *   c -> `bnel` INTO the body with the body's first instruction annulled,
 * with the shared `return 0` block sitting BETWEEN the guards and the body.
 * ALL THREE guards are `goto zero;` at one shared label placed there; the
 * second guard's `beql` is mwcc's own doing, and spelling that guard as a
 * real `return 0;` instead costs TWO words (see the report's lever 1).
 * `insect_InsectBattleCalcBaseDamage_50ffb0` is entered with $4/$5 still holding the incoming
 * parameters and $6 loaded from +0x6A in c's annulled delay slot, so it takes
 * THREE arguments.
 * The tail is the ACCUMULATOR form: retail's `bgtz` with an EMPTY delay slot
 * skips to a common exit that already holds `r`. */

typedef struct C {
    u8  pad00[0x6A];
    s16 m6A;                        /* +0x6A */
} C;

extern s32  insect_InsectBattleCalcBaseDamage_50ffb0(void *a, void *b, s16 v);
extern s32  insect_InsectBattleCalcSpecialDamage_50fce0(void *a, void *b, s32 s, C *c);
extern void insect_InsectPieceSetStatus_5132d0(void *a, s32 k);

s32 insect_InsectBattleSpecialDamage_50fc50(void *a, void *b, C *c)
{
    s32 r;

    if (a == 0) {
        goto zero;
    }
    if (b == 0) {
        goto zero;
    }
    if (c != 0) {
        goto ok;
    }
zero:
    return 0;
ok:
    r = insect_InsectBattleCalcSpecialDamage_50fce0(a, b, insect_InsectBattleCalcBaseDamage_50ffb0(a, b, c->m6A), c);
    if (r <= 0) {
        insect_InsectPieceSetStatus_5132d0(a, 0x10);
        r = 0;
    }
    return r;
}
