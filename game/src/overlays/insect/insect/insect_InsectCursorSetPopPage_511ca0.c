/* rgp:protos */
#define RGP_SELF_insect_InsectCursorSetPopPage_511ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00511CA0 -- 72 bytes, 18 instructions, leaf.  A downward scan over
 * eight words at +0xC: the first non-zero entry is cleared and the value two
 * words below it is returned -- except at index 0, where the just-cleared word
 * itself is re-read through the pointer the store used.
 *
 * TWO pointer locals, and `q = p + 3` must be computed BEFORE the guard: the
 * test loads through `p` with the 0xC displacement while both `*q` accesses go
 * through `q`, and hoisting `q` out of the `if` is what puts it in the `beqz`
 * delay slot (inside the `if` mwcc folds the store back onto `p[3]`, annuls
 * the loop decrement instead, and pays a join `b`/`nop` -- 14 bad words).
 * The result is a NAMED local with a `break`, not two early returns: an early
 * return leaves `$2 = 0` between the loop and the epilogue and costs the
 * extra join.  Declaration order is INERT (all four orders, object a52513bd).
 */

s32 insect_InsectCursorSetPopPage_511ca0(s32 *a)
{
    s32 *p;
    s32 *q;
    s32 i;
    s32 r;

    r = 0;
    for (i = 7; i >= 0; i--) {
        p = a + i;
        q = p + 3;
        if (p[3] != 0) {
            *q = 0;
            if (i > 0) {
                r = p[2];
            } else {
                r = *q;
            }
            break;
        }
    }
    return r;
}
