#include "types.h"
#include "vec.h"

extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern f32 VecLength_13d4a0(Vec4 *);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
extern void *memset(void *, s32, u32);

s32 CollBuildWallTrisMaybe_16d550(u8 *arg0, s32 arg1, Vec4 *arg2, Vec4 *arg3, f32 lim, f32 s)
{
    Vec4 d;
    Vec4 q;
    Vec4 a;
    Vec4 b;
    Vec4 c;
    Vec4 e;
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
