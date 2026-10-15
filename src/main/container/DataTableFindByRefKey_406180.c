#include "types.h"

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x7C];
    s16 m7C;
    u8 pad07E[0xE];
    s32 m8C;
};

struct Obj1 {
    u8 pad000[0x4];
    struct Obj2 *m04;
};

struct Obj2 {
    s16 m00;
};

s32 DataTableFindByRefKey_406180(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;
    struct Obj1 *l0;
    s32 l1;
    struct Obj2 *t2;
    s16 t3;
    s16 key;

    t0 = p0->m8C;
    if (t0 != 0) {
        t1 = p0->m7C;
        if (t1 > 0) goto ok;
    }
    return 0;
ok:
    key = (s16)p1;
    l0 = (struct Obj1 *)t0;
    l1 = 0;
    while (l1 < t1) {
        t2 = l0->m04;
        if (t2 != 0) {
            t3 = t2->m00;
            if (t3 == key) {
                return (s32)l0;
            }
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 0x18);
    }
    return 0;
}
