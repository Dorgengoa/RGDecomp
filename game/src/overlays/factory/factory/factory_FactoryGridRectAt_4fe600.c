/* rgp:protos */
#define RGP_SELF_factory_FactoryGridRectAt_4fe600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FE600 -- bounds-check a slot index against the
 * caller's table and forward the indexed record to the writer.
 * 80 bytes, 20 instructions, 3 conditional branches, 1 call.
 *
 * * A four-member family found by ranking the OPEN population against ITSELF;
 * `004FE3A0`/`004FE410` hold the table in the object instead of taking it as a
 * parameter, so those two are 5-parameter functions and these two are SEVEN.
 *
 * * The bound test is spelled `n <= i`, NOT `i >= n` -- both emit
 * `slt $1, $10, $7` + `bnel`, and only the "or-equal with the BOUND on the
 * left" token puts it in `$at` ([[at-compare-class]] if/else row 2).
 *
 * ** The two index guards are ONE `if` with a short-circuit `||`; two separate
 * `if`s give a `bgezl` branch-AROUND and a second `return 0` block, 8 bad
 * words at the RIGHT LENGTH.
 *
 * * The call REPLACES the table argument and shifts the last two parameters
 * left by one, which is why `$7` takes the old `$8` and `$8` the old `$9`.
 */

typedef struct Rec {
    u8 pad00[0x8];
} Rec;                                          /* 0x8 */

/*rgp*/

s32 factory_FactoryGridRectAt_4fe600(s32 a, s32 b, Rec *base, s32 n, s32 c, s32 d, s32 i)
{
    if (base == 0) {
        return 0;
    }
    if (i < 0 || n <= i) {
        return 0;
    }
    return factory_FactoryGridRotateRect_4fe650(a, b, &base[i], c, d);
}
