#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 MapAreaGetActiveBlockList_1dc0c0(s32);
extern s32 MapAreaGetActiveBlockCount_1dc0b0(s32);
extern s32 MapBlockFindEntryByKeyMaybe_1dea70(s32, s32);
extern s32 MapBlockEntriesShow_1deba0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 MapAreaActiveBlocksFindEntryByKeyMaybe_1d9150(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 l3;
    struct Obj0 *l4;
    s32 t0;
    s32 r5;
    s32 t1;
    s32 r6;

    r0 = MapDataIsLoaded_1e79d0(p0);
    if (r0 == 0) {
        return 0;
    }
    r1 = MapAreaGetActiveBlockList_1dc0c0(p0);
    if (r1 != 0) {
        r2 = MapAreaGetActiveBlockCount_1dc0b0(p0);
        l3 = 0;
        l4 = (struct Obj0 *)r1;
        while (l3 < r2) {
            t0 = l4->m00;
            r5 = MapBlockFindEntryByKeyMaybe_1dea70(t0, p1);
            if (r5 != 0) {
                return r5;
            }
            t1 = l4->m00;
            r6 = MapBlockEntriesShow_1deba0(t1);
            l3 = (l3 + 1);
            l4 = (struct Obj0 *)((u8 *)l4 + 4);
        }
    }
    return 0;
}
