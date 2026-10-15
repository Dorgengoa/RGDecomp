#include "types.h"

struct P001dd340 { u8 pad0[0x38]; s16 f38; u8 pad[0x6]; u8 *f40; };

extern s8 *MapDataGetName_1e7bf0(void *e);
extern s32 StrNotEqual_1f5300(s8 *a, s8 *b);

u8 *MapRecTableFindShareByName_1dd340(struct P001dd340 *p0, s8 *name)
{
    u8 *e;
    s32 i;
    s8 c;

    if (name == 0) {
        return 0;
    }
    e = p0->f40;
    if (e == 0) {
        return 0;
    }
    for (i = 0; i < p0->f38; i++, e += 0x58) {
        if (MapDataGetName_1e7bf0(e) == 0) {
            continue;
        }
        c = *name;
        if (c != *MapDataGetName_1e7bf0(e)) {
            continue;
        }
        if (StrNotEqual_1f5300(MapDataGetName_1e7bf0(e) + 1, name + 1) != 0) {
            continue;
        }
        return e;
    }
    return 0;
}
