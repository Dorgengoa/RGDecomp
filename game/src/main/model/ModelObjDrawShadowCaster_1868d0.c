/* rgp:protos */
#define RGP_SELF_ModelObjDrawShadowCaster_1868d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct S1868d0 { u8 pad000[0x120]; s32 m120; } S1868d0;
/*rgp*/
/*rgp*/
void ModelObjDrawShadowCaster_1868d0(S1868d0 *p0)
{
    s32 r0;
    r0 = GetDrawCtx_15de80();
    ModelDrawShadowCaster_14f5d0(p0, r0, &p0->m120);
}
