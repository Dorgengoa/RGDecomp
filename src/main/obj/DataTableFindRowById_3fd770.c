#include "types.h"

struct Obj0 {
    u8 pad000[0x7C];
    s16 m7C;
    u8 pad07E[0xE];
    s32 m8C;
};

struct Obj1 {
    u8 pad000[0x8];
    s16 m08;
};

s32 DataTableFindRowById_3fd770(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 n;
    struct Obj1 *l0;
    s32 l1;
    s16 t2;

    t0 = p0->m8C;
    if (t0 != 0) {
        n = p0->m7C;
        if (n > 0) {
            goto ok;
        }
    }
    return 0;
ok:
    l0 = (struct Obj1 *)t0;
    l1 = 0;
    while (l1 < n) {
        t2 = l0->m08;
        if (t2 == (s16)p1) {
            return (s32)l0;
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 0x20);
    }
    return 0;
}
