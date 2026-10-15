#include "types.h"

typedef struct S002107c0 {
    u8 pad0[0x3D0];
    u64 unk3D0;
    u8 pad3D8[0xA36 - 0x3D8];
    s16 unkA36;
    s16 unkA38;
    u8 pad3A[0xA44 - 0xA3A];
    u32 unkA44;
} S002107c0;

s32 CharaCanPickFrontTargetMaybe_2107c0(S002107c0 *arg0)
{
    s32 r;
    if ((((arg0->unk3D0 & 0x0080000000000000ULL) != 0) ^ 1) == 0) return 0;
    if (arg0->unkA44 & 0x01000000) goto one;
    if (arg0->unkA38 == 0) return 0;
    if (arg0->unkA36 != 0x12) return 0;
one:
    return 1;
}
