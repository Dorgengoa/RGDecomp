#include "types.h"

extern s32 MapBlockBoxListHitInclude_1e02e0(void *, s32, f32);
extern s32 MapDataIsEnabled_1e7c20(void);
extern s32 AreaBoxContainsPointThunk_1e93c0(void *, s32, f32);

s32 MapBlockContainsPoint_1dfb80(void *arg0, s32 arg1, f32 fparg0) {
    s32 arg_h2;

    if (!(MapDataIsEnabled_1e7c20() != 0)) {
        return 0;
    }
    if (MapBlockBoxListHitInclude_1e02e0((u8 *)arg0 + 0x54, arg1, fparg0) != 0) {
        return 1;
    }
    {
        if ((*(s32 *)((u8 *)arg0 + 0x2C) & 0x100) && (AreaBoxContainsPointThunk_1e93c0((u8 *)arg0 + 0x74, arg1, fparg0) != 0)) {
            return 1;
        }
        return 0;
    }
}
