/* rgp:protos */
#define RGP_SELF_func_0051DAC0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051DAC0 -- `jr $31 / addiu $2, $0, 0x1`.
 *
 * One of the 55 functions spimdisasm auto-named and normal.symbols.txt never
 * sized; brought into the symbol table by scripts/n_unnamed.py.  A constant
 * predicate return is `s32`, not `u8` -- a `u8` return re-masks with
 * `andi $2, $2, 0xFF`, which retail does not have. */
s32 func_0051DAC0(void)
{
    return 1;
}
