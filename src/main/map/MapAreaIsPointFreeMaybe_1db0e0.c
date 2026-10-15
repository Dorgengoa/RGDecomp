#include "types.h"

extern s32 MapAreaGetBoxCount_1dcdd0(s32);
extern s32 MapAreaGetBoxes_1dcde0(void);
extern s32 MapBoxGetNumMaybe_1ddf00(s32);
extern s32 AreaBoxContainsPoint_1e93c0(s32, s32, f32);
extern f32 D_0047D5D0;

s32 MapAreaIsPointFreeMaybe_1db0e0(s32 arg0, s32 arg1, f32 f)
{
    s32 p;
    s32 n;
    s32 i;

    p = MapAreaGetBoxes_1dcde0();
    if (p == 0) {
        return 1;
    }
    n = MapAreaGetBoxCount_1dcdd0(arg0);
    if (n > 0) goto L1;
    return 1;
L1:
    if (f < D_0047D5D0) {
        f = D_0047D5D0;
    }
    i = 0;
    while (i < n) {
        if (MapBoxGetNumMaybe_1ddf00(p) < 0 && AreaBoxContainsPoint_1e93c0(p, arg1, f) != 0) {
            return 0;
        }
        i++;
        p += 0x50;
    }
    return 1;
}
