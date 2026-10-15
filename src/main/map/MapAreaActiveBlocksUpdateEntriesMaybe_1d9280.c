#include "types.h"

extern s32 MapDataIsLoadedOrUnloading_1e7980(void *);
extern s32 MapBlockEntriesUpdateMaybe_1dec10(s32, s32);

struct Obj0 {
    u8 pad000[0x1CA];
    s16 m1CA;
};

struct Obj1 {
    s32 m00;
};

void MapAreaActiveBlocksUpdateEntriesMaybe_1d9280(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    struct Obj1 *l2;
    s32 l1;
    s32 t0;
    s32 r3;

    r0 = MapDataIsLoadedOrUnloading_1e7980(p0);
    if (r0 == 0) {
        return;
    }
    l2 = (struct Obj1 *)((u8 *)p0 + 0x178);
    l1 = 0;
    while (l1 < p0->m1CA) {
        t0 = l2->m00;
        r3 = MapBlockEntriesUpdateMaybe_1dec10(t0, p1);
        l1 = (l1 + 1);
        l2 = (struct Obj1 *)((u8 *)l2 + 4);
    }
}
