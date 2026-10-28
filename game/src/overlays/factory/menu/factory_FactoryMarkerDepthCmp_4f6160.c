/* rgp:protos */
#define RGP_SELF_factory_FactoryMarkerDepthCmp_4f6160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F6160 -- a three-way float comparator.
 *
 * Pass-27 conversion (session 7): a spimdisasm auto-name this overlay's
 * symbol file never carried.  The shape is a qsort-style comparator: -1 when
 * *a > *b, 1 when *a < *b, 0 when they are equal.
 *
 * ★ `andi $2, $2, 0xFF` at the two inner arms' merge is the `u8` bool idiom,
 * not a mask in the source; the `-1` arm skips it, which is why the andi sits
 * at .L004F618C rather than at the function's tail.
 *
 * ★★ THE GUARD IS `*a > *b`, NOT `!(*a <= *b)`.  Both compile to the same
 * `c.le.s $f0, $f1`, but the negation form lets mwcc fold the guard and the
 * `-1` into ONE `bc1fl` carrying the constant in its delay slot -- 12 words
 * against retail's 14.  Written with the `>` token mwcc emits the PLAIN
 * `bc1t` + `nop` and gives the `-1` its own block, exactly as retail has it.
 * Measured in one probe build: `>`, if/else, assign-then-goto and the
 * else-if chain are all exact; `!(<=)` and a `goto` to a tail block are both
 * two words short.  Same family as the `$at` compare class -- the RELATIONAL
 * OPERATOR TOKEN is load-bearing even where the two spellings are provably
 * the same condition.
 */

s32 factory_FactoryMarkerDepthCmp_4f6160(f32 *a, f32 *b)
{
    u8 lt;

    if (*a > *b) {
        return -1;
    }
    lt = *a < *b;
    return lt;
}
