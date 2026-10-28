/* rgp:protos */
#define RGP_SELF_GameFlowGetInteractTargetId_285ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s16 D_004821D2. */

extern s16 D_004821D2;

s16 GameFlowGetInteractTargetId_285ed0(void)
{
    return D_004821D2;
}
