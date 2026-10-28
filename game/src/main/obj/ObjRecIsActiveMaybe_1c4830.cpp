/* rgp:protos */
#line 1
#include "types.h"

extern "C" s32 ObjRecHasFlags6_1c3eb0(s32, s32, s32);
extern "C" s32 ObjRecGetFlags_1c3d90(s32, s32, s32);

extern "C" s32 ObjRecIsActiveMaybe_1c4830(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = ((unsigned char)ObjRecHasFlags6_1c3eb0(p0, 1, p1));
    if (r0 == 0) {
        return 0;
    }
    r1 = ObjRecGetFlags_1c3d90(p0, 1, p1);
    if ((r1 & 0x20000000) != 0) {
        return 1;
    }
    return !(r1 & 8);
}
