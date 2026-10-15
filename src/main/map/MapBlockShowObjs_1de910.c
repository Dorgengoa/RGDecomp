#include "types.h"

typedef struct E_001de910 {
    u8 pad000[0x18];
} E_001de910;

typedef struct Obj_001de910 {
    u8 pad000[0xC4];
    E_001de910 *base;
    u8 pad0C8[0x2];
    s16 count;
} Obj_001de910;

extern s32 MapDataIsLoadedOrUnloading_1e7980(void);
extern void MapObjShow_1e05e0(E_001de910 *e);

void MapBlockShowObjs_1de910(Obj_001de910 *o)
{
    s32 i;

    if (MapDataIsLoadedOrUnloading_1e7980() == 0) {
        return;
    }
    if (o->base == 0) {
        return;
    }
    for (i = 0; i < o->count; i++) {
        MapObjShow_1e05e0(&o->base[i]);
    }
}
