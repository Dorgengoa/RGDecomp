#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 InsectItemGetStat_3d1a10(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s8 t1;

    if (p1 >= 0) {
        if (p1 < 6) goto ok;
    }
    return 0;
ok:
    t0 = p0->m18;
    t1 = *(s8 *)((u8 *)p1 + t0 + 0x20);
    return (s32)t1;
}
