#include "types.h"

extern void GsPktSetUV_13ed60(void *, s32, s32);
extern void GsPktSetXYZf_13f060(void *, f32, f32, f32);

void MinimapEmitSprite_324d30(s32 a0, void *obj, f32 *p, f32 *q, s32 dx, s32 dy,
                  s32 x, s32 y, s32 ox, s32 oy)
{
    GsPktSetUV_13ed60(obj, x, y);
    GsPktSetXYZf_13f060(obj, (f32)dx + p[0], (f32)dy + p[1], 0.0f);
    GsPktSetUV_13ed60(obj, x + ox, y + oy);
    GsPktSetXYZf_13f060(obj, (f32)dx + q[0], (f32)dy + q[1], 0.0f);
}
