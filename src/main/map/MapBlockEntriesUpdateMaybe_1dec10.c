#include "types.h"

extern s32 MapDataIsLoadedOrUnloading_1e7980(void *);
extern s32 MapEntryUpdateMaybe_1e0cd0(s32, s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC0];
    s32 mC0;
    u8 pad0C4[0x4];
    s16 mC8;
};

void MapBlockEntriesUpdateMaybe_1dec10(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 t0;
    s32 l2;
    s32 l1;
    s32 r3;

    r0 = MapDataIsLoadedOrUnloading_1e7980(p0);
    if (r0 != 0) {
        t0 = p0->mC0;
        if (t0 != 0) {
            l2 = t0;
            l1 = 0;
            while (l1 < p0->mC8) {
                r3 = MapEntryUpdateMaybe_1e0cd0(l2, p1, p0);
                l1 = (l1 + 1);
                l2 = (l2 + 0x7A0);
            }
        }
        return;
    }
}
