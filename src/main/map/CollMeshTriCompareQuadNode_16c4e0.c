#include "types.h"
typedef struct P16C4E0 { u8 pad000[0x8]; u32 m8; } P16C4E0;
s32 CollMeshTriCompareQuadNode_16c4e0(P16C4E0 *a, P16C4E0 *b)
{
    u32 x;
    u32 y;

    x = a->m8;
    y = b->m8;
    if (x < y) return -1;
    return y < x;
}
