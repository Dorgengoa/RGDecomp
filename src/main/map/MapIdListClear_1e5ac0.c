#include "types.h"

extern void MapIdListEntryInit_1e5fa0(void *);

void MapIdListClear_1e5ac0(u8 *o)
{
    s32 i;

    for (i = 0; i < 0x14; i++) {
        MapIdListEntryInit_1e5fa0(o + i * 0x8);
    }
    *(s32 *)(o + 0xA0) = 0;
}
