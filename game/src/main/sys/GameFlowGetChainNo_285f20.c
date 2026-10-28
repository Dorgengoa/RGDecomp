/* rgp:protos */
#define RGP_SELF_GameFlowGetChainNo_285f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s32 D_004821C4. */

extern s32 D_004821C4;

s32 GameFlowGetChainNo_285f20(void)
{
    return D_004821C4;
}
