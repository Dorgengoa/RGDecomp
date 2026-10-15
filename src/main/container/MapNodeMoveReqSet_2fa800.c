#include "types.h"

extern void MapNodeMoveReqReset_2fa8d0(u8 *, s32, s32, void *, void *);
extern void VecCopy_1cbe30(u8 *, void *);

s32 MapNodeMoveReqSet_2fa800(u8 *p, s32 x, s32 y, void *s, void *t)
{
    MapNodeMoveReqReset_2fa8d0(p, x, y, s, t);
    if (x < 0 || y < 0) {
        return 0;
    }
    *(s32 *)(p + 0x20) = x;
    *(s32 *)(p + 0x24) = y;
    VecCopy_1cbe30(p, s);
    VecCopy_1cbe30(p + 0x10, t);
    return 1;
}
