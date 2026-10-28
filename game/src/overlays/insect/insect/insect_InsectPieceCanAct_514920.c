/* rgp:protos */
#define RGP_SELF_insect_InsectPieceCanAct_514920 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514920 -- 132 bytes.  A five-term `||` chain whose body is
 * `return 0`, NOT a five-term `&&` chain whose body is `return 1`.
 *
 * ★ The two spell the same predicate and short-circuit identically, but only
 * the `||` form reaches retail's code.  With `||` the FIRST term takes
 * `bnel $2,$0,<epilogue>` with the shared `daddu $2,$0,$0` in the annulled
 * slot, terms 2-4 take a plain `bnez`/`beqz` into that shared block, and the
 * LAST term's false exit becomes `beql $2,$0,<epilogue>` with
 * `addiu $2,$0,1` -- the trailing `return 1` -- annulled: two words.  Written
 * with `&&`, mwcc materialises the final test as a BOOLEAN
 * (`xor $2,$2,$0` / `sltiu $2,$2,1`) plus a join `b`, one word long, and that
 * residue survives the whole 486-variant pragma namespace. */

/*rgp*/

s32 insect_InsectPieceCanAct_514920(void *o)
{
    if (insect_InsectPieceTestStatus_513280(o, 1) != 0 ||
        insect_InsectPieceTestStatus_513280(o, 4) != 0 ||
        insect_InsectPieceTestStatus_513280(o, 0x1B) == 0 ||
        insect_InsectPieceTestStatus_513280(o, 0x1D) != 0 ||
        insect_InsectPieceTestStatus_513280(o, 0x1E) != 0) {
        return 0;
    }
    return 1;
}
