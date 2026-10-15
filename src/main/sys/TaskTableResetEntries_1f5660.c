#include "types.h"

extern void TaskEntryReset_1f57c0(void *p);

void TaskTableResetEntries_1f5660(u8 *p)
{
    if (p == 0) {
        return;
    }
    while (*(s32 *)p != 0) {
        TaskEntryReset_1f57c0(p);
        p += 0x10;
    }
}
