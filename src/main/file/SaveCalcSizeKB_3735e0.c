#include "types.h"

typedef struct Obj003735e0 {
    u8 pad00[0x6C];
    s32 unk6C;
} Obj003735e0;

extern u8 D_004658F8[0x400];

s32 SaveCalcSizeKB_3735e0(Obj003735e0 *arg0)
{
    s32 a;
    s32 b;
    s32 t;

    a = ((*(s32 *)D_004658F8) + 0x3FF) / 1024;
    b = (arg0->unk6C + 0x3FF) / 1024;
    return (u32)(a + b + 3) + 2;
}
