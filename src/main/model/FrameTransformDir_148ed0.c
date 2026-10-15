#include "types.h"

extern void FrameCalcWorldMatrix_148ff0(void *, void *);
extern void MtxMulVec4_13c900(void *, void *, void *);

void FrameTransformDir_148ed0(void *p0, void *p1, u8 *p2)
{
    u8 tmp[0x40];
    f32 save;

    save = *(f32 *)(p2 + 0xC);
    *(s32 *)(p2 + 0xC) = 0;
    FrameCalcWorldMatrix_148ff0(p0, tmp);
    MtxMulVec4_13c900(p1, tmp, p2);
    *(f32 *)(p2 + 0xC) = save;
}
