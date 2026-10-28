/* rgp:protos */
#define RGP_SELF_EvCmdMenuThinkIsSelecting_25fb20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuThinkIsSelecting_25fb20(void *arg0)
{
    s32 t;

    t = GetGameMode_1f59c0() != 3;
    if (t) {
        t = func_5219B0() != 0;
    }
    ScriptSetRefInt_26a1e0(arg0, t & 0xFF);
    return 1;
}
