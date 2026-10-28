/* rgp:protos */
#define RGP_SELF_MapSlotsRefreshBlocksEnabled_1e2b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 b[0x1CC]; } S;

/*rgp*/

void MapSlotsRefreshBlocksEnabled_1e2b70(void *o)
{
    S *p = (S *)((u8 *)o + 0x1928);
    s32 i;

    for (i = 0; i < 0x4; i++) {
        MapAreaRefreshBlocksEnabled_1da5a0(p);
        p++;
    }
}
