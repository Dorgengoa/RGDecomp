#include "types.h"

typedef struct { f32 x, y, z; s32 w; } V_001a8580;

extern f32 VecLength_13d4a0(void *);

void MtxGetScale_1a8580(void *p, V_001a8580 *out)
{
    out->x = VecLength_13d4a0(p);
    out->y = VecLength_13d4a0((void *)((s32)p + 0x10));
    out->z = VecLength_13d4a0((void *)((s32)p + 0x20));
    out->w = 0;
}
