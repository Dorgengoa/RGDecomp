#include "types.h"
#pragma optimization_level 3

typedef struct { u8 pad[0x32]; s16 unk32; } T3e4;
s16 GameDataFlagsSetOrClear_3e4580(T3e4 *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        arg0->unk32 |= (s16)arg1;
    } else {
        arg0->unk32 &= (s16)~arg1;
    }
    return arg0->unk32;
}
