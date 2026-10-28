/* rgp:protos */
#define RGP_SELF_normal_TransMenuIconClutBuild_518590 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518590 -- tail call through a gp handle. */

extern void *D_00484728;   /* gp - 0xA48 */

/*rgp*/

void normal_TransMenuIconClutBuild_518590(void)
{
    ItemIconMaskClutBuild_28c210(D_00484728, 0x32C);
}
