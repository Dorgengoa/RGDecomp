/* rgp:protos */
#define RGP_SELF_MapSlotsQueryCollTrisMaybe_1e34f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MapSlotsQueryCollTrisMaybe_1e34f0(u8 *p0, u8 *buf, s32 n, s32 arg3)
{
    u8 *e;
    s32 done;
    s32 i;

    if (buf == 0 || n <= 0) {
        return 0;
    }
    e = p0 + 0x1928;
    done = 0;
    for (i = 0; i < 4; i++, e += 0x1CC) {
        done += MapAreaTreeQueryCollTrisMaybe_1dade0(e, buf + done * 96, n - done, arg3);
        if (done >= n) {
            break;
        }

    }
    return done;
}
