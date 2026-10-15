#include "types.h"

extern void TaskFlagsPush_1f5730(void *p);

void TaskTableStatePush_1f53e0(u8 *p)
{
    if (p == 0) {
        return;
    }
    while (*(s32 *)p != 0) {
        TaskFlagsPush_1f5730(p);
        p += 0x10;
    }
}
