#include "types.h"
extern void ViBufSetD4Chcr_1d47a0(s32);
extern void DeleteSema(s32);
struct A { u8 pad000[0x40]; s32 m40; };
s32 ViBufDelete_1d3e20(struct A *p0)
{
    ViBufSetD4Chcr_1d47a0(5);
    *(volatile u32 *)0x1000B420 = 0;
    *(volatile u32 *)0x1000B410 = 0;
    *(volatile u32 *)0x1000B430 = 0;
    DeleteSema(p0->m40);
    return 1;
}
