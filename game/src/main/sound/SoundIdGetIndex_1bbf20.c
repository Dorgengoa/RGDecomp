/* rgp:protos */
#define RGP_SELF_SoundIdGetIndex_1bbf20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Mask the argument with 0xFFFF. */

s32 SoundIdGetIndex_1bbf20(s32 x)
{
    return x & 0xFFFF;
}
