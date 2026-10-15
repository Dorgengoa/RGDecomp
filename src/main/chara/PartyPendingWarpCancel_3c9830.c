#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern void MapMgrWarpMenuRelease_1e2d30(s32);

struct Obj0 {
    u8 pad000[0x1A4];
    u8 b0 : 1;
    u8 b1 : 7;
    u8 pad1A5[0x1];
    s16 m1A6;
    s16 m1A8;
    u8 pad1AA[0x2];
    s32 m1AC;
    s32 m1B0;
};

s32 PartyPendingWarpCancel_3c9830(struct Obj0 *p0)
{
    s32 r0;

    if (p0->b0 == 0) {
        return 0;
    }
    r0 = GetMapMgr_201a90();
    if (r0 != 0) {
        MapMgrWarpMenuRelease_1e2d30(r0);
    }
    p0->b0 = 0;
    p0->m1A6 = -1;
    p0->m1A8 = -1;
    p0->m1AC = 0;
    p0->m1B0 = 0;
    return 1;
}
