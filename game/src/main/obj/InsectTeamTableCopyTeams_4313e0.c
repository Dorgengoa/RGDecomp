/* rgp:protos */
#define RGP_SELF_InsectTeamTableCopyTeams_4313e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *memcpy(void *, const void *, s32);

s32 InsectTeamTableCopyTeams_4313e0(u8 *a, void *b)
{
    if (b == 0) {
        return 0;
    }
    memcpy(b, a + 8, 0x1180);
    return 1;
}
