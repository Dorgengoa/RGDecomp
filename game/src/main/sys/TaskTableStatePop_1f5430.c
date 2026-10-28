/* rgp:protos */
#define RGP_SELF_TaskTableStatePop_1f5430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

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
