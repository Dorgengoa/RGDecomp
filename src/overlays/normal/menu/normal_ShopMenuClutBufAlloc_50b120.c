#include "types.h"
/* normal 0x0050B120 -- one call whose argument is a gp global loaded in the
 * `jal`'s delay slot, its result stored to another gp global.
 * One of the 55 unnamed functions. */
extern void *D_004845AC;
extern void *D_004845B4;
extern void *func_28C2A0(void *p);

void normal_ShopMenuClutBufAlloc_50b120(void)
{
    D_004845B4 = func_28C2A0(D_004845AC);
}
