/* rgp:protos */
#line 1
#include "types.h"

struct A001DB1C0 {
    u8 pad0[0x178];
    s32 unk178[0x14];
    s16 unk1C8;
    s16 unk1CA;
};

struct B001DB1C0 {
    f32 unk0;
    f32 unk4;
};

extern "C" {
extern s32 MapBlockBoundsContainsXZ_1dfc20(s32, B001DB1C0 *, f32);
extern f32 MapBlockGetBoxBottomY_1dfe60(s32);
extern f32 MapBlockGetBoxTopY_1dfe70(s32);
extern f32 MapBlockGetBoxVolume_1dfe80(s32);
extern s32 MapDataIsLoaded_1e79d0(A001DB1C0 *);
extern s32 MapDataIsEnabled_1e7c20(void *);
extern f32 D_0047D1EC;
extern f32 D_0047D5D0;
}

extern "C" s32 MapAreaFindSmallestBlockContaining_1db1c0(A001DB1C0 *arg0, B001DB1C0 *arg1, f32 arg2)
{
    s32 *p;
    f32 bd;
    f32 d;
    s32 best;
    bool found;
    s32 i;

    if (((unsigned char)MapDataIsEnabled_1e7c20((void *)arg0)) == 0) {
        return 0;
    }
    if (((unsigned char)MapDataIsLoaded_1e79d0(arg0)) == 0) {
        return 0;
    }
    p = arg0->unk178;
    if (arg2 < D_0047D5D0) {
        arg2 = D_0047D5D0;
    }
    bd = D_0047D1EC;
    best = 0;
    found = false;
    for (i = 0; i < arg0->unk1CA; i++, p++) {
        if (MapBlockBoundsContainsXZ_1dfc20(*p, arg1, arg2) == 0) {
            continue;
        }
        d = MapBlockGetBoxVolume_1dfe80(*p);
        if (found) {
            if (bd <= d) {
                continue;
            }
            if (arg1->unk4 < MapBlockGetBoxBottomY_1dfe60(*p)) {
                continue;
            }
            if (MapBlockGetBoxTopY_1dfe70(*p) < arg1->unk4) {
                continue;
            }
        } else {
            if (MapBlockGetBoxBottomY_1dfe60(*p) <= arg1->unk4 && arg1->unk4 <= MapBlockGetBoxTopY_1dfe70(*p)) {
                found = true;
            } else if (bd <= d) {
                continue;
            }
        }
        best = *p;
        bd = d;
    }
    return best;
}
