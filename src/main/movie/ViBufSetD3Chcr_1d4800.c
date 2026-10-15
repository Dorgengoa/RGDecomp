#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

void ViBufSetD3Chcr_1d4800(u32 h)
{
    DisableIntr_120660();
    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 | 0x10000;
    *(volatile u32 *)0x1000B000 = h;
    *(volatile u32 *)0x1000F590 = *(volatile u32 *)0x1000F520 & 0xFFFEFFFF;
    EnableIntr_1206b0();
}
