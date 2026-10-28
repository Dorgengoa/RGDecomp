/* rgp:protos */
#define RGP_SELF_normal_LeaderHudGetWeaponFlash_5069e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005069E0 -- `jr $31 / lwc1 $f0, 0xA0($4)` */
f32 normal_LeaderHudGetWeaponFlash_5069e0(void *p)
{
    return *(f32 *)((u8 *)p + 0xA0);
}
