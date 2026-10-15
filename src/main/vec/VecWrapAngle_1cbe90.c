#include "types.h"
typedef unsigned __int128 u128;

/* s88m lqa2: pure-C replacement of the former whole-function asm.
   Retail stages the 16-byte copy through $a1 (SDK copy macro's fixed $5).
   C route: optimization_level 1 makes the param `in` the PHYSICAL a1 in the IR,
   so reassigning it (sgn[0] load) keeps the `src = in` copy (daddu t4,a1);
   `c` is read (uninitialised) by the first zero-word split, which makes it live
   from entry -> coloured v1 first -> the lq temp's first fit is a1.
   Named temps keep vreg ids in declaration order (= colour priority). */

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cbe90 asm("vf4");
extern u128 v5_1cbe90 asm("vf5");
extern u128 v8_1cbe90 asm("vf8");
extern u128 v9_1cbe90 asm("vf9");

extern f32 D_0047E2A0;

#pragma optimization_level 1
#pragma schedule on

static inline void Wrap(void *d, void *s, void *c, void *sg)
{
    v4_1cbe90 = *(volatile u128 *)s;
    v8_1cbe90 = *(volatile u128 *)c;
    v9_1cbe90 = *(volatile u128 *)sg;
    if (d) { d = (void *)(s32)(u32)d; }
    _vabs(v5_1cbe90, 0xF, v4_1cbe90);
    _vmulbc(v5_1cbe90, 0xF, v5_1cbe90, v8_1cbe90, 8);
    _vaddbc(v5_1cbe90, 0xF, v5_1cbe90, v8_1cbe90, 4);
    _vaddbc(v5_1cbe90, 0xF, v5_1cbe90, v8_1cbe90, 2);
    _vsubbc(v5_1cbe90, 0xF, v5_1cbe90, v8_1cbe90, 2);
    _vmulbc(v5_1cbe90, 0xF, v5_1cbe90, v8_1cbe90, 1);
    _vmul(v5_1cbe90, 0xF, v5_1cbe90, v9_1cbe90);
    _vsub(v4_1cbe90, 0xF, v4_1cbe90, v5_1cbe90);
    *(u128 *)d = v4_1cbe90;
}

void VecWrapAngle_1cbe90(u128 *out, u128 *in)
{
    u32 sgn[4];
    u128 *src = in;
    u128 *p = (u128 *)sgn;
    u32 m;
    u32 o;
    u32 r0;
    u32 x3;
    u32 x1;
    u32 x2;
    u128 t;
    f32 *c;

    if (c) { src = (u128 *)(s32)(u32)src; }
    t = *src;
    *p = t;
    if (c) { p = (u128 *)(s32)(u32)p; }
    m = 0x80000000;
    if (m) { m = (u32)(s32)m; }
    o = 0x3F800000;
    c = &D_0047E2A0;
    in = (u128 *)sgn[0];
    x1 = sgn[1];
    x2 = sgn[2];
    r0 = (u32)in & m;
    if (r0) { r0 = (u32)(s32)r0; }
    x3 = sgn[3];
    x1 &= m;
    x2 &= m;
    r0 |= o;
    x1 |= o;
    x2 |= o;
    x3 &= m;
    sgn[0] = r0;
    x3 |= o;
    sgn[1] = x1;
    sgn[2] = x2;
    sgn[3] = x3;
    if (p) { p = (u128 *)(s32)(u32)p; }
    if (c) { c = (f32 *)(s32)(u32)c; }
    Wrap(out, src, c, p);
}
