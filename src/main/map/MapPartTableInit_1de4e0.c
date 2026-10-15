#include "types.h"

extern void MapPartTableReset_1de6c0(void *);
extern s32 MemStackNew_14e1b0(s32, s32);

struct Obj0 {
    s16 m00;
    u8 pad002[0x2];
    s32 m04;
    u8 pad008[0x2];
    s16 m0A;
};

s32 MapPartTableInit_1de4e0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 r1;

    MapPartTableReset_1de6c0(p0);
    if (p2 > 0) {
        if (p3 != 0) {
            goto ok;
        }
    }
    return 0;
ok:
    p0->m00 = p1;
    r1 = MemStackNew_14e1b0((p2 << 2), p3);
    p0->m04 = r1;
    if (r1 == 0) {
        return 0;
    }
    p0->m0A = p2;
    return 1;
}
