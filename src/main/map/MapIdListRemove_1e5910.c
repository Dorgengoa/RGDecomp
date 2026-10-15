#include "types.h"

/* Same family documented as parked in build/s0910/agent5_FINDINGS.md:
   length-exact draft, bad=6 register swap (diff/slot) that decl-order
   reordering did not fix there either. Reusing that draft shape as-is. */
extern s32 MapIdListFind_1e5a80(void);
extern void MapIdListEntryInit_1e5fa0(void *, s32);

void MapIdListRemove_1e5910(u8 *arr)
{
    s32 end;
    s32 i;
    u8 *e;
    s32 newCount;

    end = MapIdListFind_1e5a80();
    if (end == 0) {
        return;
    }
    i = (end - (s32)arr) / 8 + 1;
    while (i < *(s32 *)(arr + 0xA0)) {
        e = arr + i * 8;
        i++;
        *(s16 *)(e - 8) = *(s16 *)(e + 0);
        *(s16 *)(e - 6) = *(s16 *)(e + 2);
        *(s32 *)(e - 4) = *(s32 *)(e + 4);
    }
    newCount = *(s32 *)(arr + 0xA0) - 1;
    *(s32 *)(arr + 0xA0) = newCount;
    if (newCount >= 0) {
        MapIdListEntryInit_1e5fa0(arr + newCount * 8, i);
    }
}
