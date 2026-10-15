#include "types.h"

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x64];
    s32 m64;
};

struct Obj1 {
    u8 pad000[0x4];
    s32 m04;
    s16 m08;
};

s32 CharaDataSubRecFindNode_1ee690(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    struct Obj1 *l0;
    s16 t1;
    s32 t2;

    t0 = p0->m64;
    l0 = (struct Obj1 *)t0;
    if (l0 == 0) {
        return 0;
    }
    while (l0 != 0) {
        t1 = l0->m08;
        if (p1 == t1) {
            return (s32)l0;
        }
        t2 = l0->m04;
        l0 = (struct Obj1 *)t2;
    }
    return 0;
}
