/* rgp:protos */
#define RGP_SELF_MinimapMgrFadeInStart_321e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T321E80 { u8 pad000[0x51C]; f32 f51C; };

void MinimapMgrFadeInStart_321e80(struct T321E80 *p, f32 x)
{
    p->f51C = 1.0f / x;
}
