/* rgp:protos */
#define RGP_SELF_EventVolumeContainsPointMoveAllowed_2e51b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O {
    u32 m00;
} O;

/*rgp*/

s32 EventVolumeContainsPointMoveAllowed_2e51b0(O *o, int rgp_a1)
{
    if ((o->m00 & 0x100) != 0) return 0;
    return ((unsigned char)EventVolumeContainsPoint_2e51f0(o, (int)rgp_a1, 0.0f));
}
