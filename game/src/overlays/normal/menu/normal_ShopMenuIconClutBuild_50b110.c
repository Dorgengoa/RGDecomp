/* rgp:protos */
#define RGP_SELF_normal_ShopMenuIconClutBuild_50b110 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050B110 -- a bare tail call (`j func_28C210`) with the gp handle
 * loaded and the id in the delay slot. */
extern void *D_004845B4;              /* gp - 0xBBC */
/*rgp*/

void normal_ShopMenuIconClutBuild_50b110(void)
{
    ItemIconMaskClutBuild_28c210(D_004845B4, 0x32E);
}
