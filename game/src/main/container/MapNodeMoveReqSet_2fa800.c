/* rgp:protos */
#define RGP_SELF_MapNodeMoveReqSet_2fa800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 MapNodeMoveReqSet_2fa800(u8 *p, s32 x, s32 y, void *s, void *t)
{
    MapNodeMoveReqReset_2fa8d0(p);
    if (x < 0 || y < 0) {
        return 0;
    }
    *(s32 *)(p + 0x20) = x;
    *(s32 *)(p + 0x24) = y;
    VecCopy_1cbe30(p, s);
    VecCopy_1cbe30(p + 0x10, t);
    return 1;
}
