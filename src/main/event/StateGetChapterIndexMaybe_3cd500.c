#include "types.h"

typedef struct Obj003cd500 {
    u8 pad0[0x8];
    s16 unk8;
} Obj003cd500;

extern s32 StateVarGet_3ccac0(Obj003cd500 *arg0, s32 arg1);

s32 StateGetChapterIndexMaybe_3cd500(Obj003cd500 *arg0)
{
    s32 sum;

    sum = arg0->unk8;
    sum = sum + StateVarGet_3ccac0(arg0, 13);
    if (sum < 0) {
        sum = 0;
    } else if (sum >= 0x10) {
        sum = 0x10;
    }
    return sum;
}
