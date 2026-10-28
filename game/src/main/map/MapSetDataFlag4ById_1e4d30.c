/* rgp:protos */
#define RGP_SELF_MapSetDataFlag4ById_1e4d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct O1e4d30 { u8 pad0[0x2C]; s32 f2C; };

/*rgp*/
/*rgp*/

void MapSetDataFlag4ById_1e4d30(s32 a, s32 b, s32 flag)
{
    struct O1e4d30 *r;
    s32 v;

    r = ((struct O1e4d30 *)MapSlotsFindActiveById_1e4870(a, b, 0));
    if (r == 0) {
        return;
    }
    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(r)) == 0) {
        return;
    }
    if (flag != 0) {
        v = r->f2C | 4;
    } else {
        v = r->f2C & ~4;
    }
    r->f2C = v;
}
