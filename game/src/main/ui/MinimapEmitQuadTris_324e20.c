/* rgp:protos */
#define RGP_SELF_MinimapEmitQuadTris_324e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void MinimapEmitQuadTris_324e20(s32 unused, void *h, f32 *v0, f32 *v1, f32 *v2, f32 *v3,
                  s32 ox, s32 oy, s32 u, s32 v, s32 du, s32 dv)
{
    GsPktSetUV_13ed60(h, u, v);
    GsPktSetXYZf_13f060(h, (f32)ox + v0[0], (f32)oy + v0[1], 0.0f);
    GsPktSetUV_13ed60(h, u + du, v);
    GsPktSetXYZf_13f060(h, (f32)ox + v1[0], (f32)oy + v1[1], 0.0f);
    GsPktSetUV_13ed60(h, u, v + dv);
    GsPktSetXYZf_13f060(h, (f32)ox + v2[0], (f32)oy + v2[1], 0.0f);
    GsPktSetUV_13ed60(h, u + du, v);
    GsPktSetXYZf_13f060(h, (f32)ox + v1[0], (f32)oy + v1[1], 0.0f);
    GsPktSetUV_13ed60(h, u, v + dv);
    GsPktSetXYZf_13f060(h, (f32)ox + v2[0], (f32)oy + v2[1], 0.0f);
    GsPktSetUV_13ed60(h, u + du, v + dv);
    GsPktSetXYZf_13f060(h, (f32)ox + v3[0], (f32)oy + v3[1], 0.0f);
}
