#include "types.h"

typedef struct World {
    u8    pad00[0x10];
    void *f10;
} World;

extern World *func_1FEDE0(void);
extern void   func_3CCB70(void *h, s32 id, s32 a, s32 b);

void factory_FactoryProduceSetProductStateFlags_4f4e90(void *w, s32 id)
{
    World *g;
    void  *h;

    if (id != 0x418F && id != 0x3ECF && id != 0x4177) {
        return;
    }
    g = func_1FEDE0();
    if (g == 0) {
        return;
    }
    h = g->f10;
    if (h == 0) {
        return;
    }
    if (id == 0x418F) {
        func_3CCB70(h, 0x492, 1, 0);
        func_3CCB70(h, 0x493, 1, 0);
    } else if (id == 0x3ECF) {
        func_3CCB70(h, 0x5AE, 1, 0);
    } else if (id == 0x4177) {
        func_3CCB70(h, 0x596, 1, 0);
    }
}
