#include "types.h"

struct O1e4da0 { u8 pad0[0x2C]; s32 f2C; };

extern struct O1e4da0 *MapSlotsFindActiveById_1e4870(s32 a, s32 b, s32 c);
extern s32 MapDataIsLoaded_1e79d0(struct O1e4da0 *r);

void MapSetDataFlag2ById_1e4da0(s32 a, s32 b, s32 flag)
{
    struct O1e4da0 *r;
    s32 v;

    r = MapSlotsFindActiveById_1e4870(a, b, 0);
    if (r == 0) {
        return;
    }
    if (MapDataIsLoaded_1e79d0(r) == 0) {
        return;
    }
    if (flag != 0) {
        v = r->f2C | 2;
    } else {
        v = r->f2C & ~2;
    }
    r->f2C = v;
}
