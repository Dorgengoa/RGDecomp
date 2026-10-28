/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetScale_32d610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_004826E0;

s32 ScriptCmdEffectSetScale_32d610(s32 arg0, s32 arg1)
{
    if (arg1 != 3) {
        return 0;
    }
    {
        s8 buf[0x10] __attribute__((aligned(16))) = {0};

        ScriptSlotsToVec4_334810(buf, arg0);
        if (D_004826E0 != 0) {
            EffectInstanceSetScale_2dd550(D_004826E0, buf);
        }
    }
    return 1;
}
