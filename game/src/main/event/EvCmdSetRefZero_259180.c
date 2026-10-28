/* rgp:protos */
#define RGP_SELF_EvCmdSetRefZero_259180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EvCmdSetRefZero_259180(void *p, s32 k)
{
    if (k > 0) goto run;
    return 0;
run:
    ScriptSetRefInt_26a1e0(p, 0);
    return 1;
}
