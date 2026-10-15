#include "types.h"

extern void MapBlockAnimStepIfActive_1dec90(s32 arg0, f32 arg1);
extern void MapDataAnimStep_1e6600(void *arg0, f32 arg1);
extern s32 MapDataIsLoadedOrUnloading_1e7980(void);

void MapAreaTreeAnimStep_1d9970(void *arg0, f32 fparg0)
{
    s32 *cur2;
    u8 **cur;
    s32 i;
    s32 j;

    if (MapDataIsLoadedOrUnloading_1e7980() != 0) {
        MapDataAnimStep_1e6600(arg0, fparg0);
        cur = (u8 **)((u8 *)arg0 + 0x128);
        i = 0;
        while (i < *(s16 *)((u8 *)arg0 + 0x1C8)) {
            MapDataAnimStep_1e6600(*cur, fparg0);
            i += 1;
            cur += 1;
        }
        cur2 = (s32 *)((u8 *)arg0 + 0x178);
        j = 0;
        while (j < *(s16 *)((u8 *)arg0 + 0x1CA)) {
            MapBlockAnimStepIfActive_1dec90(*cur2, fparg0);
            j += 1;
            cur2 += 1;
        }
    }
}
