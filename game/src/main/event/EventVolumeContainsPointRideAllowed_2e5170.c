/* rgp:protos */
#define RGP_SELF_EventVolumeContainsPointRideAllowed_2e5170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O {
    u32 m00;
} O;

/*rgp*/

s32 EventVolumeContainsPointRideAllowed_2e5170(O *o, int rgp_a1)
{
    if ((o->m00 & 0x200) != 0) return 0;
    return ((unsigned char)EventVolumeContainsPoint_2e51f0(o, (int)rgp_a1, 0.0f));
}
