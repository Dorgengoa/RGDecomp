#include "types.h"

f32 BtlElemParamGetChainFinishScaleMaybe_3f94b0(void *p, s32 i)
{
    if (i <= 0 || i > 3) return 1.0f;
    return *(f32 *)(i * 4 - (0 - (s32)p) + 0xA8);
}
