/* rgp:protos */
#define RGP_SELF_ItemStackIsKindOf_3d5c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ItemStackIsKindOf_3d5c60(void *self, s32 x)
{
    if (x == 1) return 1;
    return x == 0;
}
