/* rgp:protos */
#define RGP_SELF_UnitSetHitFxCooldownMaybe_3bd050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3BD050 { u8 pad000[0x40C]; f32 f40C; };

void UnitSetHitFxCooldownMaybe_3bd050(struct T3BD050 *p, f32 x)
{
    if (!(x <= 0.0f)) {
        p->f40C = x;
    } else {
        p->f40C = 0.0f;
    }
}
