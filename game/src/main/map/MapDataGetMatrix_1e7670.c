/* rgp:protos */
#define RGP_SELF_MapDataGetMatrix_1e7670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 pad[12]; s32 f30; } T_001e7670;

/*rgp*/
/*rgp*/
/*rgp*/

void MapDataGetMatrix_1e7670(void *a, T_001e7670 *b)
{
    f32 v;

    v = MapDataGetRotY_1e7710(a);
    MatRotY_1cb200(b, v);
    MapDataGetPosVec4_1e7740(a, &b->f30);
}
