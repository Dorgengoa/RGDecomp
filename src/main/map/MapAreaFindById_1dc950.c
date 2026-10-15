#include "types.h"

extern s32   MapDataIsStreamActive_1e7920(void);
extern s32   MapDataGetId_1e7bd0(void *self);
extern void *MapAreaFindShareById_1dc820(void *self, s32 idx);
extern void *MapAreaFindBlockById_1dc760(void *self, s32 idx);

void *MapAreaFindById_1dc950(void *self, s32 idx)
{
    void *r;

    if (idx < 0) {
        return NULL;
    }
    if (MapDataIsStreamActive_1e7920() == 0) {
        return NULL;
    }
    if (idx == MapDataGetId_1e7bd0(self)) {
        return self;
    }
    r = MapAreaFindShareById_1dc820(self, idx);
    if (r != NULL) {
        return r;
    }
    r = MapAreaFindBlockById_1dc760(self, idx);
    if (r != NULL) {
        return r;
    }
    return NULL;
}
