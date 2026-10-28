/* rgp:protos */
#define RGP_SELF_MapAreaRunDefScript_1d8830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Item {
    u8 pad00[0x2];
    s16 m02;
    void *m04;
};

/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(char *buf, const char *fmt, s32 a);
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_0045B2C8[];

s32 MapAreaRunDefScript_1d8830(void *o)
{
    char buf[0x4C] __attribute__((aligned(16)));
    s32 n;
    struct Item *it;
    void *h;
    void *r1;
    void *r2;

    LoadHandlePollThunk_1ccb00((u8 *)o + 0xA8);
    it = ((struct Item *)MapAreaLoadHandleAt_1dd120((void *)((s32)o + 0xA8), 0));
    if (it == 0) {
        return -1;
    }
    if (it->m02 == 0) {
        return 0;
    }
    Sprintf_1343b8(buf, D_0045B2C8, MapAreaGetFileStem_1dce70(o));
    h = ArchiveGetFileByPath_1c2800(it->m04, buf, &n);
    if (h == 0 || n <= 0) {
        return 1;
    }
    r1 = MapDataGetId_1e7bd0(o);
    r2 = MapDataGetId_1e7bd0(o);
    EventScriptRunTwoPass_2fd9d0(h, n, r1, r2);
    return 2;
}
