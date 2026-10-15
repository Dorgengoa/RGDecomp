#include "types.h"

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    struct Obj1 *m04;
};

struct Obj1 {
    s32 m00;
};

s32 HandleRegistryFind_3150e0(s32 p0, s32 p1)
{
    struct Obj0 *l0;
    s32 l1;
    struct Obj1 *t0;
    s32 ok;
    s32 t1;
    s32 rv2;

    l0 = (struct Obj0 *)p0;
    l1 = 0;
    while (l1 < 0x200) {
        t0 = l0->m04;
        ok = !t0;
        if (ok == 0) {
            t1 = l0->m00;
            if (t1 == p1) {
                if (t0 != 0) {
                    rv2 = t0->m00;
                } else {
                    rv2 = 0;
                }
                return rv2;
            }
        }
        l1 = (l1 + 1);
        l0 = (struct Obj0 *)((u8 *)l0 + 8);
    }
    return 0;
}
