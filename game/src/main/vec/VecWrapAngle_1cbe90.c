/* rgp:protos */
#define RGP_SELF_VecWrapAngle_1cbe90 1
#define RGP_SELF_Wrap 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

/* s88m lqa2: pure-C replacement of the former whole-function asm.
   Retail stages the 16-byte copy through $a1 (SDK copy macro's fixed $5).
   C route: optimization_level 1 makes the param `in` the PHYSICAL a1 in the IR,
   so reassigning it (sgn[0] load) keeps the `src = in` copy (daddu t4,a1);
   `c` is read (uninitialised) by the first zero-word split, which makes it live
   from entry -> coloured v1 first -> the lq temp's first fit is a1.
   Named temps keep vreg ids in declaration order (= colour priority). */

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cbe90_t; /* rg:vu0bind vf4 */
#define v4_1cbe90 RG_VU0_BIND_VF(4, rgvb_v4_1cbe90_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cbe90_t; /* rg:vu0bind vf5 */
#define v5_1cbe90 RG_VU0_BIND_VF(5, rgvb_v5_1cbe90_t)

typedef u128 __attribute__((aligned(4))) rgvb_v8_1cbe90_t; /* rg:vu0bind vf8 */
#define v8_1cbe90 RG_VU0_BIND_VF(8, rgvb_v8_1cbe90_t)

typedef u128 __attribute__((aligned(4))) rgvb_v9_1cbe90_t; /* rg:vu0bind vf9 */
#define v9_1cbe90 RG_VU0_BIND_VF(9, rgvb_v9_1cbe90_t)


extern f32 D_0047E2A0;

#pragma optimization_level 1
#pragma schedule on

static inline void Wrap(rg_vu0_state *rg_vu0_p_, void *d, void *s, void *c, void *sg)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)

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

#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

void VecWrapAngle_1cbe90(u128 *out, u128 *in)
{ RG_VU0_FRAME;
    u32 sgn[4] __attribute__((aligned(16)));
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
    Wrap(&rg_vu0, out, src, c, p);
}
