#include "types.h"

typedef struct { u8 pad[0x18]; } E_001de980;
typedef struct { u8 pad[0xC4]; E_001de980 *fC4; u8 pad2[2]; s16 fCA; } T_001de980;

extern s32 MapDataIsLoadedOrUnloading_1e7980(T_001de980 *);
extern void MapObjStep_1e0660(E_001de980 *, f32);

void MapBlockStepObjs_1de980(T_001de980 *p, f32 v)
{
    s32 i;

    if (MapDataIsLoadedOrUnloading_1e7980(p) == 0) return;
    if (p->fC4 == 0) return;
    for (i = 0; i < p->fCA; i++) {
        MapObjStep_1e0660(&p->fC4[i], v);
    }
}
