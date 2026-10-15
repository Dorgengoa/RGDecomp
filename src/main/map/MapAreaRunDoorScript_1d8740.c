#include "types.h"

struct Item {
    u8 pad00[0x2];
    s16 m02;
    void *m04;
};

extern void LoadHandlePollThunk_1ccb00(void *a);
extern struct Item *MapAreaLoadHandleAt_1dd120(void *a, s32 b);
extern s32 MapAreaGetFileStem_1dce70(void *a);
extern void Sprintf_1343b8(char *buf, const char *fmt, s32 a);
extern void *ArchiveGetFileByPath_1c2800(void *a, char *b, s32 *c);
extern void *MapDataGetId_1e7bd0(void *a);
extern void EventScriptRunTwoPass_2fd9d0(void *a, s32 b, void *c, void *d);
extern const char D_0045B2B8[];

s32 MapAreaRunDoorScript_1d8740(void *o)
{
    char buf[0x4C];
    s32 n;
    struct Item *it;
    void *h;
    void *r1;
    void *r2;

    LoadHandlePollThunk_1ccb00((u8 *)o + 0xA8);
    it = MapAreaLoadHandleAt_1dd120((void *)((s32)o + 0xA8), 0);
    if (it == 0) {
        return -1;
    }
    if (it->m02 == 0) {
        return 0;
    }
    Sprintf_1343b8(buf, D_0045B2B8, MapAreaGetFileStem_1dce70(o));
    h = ArchiveGetFileByPath_1c2800(it->m04, buf, &n);
    if (h == 0 || n <= 0) {
        return 1;
    }
    r1 = MapDataGetId_1e7bd0(o);
    r2 = MapDataGetId_1e7bd0(o);
    EventScriptRunTwoPass_2fd9d0(h, n, r1, r2);
    return 2;
}
