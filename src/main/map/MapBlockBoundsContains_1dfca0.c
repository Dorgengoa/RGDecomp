#include "types.h"

extern s32 MapDataIsEnabled_1e7c20(void *p);
extern s32 MapBlockBoxListHitExclude_1e0220(void *p, void *q, f32 x);
extern s32 AreaBoxContainsPointThunk_1e93c0(void *p, void *q, f32 x);

s32 MapBlockBoundsContains_1dfca0(u8 *p0, void *p1, f32 x)
{
    if (MapDataIsEnabled_1e7c20(p0) == 0) {
        return 0;
    }
    if (MapBlockBoxListHitExclude_1e0220(p0 + 0x54, p1, -x) != 0) {
        return 0;
    }
    return AreaBoxContainsPointThunk_1e93c0(p0 + 0x74, p1, x);
}
