#include "types.h"

typedef struct { f32 x, y, z, w; } V4;

extern void MatFromSRT_1caf40(s32, V4 *, V4 *, V4 *);
extern V4 D_0047F030 __attribute__((section(".sdata")));
extern V4 D_0047F040 __attribute__((section(".sdata")));
extern V4 D_0047F050 __attribute__((section(".sdata")));

void EvSwitchRecBuildMatrix_2f8750(f32 *arg0, s32 arg1) {
    V4 a;
    V4 b;
    V4 c;

    *(V4 *)&a = D_0047F030;
    a.x = arg0[6];
    a.y = arg0[7];
    a.z = arg0[8];
    *(V4 *)&b = D_0047F040;
    b.x = arg0[3];
    b.y = arg0[4];
    b.z = arg0[5];
    *(V4 *)&c = D_0047F050;
    c.x = arg0[0];
    c.y = arg0[1];
    c.z = arg0[2];
    MatFromSRT_1caf40(arg1, &c, &b, &a);
}
