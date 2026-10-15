#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(void);
extern char *MapDataGetName_1e7bf0(void *);
extern s32 StrNotEqual_1f5300(char *, char *);
extern void *MapAreaFindLoadedBlockByName_1dbd70(void *, char *);
extern void *MapAreaFindLoadedShareByName_1dc0d0(void *, char *);

void *MapAreaFindLoadedByName_1dc370(void *a0, char *a1)
{
    s32 c;
    void *r;

    if (a1 == 0) {
        return 0;
    }
    if (MapDataIsLoaded_1e79d0() == 0) {
        return 0;
    }
    c = a1[0];
    if (c == *MapDataGetName_1e7bf0(a0)) {
        if (StrNotEqual_1f5300(a1 + 1, MapDataGetName_1e7bf0(a0) + 1) == 0) {
            return a0;
        }
    }
    r = MapAreaFindLoadedBlockByName_1dbd70(a0, a1);
    if (r != 0) {
        return r;
    }
    r = MapAreaFindLoadedShareByName_1dc0d0(a0, a1);
    if (r != 0) {
        return r;
    }
    return 0;
}
