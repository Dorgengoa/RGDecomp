/* rgp:protos */
#define RGP_SELF_EventIconSpawnGlobal_278ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_0047E9AC;
/*rgp*/

void EventIconSpawnGlobal_278ba0(s32 a, s32 b, s32 c, s32 d)
{
    void *g;

    g = D_0047E9AC;
    if (g != 0) {
        EventIconSpawn_278640(g, a, b, c, d);
    }
}
