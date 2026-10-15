#include "types.h"
/* normal 0x00518640 -- records the shop's pending item, and its price only
 * when the price is valid.  `bltz` is a PLAIN branch, so the first store is in
 * its delay slot and runs on both paths -- only the second store is guarded. */
extern s32 D_00484738;            /* gp - 0xA38 */
extern s32 D_0048473C;            /* gp - 0xA34 */
extern void normal_TransMenuSetWarpRequest_518640(s32 a, s32 b);
void normal_TransMenuSetWarpRequest_518640(s32 a, s32 b)
{
    D_00484738 = a;
    if (b >= 0) {
        D_0048473C = b;
    }
}
