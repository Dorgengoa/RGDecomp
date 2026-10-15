#include "types.h"

struct Obj0 {
    u8 pad000[0x2];
    u8 m02_b0 : 1;
    u8 m02_b1 : 7;
};

s32 StatusEntryClearStartPending_3a5fb0(struct Obj0 *p0, s32 p1)
{
    if (p1 == 0) {
        if (p0->m02_b0 == 0) {
            return 0;
        }
    }
    p0->m02_b0 = 0;
    return 1;
}
