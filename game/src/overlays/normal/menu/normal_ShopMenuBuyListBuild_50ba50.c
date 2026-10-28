/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyListBuild_50ba50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050BA50 -- clears the 64-slot overlay table then refills the first
 * `n` entries from func_3E7DE0. */
extern s32 normal_D_00527D30[];

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyListBuild_50ba50(void)
{
    void *h;
    s32   n;
    s32   i;

    for (i = 0; i < 0x40; i++) {
        normal_D_00527D30[i] = 0;
    }
    h = GetGameData_1fede0();
    n = ShopListGetRowCount_3e7e10(h);
    for (i = 0; i < n; i++) {
        normal_D_00527D30[i] = ShopListGetRow_3e7de0(h, i);
    }
    return 1;
}
