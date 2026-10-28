#include "types.h"

extern void IpuSyncWithRefill_10d9a0(void);

asm void IpuSyncIfBusy_10ffc8(void)
{
    .set noreorder;
    lui        $2, (0x10002010 >> 16);
    lui        $5, (0x80004000 >> 16);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    ori        $5, $5, (0x80004000 & 0xFFFF);
    lw         $3, 0x0($2);
    lui        $2, (0x80000000 >> 16);
    and        $3, $3, $5;
    bne        $3, $2, L0010FFF4;
    nop;
    j          IpuSyncWithRefill_10d9a0;
    nop;
  L0010FFF4:
    jr         $31;
    nop;
}

