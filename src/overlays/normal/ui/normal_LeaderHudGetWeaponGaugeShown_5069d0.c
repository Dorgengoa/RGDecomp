#include "types.h"
/* normal 0x005069D0 -- `jr $31 / lwc1 $f0, 0xA8($4)` */
f32 normal_LeaderHudGetWeaponGaugeShown_5069d0(void *p)
{
    return *(f32 *)((u8 *)p + 0xA8);
}
