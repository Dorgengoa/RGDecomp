#include "types.h"

extern s32 MapAreaFindShareById_1dc820(s32, s32);
extern void MapAreaLoadShare_1da270(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapAreaLoadShareById_1da320(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;

    r0 = MapAreaFindShareById_1dc820(p0, p2);
    MapAreaLoadShare_1da270(p0, p1, r0, p3);
}
