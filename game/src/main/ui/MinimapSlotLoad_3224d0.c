/* rgp:protos */
#define RGP_SELF_MinimapSlotLoad_3224d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T3224D0 { u8 pad000[0x1A0]; s32 f1A0; };

/*rgp*/

s32 MinimapSlotLoad_3224d0(struct T3224D0 *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h)
{
    if (MinimapLoad_32a240(p, a, b, c, d, e, f, g, h) != 0) {
        p->f1A0 = 1;
        return 1;
    }
    return 0;
}
