/* rgp:protos */
#define RGP_SELF_TaskTableStatePush_1f53e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

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
