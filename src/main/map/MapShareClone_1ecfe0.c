#include "types.h"

/* Known-positive sibling shape of MapBlockClone_1df760 (byte-identical, in cunits). */

extern s32 MapDataCloneNames_1e7110(s32, s32);
extern s32 ReturnTrue_1ed0a0(s32, s32);

s32 MapShareClone_1ecfe0(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = MapDataCloneNames_1e7110(p0, p1);
    rv2 = r1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        r1 = ReturnTrue_1ed0a0((p0 + 0x54), p1);
        rv2 = r1;
    }
    return rv2;
}
