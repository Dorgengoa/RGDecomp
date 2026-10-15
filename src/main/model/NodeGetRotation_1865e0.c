#include "types.h"

typedef unsigned __int128 u128;

typedef union V186 {
    u128 q;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } v;
} V186;

typedef struct S186 {
    u8  pad000[0xC];
    f32 f0C;
    f32 f10;
    f32 f14;
    u8  pad018[0x18];
    s16 f30;
} S186;

void NodeGetRotation_1865e0(S186 *p, V186 *d)
{
    if (p->f30 != 0) {
        d->q = 0;
    } else {
        d->v.x = p->f0C;
        d->v.y = p->f10;
        d->v.z = p->f14;
        d->v.w = 0.0f;
    }
}
