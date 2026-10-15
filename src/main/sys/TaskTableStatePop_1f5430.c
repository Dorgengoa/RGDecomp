#include "types.h"

extern void TaskFlagsPop_1f5720(void *p);

void TaskTableStatePop_1f5430(u8 *p)
{
    if (p == 0) {
        return;
    }
    while (*(s32 *)p != 0) {
        TaskFlagsPop_1f5720(p);
        p += 0x10;
    }
}
