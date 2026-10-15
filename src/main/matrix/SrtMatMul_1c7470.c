#include "types.h"

typedef struct Sp001c7470 {
    u8 pad0[0x40];
} Sp001c7470;

extern void MatFromSRT_1caf40(Sp001c7470 *, u8 *, u8 *, u8 *);
extern void MatMul_1cb700(s32, s32, Sp001c7470 *);

void SrtMatMul_1c7470(u8 *arg0, s32 arg1, s32 arg2)
{
    u8 *base;
    Sp001c7470 sp30;

    base = arg0;
    MatFromSRT_1caf40(&sp30, base, base + 0x10, base + 0x20);
    MatMul_1cb700(arg1, arg2, &sp30);
}
