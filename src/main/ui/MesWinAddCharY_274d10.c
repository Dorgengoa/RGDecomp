#include "types.h"

typedef struct { s16 v; s16 pad[3]; } E;
typedef struct { u8 pad[0xC8]; E e[0x300]; } S;

void MesWinAddCharY_274d10(S *base, s32 idx, s16 delta)
{
    if (idx < 0 || idx >= 0x300) {
        if (base) { base = (S *)(s32)(u32)base; }
    } else {
        base->e[idx].v += delta;
    }
}
