/* rgp:protos */
#define RGP_SELF_SunLightUpdate_293bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1FC;
extern f32 D_0047D7C4;
extern f32 D_0047D7CC;
extern f32 D_0047D858;

typedef struct O293 {
    u8 pad0[2];
    u8 m2;
    u8 pad3[0x48 - 3];
    f32 m48;
    s32 m4C;
    u8 pad50[0x150 - 0x50];
    s32 m150;
    f32 m154;
    s32 m158;
    s32 m15C;
    s32 m160;
    s32 m164;
    f32 m168;
} O293;

#pragma divbyzerocheck on

void SunLightUpdate_293bd0(O293 *arg0)
{
    f32 target;
    f32 d;
    f32 ad;
    f32 s;
    f32 r;
    f32 m;
    f32 t;
    s32 x;

    target = 1.0f;
    arg0->m2 = 1;
    if (arg0->m4C == 1) {
        target = 0.0f;
    }
    m = arg0->m48;
    d = target - m;
    d = d < 0.0f ? -d : d;
    if (d < *(volatile f32 *)&D_0047D7CC) {
        arg0->m48 = target;
    } else {
        target -= m;
        ad = target < 0.0f ? -target : target;
        arg0->m48 = arg0->m48 + D_0047D7CC * target / ad;
    }
    if (arg0->m48 < 0.0f) {
        arg0->m48 = 0.0f;
    }
    if (arg0->m150 == 3) {
        t = arg0->m154 + D_0047D7CC;
        {
            f32 a_ = D_0047D1FC + t;
            arg0->m154 = t;
            r = WrapAngle_13c050(a_);
        }
        if (!(arg0->m154 < D_0047D858)) {
            arg0->m150 = 2;
            x = Rand_133710() % arg0->m164;
            r = D_0047D1FC;
            arg0->m15C = arg0->m160 + x;
            arg0->m158 = 0;
        }
        r = Cosf_128d30(r);
        arg0->m168 = 1.0f + D_0047D7C4 * ((1.0f + r) / 2.0f);
    } else {
        arg0->m158++;
        if (arg0->m15C < arg0->m158) {
            arg0->m154 = 0.0f;
            arg0->m150 = 3;
        }
    }
}
