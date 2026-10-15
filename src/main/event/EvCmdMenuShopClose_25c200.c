#include "types.h"

/* Known-positive sibling shape of EvCmdMenuCompleteCheckClose_25be80 (byte-identical, in cunits). */

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 ShopMenuClose_2036a0(void);

extern u8 D_0045EF40[];
extern u8 D_0045EF50[];

s32 EvCmdMenuShopClose_25c200(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(0, D_0045EF40);
    TaskSetEnabled_27c2a0(0, D_0045EF50);
    r2 = ShopMenuClose_2036a0();
    return 1;
}
