/* rgp:protos */
#define RGP_SELF_FrameTransformDir_148ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void FrameTransformDir_148ed0(void *p0, void *p1, u8 *p2)
{
    u8 tmp[0x40] __attribute__((aligned(16)));
    f32 save;

    save = *(f32 *)(p2 + 0xC);
    *(s32 *)(p2 + 0xC) = 0;
    FrameCalcWorldMatrix_148ff0(p0, tmp);
    MtxMulVec4_13c900(p1, tmp, p2);
    *(f32 *)(p2 + 0xC) = save;
}
