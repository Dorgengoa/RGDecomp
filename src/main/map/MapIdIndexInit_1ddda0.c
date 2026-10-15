#include "types.h"

struct Obj0 { s32 m00; s32 m04; u8 pad008[0x4]; s16 m0C; s16 m0E; };

extern void MapIdIndexReset_1dde60(struct Obj0 *);
extern s32 MemStackNew_14e1b0(s32, s32);

s32 MapIdIndexInit_1ddda0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r1;
    s32 r2;

    MapIdIndexReset_1dde60(p0);
    if (p2 == 0) {
        return 0;
    }
    if (p1 > 0) {
        goto ok;
    }
    return 1;
ok:
    r1 = MemStackNew_14e1b0((p1 << 2), p2);
    p0->m00 = r1;
    r2 = MemStackNew_14e1b0((p1 << 2), p2);
    p0->m04 = r2;
    p0->m0C = 1;
    while (p1 >= p0->m0C) {
        p0->m0C <<= 1;
    }
    p0->m0E = p1;
    return 1;
}
