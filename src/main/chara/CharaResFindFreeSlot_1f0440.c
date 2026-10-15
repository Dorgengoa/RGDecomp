#include "types.h"

typedef struct { u8 pad[0x64]; s16 f64; s16 pad2; } E;

#pragma opt_propagation off
void *CharaResFindFreeSlot_1f0440(E *p)
{
    s32 i;
    for (i = 0; i < 0x20; i++, p++) {
        s32 nz = p->f64 != 0;
        if (!nz) return p;
    }
    return 0;
}
