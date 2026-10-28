#include "types.h"

struct S23A {
    u8  pad000[0x70];
    f32 f70;
    f32 f74;
    f32 f78;
    s32 f7C;
};

struct V23A {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

extern "C" s32 CharaHangLedgeGetPos_23a230(struct S23A *p, struct V23A *d)
{
    bool ok;

    ok = !(p->f7C & 0x80000000);
    if (ok) goto payload;
    return 0;
payload:
    d->x = p->f70;
    d->y = p->f74;
    d->z = p->f78;
    d->w = 1.0f;
    return 1;
}
