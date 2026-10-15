#include "types.h"

s32 ObjRecClearFlag2_1c3e40(s32, s32, s32);
s32 ObjRecSetFlag2_1c3e80(s32, s32, s32);

void ObjRecFlagsSnapshotPop_1d76a0(u8 *arg0, s32 arg1)
{
    s32 i;
    s32 b;
    s32 m;
    u8 *p;

    if (*arg0 > 0) {
        *arg0 = *arg0 - 1;
        for (i = 0; i < 0xE0; i++) {
            b = (arg0 + *arg0 * 0x1C)[i / 8 + 1];
            if (b & (1 << (i % 8))) {
                ObjRecSetFlag2_1c3e80(arg1, 1, i);
            } else {
                ObjRecClearFlag2_1c3e40(arg1, 1, i);
            }
        }
        p = arg0 + *arg0 * 0x1C;
        for (i = 0; i < 0x1C; i++) {
            p[i + 1] = 0;
        }
    }
}
