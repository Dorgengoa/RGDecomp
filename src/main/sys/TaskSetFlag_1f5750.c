#include "types.h"

struct Obj0 { u8 pad000[0xC]; u16 m0C; };

void TaskSetFlag_1f5750(struct Obj0 *p0, s32 p1, s32 p2)
{
    u16 m;

    if (p1 != 0) {
        m = 1 << p2;
        p0->m0C = p0->m0C | m;
        return;
    }
    m = ~(1 << p2);
    p0->m0C = p0->m0C & m;
}
