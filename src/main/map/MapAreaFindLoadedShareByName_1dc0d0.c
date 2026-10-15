#include "types.h"

struct Obj {
    u8 pad000[0x128];
    void *items[1];
};

extern s32 MapDataIsLoaded_1e79d0(void *p);
extern char *MapDataGetName_1e7bf0(void *p);
extern s32 StrNotEqual_1f5300(const char *a, const char *b);

void *MapAreaFindLoadedShareByName_1dc0d0(struct Obj *o, const char *s)
{
    void **p;
    s32 i;
    char c;

    if (MapDataIsLoaded_1e79d0(o) == 0) {
        return 0;
    }
    if (s == 0) {
        return 0;
    }
    p = o->items;
    for (i = 0; i < *(s16 *)((u8 *)o + 0x1C8); i++, p++) {
        if (MapDataIsLoaded_1e79d0(*p) != 0) {
            c = *s;
            if (c == *MapDataGetName_1e7bf0(*p)) {
                if (StrNotEqual_1f5300(s + 1, MapDataGetName_1e7bf0(*p) + 1) == 0) {
                    return *p;
                }
            }
        }
    }
    return 0;
}
