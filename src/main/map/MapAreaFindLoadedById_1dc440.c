#include "types.h"

extern s32   MapDataIsLoaded_1e79d0(void);
extern s32   MapDataGetId_1e7bd0(void *self);
extern void *MapAreaFindLoadedBlockById_1dbe50(void *self, s32 idx);
extern void *MapAreaFindLoadedShareById_1dc1b0(void *self, s32 idx);

void *MapAreaFindLoadedById_1dc440(void *self, s32 idx)
{
    void *r;

    if (idx < 0) {
        return NULL;
    }
    if (MapDataIsLoaded_1e79d0() == 0) {
        return NULL;
    }
    if (idx == MapDataGetId_1e7bd0(self)) {
        return self;
    }
    r = MapAreaFindLoadedBlockById_1dbe50(self, idx);
    if (r != NULL) {
        return r;
    }
    r = MapAreaFindLoadedShareById_1dc1b0(self, idx);
    if (r != NULL) {
        return r;
    }
    return NULL;
}
