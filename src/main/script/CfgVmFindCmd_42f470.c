#include "types.h"

struct Obj0 { s32 m00; };

s32 CfgVmFindCmd_42f470(struct Obj0 *p0, s32 p1)
{
    s32 lo;
    s32 hi;
    s32 mid;
    u16 key;
    u16 v;

    if (p0->m00 <= 0) {
        return 0;
    }
    hi = p0->m00 - 1;
    key = p1 & 0xFFFF;
    lo = 0;
    while (hi >= lo) {
        mid = lo + (((hi - lo) + 1) / 2);
        v = *(u16 *)((u8 *)p0 + (mid << 3) + 4);
        if (key == v) {
            return (s32)((u8 *)p0 + (mid << 3) + 4);
        }
        if (key < v) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}
