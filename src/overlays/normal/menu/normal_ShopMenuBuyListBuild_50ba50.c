#include "types.h"
/* normal 0x0050BA50 -- clears the 64-slot overlay table then refills the first
 * `n` entries from func_3E7DE0. */
extern s32 D_00527D30[];

extern void *func_1FEDE0(void);
extern s32   func_3E7E10(void *h);
extern s32   func_3E7DE0(void *h, s32 i);

s32 normal_ShopMenuBuyListBuild_50ba50(void)
{
    void *h;
    s32   n;
    s32   i;

    for (i = 0; i < 0x40; i++) {
        D_00527D30[i] = 0;
    }
    h = func_1FEDE0();
    n = func_3E7E10(h);
    for (i = 0; i < n; i++) {
        D_00527D30[i] = func_3E7DE0(h, i);
    }
    return 1;
}
