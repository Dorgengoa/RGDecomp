/* rgp:protos */
#define RGP_SELF_MapSetDataFlag2ById_1e4da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct O1e4da0 { u8 pad0[0x2C]; s32 f2C; };

/*rgp*/
/*rgp*/

int MapSetDataFlag2ById_1e4da0(s32 a, s32 b, s32 flag)
{ int rgp_v0 = 0;
    struct O1e4da0 *r;
    s32 v;

    r = (rgp_v0 = ((struct O1e4da0 *)MapSlotsFindActiveById_1e4870(a, b, 0)));
    if (r == 0) {
        return rgp_v0;
    }
    if ((rgp_v0 = ((unsigned char)MapDataIsLoaded_1e79d0(r))) == 0) {
        return rgp_v0;
    }
    if (flag != 0) {
        v = r->f2C | 2;
    } else {
        v = r->f2C & ~2;
    }
    r->f2C = v;
return rgp_v0; }
