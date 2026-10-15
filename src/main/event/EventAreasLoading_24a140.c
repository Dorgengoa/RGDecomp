#include "types.h"

extern s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
extern s32 MapDataGetState_1e7a00(s32);

s32 EventAreasLoading_24a140(u8 *arg0, s32 arg1)
{
    s32 *p;
    s32 i;
    s32 v;
    s32 r;

    p = (s32 *)(arg0 + 0x334);
    for (i = 0; i < 0x20; i++, p++) {
        v = *p;
        if (v >= 0) {
            r = MapSlotsFindBlockById_1e49b0(arg1, v, 0);
            if (r == 0) {
                *p = -1;
                continue;
            }
            if (MapDataGetState_1e7a00(r) != 2) {
                return 1;
            }
            *p = -1;
        }
    }
    return 0;
}
