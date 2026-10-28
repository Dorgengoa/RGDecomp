/* rgp:protos */
#define RGP_SELF_InfoCfgOutlineLevelCmd_1ab1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern struct Big9D43C { s32 v; s32 pad[3]; } D_0049D43C;
extern struct Big9D440 { s32 v; s32 pad[3]; } D_0049D440;
/*rgp*/

s32 InfoCfgOutlineLevelCmd_1ab1e0(void *rgp_a0)
{
    D_0049D43C.v = 1;
    D_0049D440.v = VariantGetInt_15f780((void *)rgp_a0);
    return 1;
}
