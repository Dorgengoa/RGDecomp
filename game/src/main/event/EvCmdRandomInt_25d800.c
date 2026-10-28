/* rgp:protos */
#define RGP_SELF_EvCmdRandomInt_25d800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdRandomInt_25d800(void *a0, s32 mode)
{
    void *q;
    s32 r1;
    f32 f;

    if (mode != 2) {
        return 0;
    }
    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = ScriptGetInt_26a2a0(q);
    f = (f32)Rand_133710();
    ScriptSetRefInt_26a1e0(a0, (s32)((f32)r1 * f / 2147483648.0f));
    return 1;
}
