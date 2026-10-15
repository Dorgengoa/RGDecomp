#include "types.h"

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x270];
    struct Obj1 *m270;
};

struct Obj1 {
    u8 pad000[0x24];
    s32 m24;
    s32 m28;
};

void DrawEnvSetVsyncInterval_144140(struct Obj0 *p0, s32 a5, s32 a6)
{
    struct Obj1 * t0;

    t0 = p0->m270;
    t0->m24 = a5;
    t0->m28 = a6;
}
