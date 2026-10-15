#include "types.h"

struct C0 {
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
};

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
};

struct Obj1 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
};

extern "C" s32 WorldSubsysPlanetEntryRelease_41fc70(struct Obj1 *p0, struct Obj0 *p1)
{
    s16 n;
    s32 t;

    if (p1 == 0) {
        return 0;
    }
    n = p1->m08;
    if (n >= 0) {
        if (n < 2) {
            goto ok;
        }
    }
    return 0;
ok:
    t = p0->m08;
    if (t != 0) {
        ((struct C0 *)(t + ((n * 3) << 6)))->v6();
    }
    t = p0->m0C;
    if (t != 0) {
        ((struct C0 *)(t + ((n * 19) << 3)))->v6();
    }
    return 1;
}
