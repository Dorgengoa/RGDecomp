/* rgp:protos */
#define RGP_SELF_WarpMenuFadeInStart_39dd70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T39DD70 { u8 pad000[0x28]; f32 f28; f32 f2C; };

/*rgp*/

void WarpMenuFadeInStart_39dd70(struct T39DD70 *p, f32 x)
{
    if (x <= 0.0f) {
        WarpMenuFadeReset_39dd10(p);
        return;
    }
    p->f2C = (1.0f - p->f28) / x;
}
