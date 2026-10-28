/* rgp:protos */
#define RGP_SELF_EvTargetPointInVolumes_3527a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
typedef rg_u128 u128;

s32 EvTargetPointInVolumes_3527a0(s32 p0, s32 p1, s32 p2)
{
    u128 v20;

    if (p2 == 0) {
        return 0;
    }
    XformToLocal_2e7440((p0 + 0x80), &v20, p1);
    return (s32)EventVolumeRecAnyHitRideAllowed_2e4b50(p2, &v20);
}
