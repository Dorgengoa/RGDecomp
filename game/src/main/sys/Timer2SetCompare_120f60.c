#include "types.h"

extern void KernelWriteWordEret_120ed0(void);

asm void Timer2SetCompare_120f60(void)
{
    .set noreorder;
    daddu      $5, $4, $0;
    lui        $4, (0xB0001020 >> 16);
    j          KernelWriteWordEret_120ed0;
    ori       $4, $4, (0xB0001020 & 0xFFFF);
}
