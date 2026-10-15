#include "types.h"
/* normal 0x0050B110 -- a bare tail call (`j func_28C210`) with the gp handle
 * loaded and the id in the delay slot. */
extern void *D_004845B4;              /* gp - 0xBBC */
extern void  func_28C210(void *p, s32 id);

void normal_ShopMenuIconClutBuild_50b110(void)
{
    func_28C210(D_004845B4, 0x32E);
}
