#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(void);
extern s32 MapIdIndexGetMinId_1ddbe0(void *);
extern s32 MapIdIndexGetMaxId_1ddbf0(void *);
extern s32 MapDataIsLoadedOrUnloading_1e7980(void *);
extern s32 MapDataGetId_1e7bd0(void *);

void *MapAreaFindActiveShareById_1dc280(void *p0, s32 key)
{
    void **pp;
    s32 i;

    if (MapDataIsLoaded_1e79d0() == 0) {
        return 0;
    }
    if (key < MapIdIndexGetMinId_1ddbe0((u8 *)p0 + 0xFC) || MapIdIndexGetMaxId_1ddbf0((void *)((s32)p0 + 0xFC)) < key) {
        return 0;
    }
    pp = (void **)((u8 *)p0 + 0x128);
    i = 0;
    while (i < *(s16 *)((u8 *)p0 + 0x1C8)) {
        if (MapDataIsLoadedOrUnloading_1e7980(*pp) != 0) {
            if (key == MapDataGetId_1e7bd0(*pp)) {
                return *pp;
            }
        }
        i++;
        pp++;
    }
    return 0;
}
