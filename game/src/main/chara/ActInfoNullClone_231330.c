/* rgp:protos */
#define RGP_SELF_ActInfoNullClone_231330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Mirror of ActInfoColPrmClone_230880 with the guard and the rebuilt field on m04. */

/*rgp*/

struct Pair {
    s32 m00;
    s32 m04;
};

s32 ActInfoNullClone_231330(struct Pair *out, struct Pair *s, s32 c, s32 d)
{
    s32 r;

    out->m00 = -1;
    out->m04 = 0;
    if (c == 0 || d == 0 || s == 0 || s->m04 == 0) {
        return 0;
    }
    out->m00 = s->m00;
    out->m04 = s->m04;
    r = ((s32)StrPoolIntern_302fd0(d, s->m04, c));
    out->m04 = r;
    return r != 0;
}
