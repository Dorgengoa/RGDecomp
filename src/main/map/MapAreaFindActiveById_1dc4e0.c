#include "types.h"

extern s32   MapDataIsLoadedOrUnloading_1e7980(void);
extern s32   MapDataGetId_1e7bd0(void *self);
extern void *MapAreaFindActiveBlockById_1dbf20(void *self, s32 idx);
extern void *MapAreaFindActiveShareById_1dc280(void *self, s32 idx);

void *MapAreaFindActiveById_1dc4e0(void *self, s32 idx)
{
    void *r;

    if (idx < 0) {
        return NULL;
    }
    if (MapDataIsLoadedOrUnloading_1e7980() == 0) {
        return NULL;
    }
    if (idx == MapDataGetId_1e7bd0(self)) {
        return self;
    }
    r = MapAreaFindActiveBlockById_1dbf20(self, idx);
    if (r != NULL) {
        return r;
    }
    r = MapAreaFindActiveShareById_1dc280(self, idx);
    if (r != NULL) {
        return r;
    }
    return NULL;
}
