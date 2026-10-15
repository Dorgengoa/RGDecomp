#include "types.h"

typedef struct Obj00311660 {
    s16 unk0;
    s16 unk2;
    u8 pad4[0xE - 0x4];
    s16 unkE;
    s16 unk10;
} Obj00311660;

s32 NavEdgeGetDirFlag_311660(Obj00311660 *arg0, s32 arg1, s32 arg2)
{
    if (arg0->unk0 == arg1 && arg0->unk2 == arg2) {
        return arg0->unkE != 0;
    }
    if (arg0->unk0 == arg2 && arg0->unk2 == arg1) {
        return arg0->unk10 != 0;
    }
    return 0;
}
