/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCalcHealAmount_50fab0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x0050FAB0 -- 88 B / 22 words.
 *
 * `#pragma divbyzerocheck on` is what buys retail's `bnez $2 / div / break 0,7`;
 * without it mwcc folds the pair away (measured, build/xa01-arms/v_dbz.py).
 * The div takes `mflo`, so it is a `/` and carries the trap.
 *
 * THREE zero guards but ONE `||` chain: retail's first test is a `beql` whose
 * delay slot holds the shared `daddu $2,$0,$0`, and the other two fall into a
 * single zero block.  Writing them as separate `if`s (0x64) or as a nested
 * `&&` (0x5c) both give the wrong LENGTH -- only the flat three-term `||` is
 * 22 words.  Measured: 8 control-flow shapes x 2 expression spellings.
 *
 * `sll 2 / addu / sll 1` off (x+1) is *10, and the *10 term must be a NAMED
 * LOCAL: written inline the `mult` comes out with its operands swapped
 * (rs = m1E instead of rs = the product) and that is the unit's last bad word.
 * Seven inline respellings -- b->m1E * (..), 10 * (x+1) * .., an (s32) cast,
 * naming m1E instead -- are all ONE identical object.  See
 * [[normal-named-product-local]]: name the PRODUCT, not the operand. */

typedef struct FAB0A { u8 pad00[0x18]; s8 m18; } FAB0A;
typedef struct FAB0B { u8 pad00[0x1E]; s16 m1E; } FAB0B;

s32 insect_InsectBattleCalcHealAmount_50fab0(FAB0A *a, FAB0B *b, s32 mode)
{
    s32 w;

    if (a == 0 || mode == 0 || b == 0) {
        return 0;
    }
    w = (a->m18 + 1) * 10;
    return w * b->m1E / 100;
}
