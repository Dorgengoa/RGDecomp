#include "types.h"
extern "C" s32 ObjRecHasFlags6_1c3eb0(s32, s32, s32);
extern "C" s32 ObjRecGetFlags_1c3d90(s32, s32, s32);

extern "C" s32 ObjRecIsDrawableMaybe_1c48b0(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = ObjRecHasFlags6_1c3eb0(p0, 1, p1);
    if (r0 == 0) {
        return 0;
    }
    r1 = ObjRecGetFlags_1c3d90(p0, 1, p1);
    return (u8)!(r1 & 0x10);
}
