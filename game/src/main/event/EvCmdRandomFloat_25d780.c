/* rgp:protos */
#define RGP_SELF_EvCmdRandomFloat_25d780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdRandomFloat_25d780(void *a0, s32 mode)
{
    void *q;
    f32 r1;
    f32 f;

    if (mode != 2) {
        return 0;
    }
    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = TaggedGetFloat_26a280(q);
    f = (f32)Rand_133710();
    ScriptSetRefFloat_26a1c0(a0, (f32)(s32)(r1 * f / 2147483648.0f));
    return 1;
}
