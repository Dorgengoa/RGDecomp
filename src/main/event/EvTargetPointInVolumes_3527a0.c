#include "types.h"

extern void XformToLocal_2e7440(s32, void *, s32);
extern void EventVolumeRecAnyHitRideAllowed_2e4b50(s32, void *);
typedef unsigned __int128 u128;

s32 EvTargetPointInVolumes_3527a0(s32 p0, s32 p1, s32 p2)
{
    u128 v20;

    if (p2 == 0) {
        return 0;
    }
    XformToLocal_2e7440((p0 + 0x80), &v20, p1);
    EventVolumeRecAnyHitRideAllowed_2e4b50(p2, &v20);
}
