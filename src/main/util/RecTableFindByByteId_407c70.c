#include "types.h"

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x1];
    u8 m01;
    u8 pad002[0x2];
    s32 m04;
};

struct Obj1 {
    u8 m00;
};

s32 RecTableFindByByteId_407c70(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    struct Obj1 *l0;
    s32 l1;
    u8 t2;

    t0 = p0->m01;
    t1 = p0->m04;
    l0 = (struct Obj1 *)t1;
    l1 = 0;
    while (l1 < t0) {
        t2 = l0->m00;
        if (t2 == p1) {
            return (s32)l0;
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 6);
    }
    return 0;
}
