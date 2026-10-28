/* rgp:protos */
#define RGP_SELF_CollBuildWallTrisMaybe_16d550 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);

s32 CollBuildWallTrisMaybe_16d550(u8 *arg0, s32 arg1, Vec4 *arg2, Vec4 *arg3, f32 lim, f32 s)
{
    Vec4 d __attribute__((aligned(16)));
    Vec4 q __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Vec4 e __attribute__((aligned(16)));
    f32 f;

    if (arg1 > 0 && arg1 < 2) {
        return 0;
    }
    VecSub_13be40(&d, arg3, arg2);
    d.y = 0.0f;
    f = VecLength_13d4a0(&d);
    if (!(f <= lim)) {
        f = lim;
    }
    if (f < lim) {
        f -= 1.0f;
    }
    VecNormalize_13bd90(&d, &d);
    a.x = -d.z * s;
    a.y = s;
    a.z = d.x * s;
    a.w = 1.0f;
    *(u128 *)&b = *(u128 *)&a;
    *(u128 *)&c = *(u128 *)&a;
    b.x = -a.x;
    b.z = -a.z;
    c.y = -s;
    *(u128 *)&e = *(u128 *)&b;
    e.y = -s;
    VecScale_13be00(&q, &d, f);
    VecAdd_13be20(&q, &q, arg2);
    VecAdd_13be20(&a, &a, &q);
    VecAdd_13be20(&b, &b, &q);
    VecAdd_13be20(&c, &c, &q);
    VecAdd_13be20(&e, &e, &q);
    memset(arg0 + 0x40, 0, 0x14);
    *(Vec4 *)(arg0 + 0x00) = a;
    *(Vec4 *)(arg0 + 0x10) = b;
    *(Vec4 *)(arg0 + 0x20) = c;
    *(Vec4 *)(arg0 + 0x30) = d;
    memset(arg0 + 0xA0, 0, 0x14);
    *(Vec4 *)(arg0 + 0x60) = c;
    *(Vec4 *)(arg0 + 0x70) = b;
    *(Vec4 *)(arg0 + 0x80) = e;
    *(Vec4 *)(arg0 + 0x90) = d;
    return 2;
}
