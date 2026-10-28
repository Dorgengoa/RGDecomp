/* rgp:protos */
#define RGP_SELF_CollMeshIsKindOf_16b920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 CollMeshIsKindOf_16b920(s32 a, s32 b)
{
    if (b == 10007) return 1;
    return b == 10005;
}
