#include "types.h"

extern s32 MapDataCloneNames_1e7110(s32, s32);
extern s32 MapRecTableClone_1dd5b0(s32, s32);
extern s32 MapAreaGetShares_1dce60(s32);
extern s32 MapAreaGetShareCount_1dce50(s32);
extern s32 MapIdIndexInit_1ddda0(s32, s32, s32);
extern s32 MapIdIndexInsertSorted_1ddc00(s32, s32, s32);
extern s32 MapAreaGetBlocks_1dce30(s32);
extern s32 MapAreaGetBlockCount_1dce20(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaCloneAndIndex_1dab10(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 rv14;
    s32 rv15;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 l5;
    s32 l6;
    s32 r7;
    s32 r8;
    s32 r9;
    s32 r10;
    s32 l11;
    s32 l12;
    s32 r13;

    r0 = MapDataCloneNames_1e7110(p0, p1);
    if (r0 == 0) {
        return 0;
    }
    r1 = MapRecTableClone_1dd5b0((p0 + 0x54), p1);
    rv14 = 1;
    if (r1 == 0) {
        rv14 = 0;
        rv15 = p1;
    } else {
        r2 = MapAreaGetShares_1dce60(p0);
        r3 = MapAreaGetShareCount_1dce50(p0);
        r4 = MapIdIndexInit_1ddda0((p0 + 0xFC), r3, p1);
        l5 = 0;
        l6 = r2;
        while (l5 < r3) {
            r7 = MapIdIndexInsertSorted_1ddc00((p0 + 0xFC), l6, l5);
            l5 = (l5 + 1);
            l6 = (l6 + 0x58);
        }
        r8 = MapAreaGetBlocks_1dce30(p0);
        r9 = MapAreaGetBlockCount_1dce20(p0);
        r10 = MapIdIndexInit_1ddda0((p0 + 0x10C), r9, p1);
        l11 = 0;
        l12 = r8;
        while (l11 < r9) {
            r13 = MapIdIndexInsertSorted_1ddc00((p0 + 0x10C), l12, l11);
            l11 = (l11 + 1);
            l12 = (l12 + 0xCC);
        }
        rv14 = 1;
        rv15 = l11;
    }
    return rv14;
}
