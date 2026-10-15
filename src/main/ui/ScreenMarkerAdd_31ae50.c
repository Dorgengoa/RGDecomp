#include "types.h"

extern s32 ScreenMarkerProjectObj_31aad0(s32, s32);
extern s32 ScreenMarkerAddOrUpdate_31be60(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ScreenMarkerAdd_31ae50(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = ScreenMarkerProjectObj_31aad0(p0, p1);
    rv2 = r0;
    if (r0 != 0) {
        r1 = ScreenMarkerAddOrUpdate_31be60(p0, p1, p2);
        rv2 = r1;
    }
    return rv2;
}
