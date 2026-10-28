/* rgp:protos */
#define RGP_SELF_EvCmdPauseSetAllowed_25c550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EvCmdTaskSetRenderTasksEnabled_25bc50 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

s32 EvCmdPauseSetAllowed_25c550(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = (PauseSetAllowed_2f6640((r0 != 0)), (s32)0);
    return 1;
}
