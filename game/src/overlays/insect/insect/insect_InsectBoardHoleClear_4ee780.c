/* rgp:protos */
#define RGP_SELF_insect_InsectBoardHoleClear_4ee780 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EE780 -- 24 instructions.  Three parameters held across the
 * guard call, then one read-modify-write of a flag byte at +0x13B of a
 * five-byte-strided element.  The product is a NAMED LOCAL: written inline
 * mwcc canonicalises `c * 5 + a` into `a + c * 5` and the `addu` operands come
 * out swapped -- the integer case of [[normal-named-product-local]]. */

/*rgp*/

void insect_InsectBoardHoleClear_4ee780(s32 a, s32 b, s32 c)
{
    s32 t;
    u8 *p;

    if (insect_InsectBoardInBounds_4efac0((void *)a, (long long)b, (long long)c) != 0) {
        t = c * 5;
        p = (u8 *)(b + (t + a));
        p[0x13B] = p[0x13B] & 0xFB;
    }
}
