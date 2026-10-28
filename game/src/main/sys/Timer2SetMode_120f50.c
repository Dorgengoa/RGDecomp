#include "types.h"

extern void KernelWriteWordEret_120ed0(void);

asm void Timer2SetMode_120f50(void)
{
    .set noreorder;
    daddu      $5, $4, $0;
    lui        $4, (0xB0001010 >> 16);
    j          KernelWriteWordEret_120ed0;
    ori       $4, $4, (0xB0001010 & 0xFFFF);
}
