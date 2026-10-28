/* rgp:protos */
#define RGP_SELF_ActInfoColPrmClone_230880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The zero-return block sits BETWEEN the guards and the body: this is one
   `||` chain with an early return, not an `&&` around the body.
   StrPoolIntern_302fd0 takes THREE arguments - the third register is the untouched
   incoming parameter, so no copy is emitted for it here. */

/*rgp*/

struct Pair {
    s32 m00;
    s32 m04;
};

s32 ActInfoColPrmClone_230880(struct Pair *out, struct Pair *s, s32 c, s32 d)
{
    s32 r;

    out->m00 = 0;
    out->m04 = -1;
    if (c == 0 || d == 0 || s == 0 || s->m00 == 0) {
        return 0;
    }
    out->m00 = s->m00;
    out->m04 = s->m04;
    r = ((s32)StrPoolIntern_302fd0(d, s->m00, c));
    out->m00 = r;
    return r != 0;
}
