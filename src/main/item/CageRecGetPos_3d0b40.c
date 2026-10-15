#include "types.h"

typedef struct { u8 pad[0x10]; f32 f10, f14, f18; } S_003d0b40;
typedef struct { u8 pad[0x18]; S_003d0b40 *f18; } T_003d0b40;
typedef struct { f32 x, y, z, w; } V_003d0b40;

extern s32 CageRecIsPlaced_3d0d20(T_003d0b40 *);

s32 CageRecGetPos_3d0b40(T_003d0b40 *p, V_003d0b40 *out)
{
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    out->w = 1.0f;
    if (CageRecIsPlaced_3d0d20(p) == 0) return 0;
    out->x = p->f18->f10;
    out->y = p->f18->f14;
    out->z = p->f18->f18;
    return 1;
}
