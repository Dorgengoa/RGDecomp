#include "types.h"

struct P1dd270 { u8 pad0[0x3A]; s16 f3A; u8 pad3C[8]; u8 *f44; };

extern s8 *MapDataGetName_1e7bf0(void *e);
extern s32 StrNotEqual_1f5300(s8 *a, s8 *b);

u8 *MapRecTableFindBlockByName_1dd270(struct P1dd270 *p0, s8 *name)
{
    u8 *e;
    s32 i;
    s8 c;

    if (name == 0) {
        return 0;
    }
    e = p0->f44;
    if (e == 0) {
        return 0;
    }
    for (i = 0; i < p0->f3A; i++, e += 0xCC) {
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
