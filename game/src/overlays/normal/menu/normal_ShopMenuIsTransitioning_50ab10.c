/* rgp:protos */
#define RGP_SELF_normal_ShopMenuIsTransitioning_50ab10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050AB10 -- `lh $4,gp / addiu $3,$0,2 / beq $4,$3,L1 /
 * daddu $2,$0,$0 / addiu $3,$0,1 / bne $4,$3,L2 / nop / L1: addiu $2,$0,1 /
 * L2: jr`.  A two-value `||` test whose result is a variable, not a folded
 * predicate -- the `r = 0; if (...) { r = 1; }` shape that normal_FieldHudWidget86IsOpen_4f9490
 * needed, here with an `s32` result (`daddu`/`addiu`) rather than a `u16`.
 * ⚠ It is neither `||` NOR a switch.  `v == 2 || v == 1` is RANGE-OPTIMISED
 * into `addiu $3,$3,-1 / sltiu $1,$3,2` (three words short); a `switch` on
 * cases 1,2 and every if/else-if spelling are one word LONG.  Retail's two
 * guards jump to a SHARED `r = 1` block that the second guard falls into --
 * the cold-block `goto`, and it is the only one of ten spellings that is
 * exact (scripts/n_oprobe.py).
 * The global is read ONCE into a local; both compares reuse `$4`.
 * One of the 55 unnamed functions. */
extern s16 D_00480638;

s32 normal_ShopMenuIsTransitioning_50ab10(void)
{
    s32 v;
    s32 r;

    v = D_00480638;
    r = 0;
    if (v == 2) {
        goto one;
    }
    if (v != 1) {
        goto done;
    }
one:
    r = 1;
done:
    return r;
}
