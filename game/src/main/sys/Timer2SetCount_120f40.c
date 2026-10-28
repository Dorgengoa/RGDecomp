#include "types.h"

extern void KernelWriteWordEret_120ed0(void);

asm void Timer2SetCount_120f40(void)
{
    .set noreorder;
    daddu      $5, $4, $0;
    lui        $4, (0xB0001000 >> 16);
    j          KernelWriteWordEret_120ed0;
    ori       $4, $4, (0xB0001000 & 0xFFFF);
}
