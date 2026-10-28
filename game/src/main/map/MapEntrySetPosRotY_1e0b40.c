/* rgp:protos */
#define RGP_SELF_MapEntrySetPosRotY_1e0b40 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct B30 { s32 i0; f32 f4; s32 i8; s32 iC; } B30;
/*rgp*/
/*rgp*/
extern f32 D_0047E3A0;
extern f32 D_0047E3A4;
extern f32 D_0047E3A8;
extern f32 D_0047E3AC;

void MapEntrySetPosRotY_1e0b40(s32 arg0, f32 x, f32 y, f32 z, f32 w)
{
    f32 v[4] __attribute__((aligned(16)));
    f32 *qv = v;
    B30 b __attribute__((aligned(16)));
    u8 *p;
    u32 n;


    qv[0] = D_0047E3A0;
    qv[1] = D_0047E3A4;
    qv[2] = D_0047E3A8;
    qv[3] = D_0047E3AC;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    ModelSetPos_151110(arg0, v);
    p = (u8 *)&b;
    n = 0x10;
    if (p != NULL) {
        do {
            *p = 0;
            n -= 1;
            p += 1;
        } while (n != 0);
    }
    b.f4 = w;
    b.i0 = 0;
    b.i8 = 0;
    ModelSetRot_151080(arg0, &b);
}
