#include "types.h"

typedef struct { s32 pad[12]; s32 f30; } T_001e7670;

extern f32 MapDataGetRotY_1e7710(void *);
extern void MatRotY_1cb200(void *, f32);
extern void MapDataGetPosVec4_1e7740(void *, void *);

void MapDataGetMatrix_1e7670(void *a, T_001e7670 *b)
{
    f32 v;

    v = MapDataGetRotY_1e7710(a);
    MatRotY_1cb200(b, v);
    MapDataGetPosVec4_1e7740(a, &b->f30);
}
