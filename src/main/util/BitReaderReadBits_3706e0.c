#include "types.h"

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s16 m00;
    u8 pad002[0x6];
    s32 m08;
};

s32 BitReaderReadBits_3706e0(struct Obj1 *p0, struct Obj0 *p1, s32 p2)
{
    s32 l1;
    s32 l0;
    s16 t0;
    s32 t1;
    u8 bit;
    u8 byte;
    u8 hit;
    s32 t3;

    p1->m00 = 0;
    l0 = 0;
    l1 = 1;
    while (l0 < p2) {
        t0 = p0->m00;
        p0->m00 = (t0 + 1);
        t1 = p0->m08;
        bit = (u8)(1 << (t0 & 7));
        byte = *(u8 *)((u8 *)t1 + (t0 >> 3));
        hit = ((byte & bit) != 0);
        if (hit != 0) {
            t3 = p1->m00;
            p1->m00 = (t3 | l1);
        }
        l1 = (l1 << 1);
        l0 = (l0 + 1);
    }
    return p2;
}
