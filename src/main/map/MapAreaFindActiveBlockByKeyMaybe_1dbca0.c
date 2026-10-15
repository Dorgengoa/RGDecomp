#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(void);
extern s32 MapIdIndexGetMinId_1ddbe0(void *);
extern s32 MapIdIndexGetMaxId_1ddbf0(void *);
extern s32 MapDataIsLoadedOrUnloading_1e7980(void *);
extern s32 MapDataGetKeyMaybe_1e7bc0(void *);

void *MapAreaFindActiveBlockByKeyMaybe_1dbca0(void *p0, s32 key)
{
    void **pp;
    s32 i;

    if (MapDataIsLoaded_1e79d0() == 0) {
        return 0;
    }
    if (key < MapIdIndexGetMinId_1ddbe0((u8 *)p0 + 0x10C) || MapIdIndexGetMaxId_1ddbf0((void *)((s32)p0 + 0x10C)) < key) {
        return 0;
    }
    pp = (void **)((u8 *)p0 + 0x178);
    i = 0;
    while (i < *(s16 *)((u8 *)p0 + 0x1CA)) {
        if (MapDataIsLoadedOrUnloading_1e7980(*pp) != 0) {
            if (key == MapDataGetKeyMaybe_1e7bc0(*pp)) {
                return *pp;
            }
        }
        i++;
        pp++;
    }
    return 0;
}
