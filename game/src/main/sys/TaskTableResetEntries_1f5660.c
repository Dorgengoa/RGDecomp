/* rgp:protos */
#define RGP_SELF_TaskTableResetEntries_1f5660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

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
