#include "types.h"
typedef struct S1868d0 { u8 pad000[0x120]; s32 m120; } S1868d0;
extern s32 GetDrawCtx_15de80(void);
extern void ModelDrawShadowCaster_14f5d0(S1868d0 *, s32, s32 *);
void ModelObjDrawShadowCaster_1868d0(S1868d0 *p0)
{
    s32 r0;
    r0 = GetDrawCtx_15de80();
    ModelDrawShadowCaster_14f5d0(p0, r0, &p0->m120);
}
