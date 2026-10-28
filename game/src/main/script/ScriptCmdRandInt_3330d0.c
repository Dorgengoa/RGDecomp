/* rgp:protos */
#define RGP_SELF_ScriptCmdRandInt_3330d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdRandInt_3330d0(void *a0, s32 mode)
{
    void *q;
    s32 r1;
    f32 f;

    if (mode != 2) {
        return 0;
    }
    q = a0;
    a0 = (u8 *)a0 + 8;
    r1 = ScriptSlotGetInt_3348b0(q);
    f = (f32)Rand_133710();
    ScriptSlotStoreIntRef_3347f0(a0, (s32)((f32)r1 * f / 2147483648.0f));
    return 1;
}
