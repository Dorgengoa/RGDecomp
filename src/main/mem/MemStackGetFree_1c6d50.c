#include "types.h"

extern void MemStackGetStats_14d0e0(void *, void *, void *, void *, void *);

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    u8 pad018[0x10];
    s32 m28;
    s32 m2C;
    u8 pad030[0x4];
    s32 m34;
};

s32 MemStackGetFree_1c6d50(struct Obj0 *p0)
{
    s32 v1C;
    s32 v18;
    s32 v14;
    s32 v10;
    u8 ok;

    if (p0 == 0) {
        return 0;
    }
    ok = (p0->m28 != 0);
    if (ok != 0) {
        return (p0->m34 - p0->m2C);
    }
    if (p0->m14 == 0) {
        return 0;
    }
    MemStackGetStats_14d0e0(p0, &v1C, &v18, &v14, &v10);
    return v1C;
}
