#include "types.h"

extern void memset(s32, s32, s32);

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x14];
    s32 m1C;
    s32 m20;
    s32 m24;
};

void PoolClear_36ade0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 t4;

    t0 = p0->m00;
    if (t0 != 0) {
        t1 = p0->m04;
        if (t1 > 0) {
            memset(t0, 0, t1);
        }
    }
    rv1 = p0->m20;
    if (rv1 != 0) {
        t4 = p0->m24;
        if (t4 > 0) {
            memset(rv1, 0, t4);
        }
    }
    p0->m1C = 0;
}
