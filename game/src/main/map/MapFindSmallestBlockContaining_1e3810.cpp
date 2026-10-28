/* rgp:protos */
#line 1
#include "types.h"

typedef struct Arg {
    f32 x0;
    f32 x4;
} Arg;

extern "C" {
extern s32 MapAreaFindSmallestBlockContaining_1db1c0(u8 *, Arg *, f32);
extern f32 MapBlockGetBoxBottomY_1dfe60(s32);
extern f32 MapBlockGetBoxTopY_1dfe70(s32);
extern f32 MapBlockGetBoxVolume_1dfe80(s32);
extern s32 MapGetAreaSlot2_1e5740(int);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 MapDataIsEnabled_1e7c20(s32);
}
extern "C" f32 D_0047D1EC;

extern "C" s32 MapFindSmallestBlockContaining_1e3810(u8 *arg0, Arg *arg1, f32 f)
{
    s32 r;
    bool found;
    u8 *p;
    s32 best;
    s32 i;
    s32 e;
    f32 bd;
    f32 d;

    r = MapGetAreaSlot2_1e5740((int)arg0);
    if (r != 0 && ((unsigned char)MapDataIsEnabled_1e7c20(r)) != 0 && ((unsigned char)MapDataIsLoaded_1e79d0(r)) != 0) {
        return r;
    }
    bd = D_0047D1EC;
    p = arg0 + 0x1928;
    found = false;
    best = 0;
    for (i = 0; i < 4; i++, p += 0x1CC) {
        if (i == 2) {
            continue;
        }
        e = MapAreaFindSmallestBlockContaining_1db1c0(p, arg1, f);
        if (e == 0) {
            continue;
        }
        d = MapBlockGetBoxVolume_1dfe80(e);
        if (found) {
            if (bd <= d) {
                continue;
            }
            if (arg1->x4 < MapBlockGetBoxBottomY_1dfe60(e)) {
                continue;
            }
            if (MapBlockGetBoxTopY_1dfe70(e) < arg1->x4) {
                continue;
            }
        } else {
            if (MapBlockGetBoxBottomY_1dfe60(e) <= arg1->x4 && arg1->x4 <= MapBlockGetBoxTopY_1dfe70(e)) {
                found = true;
            } else if (bd <= d) {
                continue;
            }
        }
        bd = d;
        best = e;
    }
    return best;
}
