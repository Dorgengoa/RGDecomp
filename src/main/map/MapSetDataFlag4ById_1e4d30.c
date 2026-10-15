#include "types.h"

struct O1e4d30 { u8 pad0[0x2C]; s32 f2C; };

extern struct O1e4d30 *MapSlotsFindActiveById_1e4870(s32 a, s32 b, s32 c);
extern s32 MapDataIsLoadedOrUnloading_1e7980(struct O1e4d30 *r);

void MapSetDataFlag4ById_1e4d30(s32 a, s32 b, s32 flag)
{
    struct O1e4d30 *r;
    s32 v;

    r = MapSlotsFindActiveById_1e4870(a, b, 0);
    if (r == 0) {
        return;
    }
    if (MapDataIsLoadedOrUnloading_1e7980(r) == 0) {
        return;
    }
    if (flag != 0) {
        v = r->f2C | 4;
    } else {
        v = r->f2C & ~4;
    }
    r->f2C = v;
}
