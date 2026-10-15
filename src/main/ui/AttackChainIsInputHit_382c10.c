#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x4];
    s16 m0A;
};

s32 AttackChainIsInputHit_382c10(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s16 t1;

    if (p1 >= 0) {
        t0 = p0->m04;
        if (t0 > p1) goto ok;
    }
    return 0;
ok:
    t1 = p0->m0A;
    return (s32)(p1 < t1);
}
