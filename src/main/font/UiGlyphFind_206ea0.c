#include "types.h"

extern s32 D_00481B88;
extern s32 D_00481B8C;

s32 UiGlyphFind_206ea0(s32 p0)
{
    s32 lo;
    s32 hi;
    s32 mid;
    u16 key;
    u16 *e;

    key = p0 & 0xFFFF;
    lo = 0;
    hi = D_00481B88 - 1;
    while (hi >= lo) {
        mid = lo + (((hi - lo) + 1) / 2);
        e = (u16 *)((u8 *)D_00481B8C + (mid * 6));
        if (*e == key) {
            return (s32)e;
        }
        if (*e < key) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return 0;
}
