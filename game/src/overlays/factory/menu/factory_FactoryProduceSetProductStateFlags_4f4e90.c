/* rgp:protos */
#define RGP_SELF_factory_FactoryProduceSetProductStateFlags_4f4e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct World {
    u8    pad00[0x10];
    void *f10;
} World;

/*rgp*/
/*rgp*/

void factory_FactoryProduceSetProductStateFlags_4f4e90(void *w, s32 id)
{
    World *g;
    void  *h;

    if (id != 0x418F && id != 0x3ECF && id != 0x4177) {
        return;
    }
    g = ((World *)GetGameData_1fede0());
    if (g == 0) {
        return;
    }
    h = g->f10;
    if (h == 0) {
        return;
    }
    if (id == 0x418F) {
        StateFlagSet_3ccb70(h, 0x492, 1, 0);
        StateFlagSet_3ccb70(h, 0x493, 1, 0);
    } else if (id == 0x3ECF) {
        StateFlagSet_3ccb70(h, 0x5AE, 1, 0);
    } else if (id == 0x4177) {
        StateFlagSet_3ccb70(h, 0x596, 1, 0);
    }
}
