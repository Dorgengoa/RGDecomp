#include "types.h"

class V41c {
public:
    virtual void s08();
    virtual void s0C();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1C();
    virtual void s20();
    u8 pad04[0x94];
};

struct O41c { u8 pad00[0xC]; V41c *arr; };
struct S41c { u8 pad00[0x10]; s16 m10; };

extern struct BigD41c { s32 v; s32 pad[3]; } D_004644A8;

extern "C" s32 WorldSubsysZoneEntryRelease_41c400(O41c *o, S41c *p)
{
    V41c *arr;
    s32 i;

    if (p == 0) {
        return 0;
    }
    i = p->m10;
    if (i < 0) {
        goto none;
    }
    if (i < D_004644A8.v) {
        goto ok;
    }
none:
    return 0;
ok:
    arr = o->arr;
    if (arr != 0) {
        arr[i].s20();
    }
    return 1;
}
