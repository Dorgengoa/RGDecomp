#include "types.h"
/* normal 0x0050BB00 -- twin of 0x0050EC80.  `dsll32/dsra32 ..,16` on the
 * second parameter is an s32 parameter with an explicit (s16) cast; the
 * `dsll32/dsra32 ..,0` on the product is the widening to func_291250's s64
 * value slot. */
extern void *D_004845CC;              /* gp - 0xBA4 */
extern void  func_291250(void *w, u16 id, s32 slot, s64 v);

s32 normal_ShopMenuBuyTotalPriceSet_50bb00(s32 a, s32 b)
{
    func_291250(D_004845CC, 0x4F, 1, a * (s16)b);
    return 1;
}
