/* rgp:protos */
#define RGP_SELF_EvCmdEventStackPop_25d140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004BD980[];
extern void *D_00481F78;
/*rgp*/
/*rgp*/

s32 EvCmdEventStackPop_25d140(void *rgp_a0)
{
    s32 *e;
    s32 r = ScriptGetInt_26a2a0((void *)rgp_a0);
    if (r < 0) goto zero;
    if (r < 8) goto ok;
zero:
    return 0;
ok:
    e = &D_004BD980[r];
    RecStackPop_1c4140(D_00481F78, *e);
    *e = -1;
    return 1;
}
