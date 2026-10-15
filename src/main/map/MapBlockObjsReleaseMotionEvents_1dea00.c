#include "types.h"

typedef struct E_001dea00 {
    u8 pad000[0x18];
} E_001dea00;

typedef struct Obj_001dea00 {
    u8 pad000[0xC4];
    E_001dea00 *base;
    u8 pad0C8[0x2];
    s16 count;
} Obj_001dea00;

extern s32 MapDataIsLoadedOrUnloading_1e7980(void);
extern void MapObjReleaseMotionEvents_1e07f0(E_001dea00 *e);

void MapBlockObjsReleaseMotionEvents_1dea00(Obj_001dea00 *o)
{
    s32 i;

    if (MapDataIsLoadedOrUnloading_1e7980() == 0) {
        return;
    }
    if (o->base == 0) {
        return;
    }
    for (i = 0; i < o->count; i++) {
        MapObjReleaseMotionEvents_1e07f0(&o->base[i]);
    }
}
