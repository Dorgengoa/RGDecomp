#include "types.h"

extern void *GetMapMgr_201a90(void);
extern void *EvObjGetAreaId_2f8f30(u8 *);
extern void MapSetDataFlag4ById_1e4d30(void *, void *, s32);

void EvObjAreaFadeLock_2f8e40(u8 *p)
{
    void *a;

    if (*(f32 *)(p + 0xE4) < 1.0f) {
        a = GetMapMgr_201a90();
        MapSetDataFlag4ById_1e4d30(a, EvObjGetAreaId_2f8f30(p), 1);
    }
}
