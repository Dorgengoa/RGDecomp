/* rgp:protos */
#define RGP_SELF_ScriptCmdNopArgcCheck_3322f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ScriptCmdNopArgcCheck_3322f0(void *a, s32 k)
{
    s32 r;

    if (k < 2) goto zero;
    if (k <= 4) goto one;
zero:
    r = 0;
    goto out;
one:
    r = 1;
out:
    return r;
}
