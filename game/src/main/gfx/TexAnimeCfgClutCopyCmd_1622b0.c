/* rgp:protos */
#define RGP_SELF_TexAnimeCfgClutCopyCmd_1622b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern struct Big95E73 { u8 v; u8 pad[15]; } D_00495E73;

s32 TexAnimeCfgClutCopyCmd_1622b0(void *rgp_a0)
{
    D_00495E73.v = VariantGetInt_15f780((void *)rgp_a0);
    return 1;
}
