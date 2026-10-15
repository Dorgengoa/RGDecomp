#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4;

extern void MapSequencerAddMoveReq_2fa150(s32, s32, s32, V4 *, V4 *);
extern V4 D_0047F070 __attribute__((section(".sdata")));
extern V4 D_0047F080 __attribute__((section(".sdata")));

void MapSequencerAddMoveReqXyz_2fa0d0(s32 a0, s32 a1, s32 a2, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1) {
    V4 a;
    V4 b;

    *(V4 *)&a = D_0047F070;
    a.x = x0;
    a.y = y0;
    a.z = z0;
    *(V4 *)&b = D_0047F080;
    b.x = x1;
    b.y = y1;
    b.z = z1;
    MapSequencerAddMoveReq_2fa150(a0, a1, a2, &a, &b);
}
