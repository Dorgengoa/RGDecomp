#include "types.h"

extern s32 MapDataIsStreamActive_1e7920(void);
extern char *MapDataGetName_1e7bf0(void *);
extern s32 StrNotEqual_1f5300(char *, char *);
extern void *MapAreaFindShareByName_1dc7c0(void *, char *);
extern void *MapAreaFindBlockByName_1dc700(void *, char *);

void *MapAreaFindByName_1dc880(void *a0, char *a1)
{
    s32 c;
    void *r;

    if (a1 == 0) {
        return 0;
    }
    if (MapDataIsStreamActive_1e7920() == 0) {
        return 0;
    }
    c = a1[0];
    if (c == *MapDataGetName_1e7bf0(a0)) {
        if (StrNotEqual_1f5300(a1 + 1, MapDataGetName_1e7bf0(a0) + 1) == 0) {
            return a0;
        }
    }
    r = MapAreaFindShareByName_1dc7c0(a0, a1);
    if (r != 0) {
        return r;
    }
    r = MapAreaFindBlockByName_1dc700(a0, a1);
    if (r != 0) {
        return r;
    }
    return 0;
}
