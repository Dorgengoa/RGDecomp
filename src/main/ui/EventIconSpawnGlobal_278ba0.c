#include "types.h"

extern void *D_0047E9AC;
extern void EventIconSpawn_278640(void *, s32, s32, s32, s32);

void EventIconSpawnGlobal_278ba0(s32 a, s32 b, s32 c, s32 d)
{
    void *g;

    g = D_0047E9AC;
    if (g != 0) {
        EventIconSpawn_278640(g, a, b, c, d);
    }
}
