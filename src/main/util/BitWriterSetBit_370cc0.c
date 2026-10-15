#include "types.h"

typedef struct Obj00370cc0 {
    u8 pad0[0x8];
    u8 *unk8;
} Obj00370cc0;

void BitWriterSetBit_370cc0(Obj00370cc0 *arg0, s32 bit, s32 set)
{
    s32 byteIdx;
    u8 mask;

    byteIdx = bit >> 3;
    mask = (u8)(1 << (bit & 7));
    if (set != 0) {
        arg0->unk8[byteIdx] |= mask;
    } else {
        arg0->unk8[byteIdx] &= (u8)~mask;
    }
}
