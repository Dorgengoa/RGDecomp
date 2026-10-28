/* rgp:protos */
#define RGP_SELF_MinimapEmitSprite_324d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void MinimapEmitSprite_324d30(s32 a0, void *obj, f32 *p, f32 *q, s32 dx, s32 dy,
                  s32 x, s32 y, s32 ox, s32 oy)
{
    GsPktSetUV_13ed60(obj, x, y);
    GsPktSetXYZf_13f060(obj, (f32)dx + p[0], (f32)dy + p[1], 0.0f);
    GsPktSetUV_13ed60(obj, x + ox, y + oy);
    GsPktSetXYZf_13f060(obj, (f32)dx + q[0], (f32)dy + q[1], 0.0f);
}
