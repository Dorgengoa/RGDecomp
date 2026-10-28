#include "types.h"

void KernelAlarmArmTimer3_447560(u32 v)
{
    asm volatile {
        lui   $2, 0xB000
        ori   $2, $2, 0x1820
        sw    v, 0x0($2)
        sync
        lui   $2, 0xB000
        addiu $3, $0, 0x583
        ori   $2, $2, 0x1810
        sw    $3, 0x0($2)
    }
}
