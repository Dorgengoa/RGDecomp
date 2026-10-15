#include "types.h"
struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    u8 pad024[0x4];
    s32 m28;
    s32 m2C;
    u8 pad030[0x4];
    s32 m34;
    u8 pad038[0x1C];
    s32 m54;
};
s32 MemStackAllocQw_14d950(struct Obj0 *p0, s32 p1)
{
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;
    if (p0->m20 != 0) {
        return 0;
    }
    if (p1 <= 0) {
        return 0;
    }
    t1 = p0->m2C;
    t2 = p0->m34;
    if (t2 < (t1 + p1)) {
        t3 = p0->m54;
        do {
        } while (t3 != 0);
        return 0;
    }
    t4 = p0->m28;
    t5 = t4 + (t1 << 4);
    p0->m2C = (t1 + p1);
    return t5;
}
