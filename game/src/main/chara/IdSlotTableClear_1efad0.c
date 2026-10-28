/* rgp:protos */
#define RGP_SELF_IdSlotTableClear_1efad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void IdSlotTableClear_1efad0(s32 p0, s32 p1)
{
    if (p1 >= 0) {
        if (p1 < 0x100) {
            goto ok;
        }
    }
    return;
ok:
    *(s32 *)((u8 *)p0 + (p1 << 3)) = 0;
    *(s32 *)((u8 *)p0 + (p1 << 3) + 0x4) = -1;
}
