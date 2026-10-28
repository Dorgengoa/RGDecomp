/* rgp:protos */
#define RGP_SELF_MapEnvApplyFog_1e5ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T1e5ba0 {
    u8  pad00[4];
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
} T1e5ba0;

/*rgp*/
/*rgp*/
/*rgp*/

void MapEnvApplyFog_1e5ba0(T1e5ba0 *p)
{
    void *o;

    o = GetDrawCtx_15de80();
    FogSet_15cc60((u8)p->f04, (u8)p->f08, (u8)p->f0C, p->f10, p->f14,
                 p->f18, p->f1C);
    CameraRecSetFieldByIndexMaybe_142d90(o, 0, 1);
}
