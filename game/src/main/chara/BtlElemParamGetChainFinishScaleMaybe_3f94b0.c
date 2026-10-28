/* rgp:protos */
#define RGP_SELF_BtlElemParamGetChainFinishScaleMaybe_3f94b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

f32 BtlElemParamGetChainFinishScaleMaybe_3f94b0(void *p, s32 i)
{
    if (i <= 0 || i > 3) return 1.0f;
    return *(f32 *)(i * 4 - (0 - (s32)p) + 0xA8);
}
