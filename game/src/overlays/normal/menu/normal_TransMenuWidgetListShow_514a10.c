/* rgp:protos */
#define RGP_SELF_normal_TransMenuWidgetListShow_514a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00514A10 -- tail `j func_28C190`, the parameter moved to $6. */

extern char normal_D_005266D0[];
extern void *D_004846E8;          /* gp - 0xA88 */

/*rgp*/

s32 normal_TransMenuWidgetListShow_514a10(void *p)
{
    return (UiSetWidgetListVisibleById_28c190(D_004846E8, normal_D_005266D0, p), (s32)0);
}
