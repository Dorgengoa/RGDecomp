/* rgp:protos */
#define RGP_SELF_MatFromRotPos_1caf90 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

/* s88m ol1a: pure-C replacement of the former asm-helper-header version.
   Retail's Vu0SquareLength macro stages the qmfc2 result through $a1 (= rot's
   register) and copies rot to $a0 at entry.  C route (VecWrapAngle_1cbe90 lever):
   optimization_level 1 keeps params as PHYSICAL registers, so writing the
   qmfc2 value INTO `rot` (pointer pun of the bound vf4 = free) puts it in a1
   and keeps the entry `r = rot` copy (daddu a0,a1).  opt_common_subs lets the
   float pun of vf4 reuse that same qmfc2 (mtc1 a1,f1); `rot` stays live until
   the zero-word split at the top of the else path.  The other splits order
   the entry copies before the first lqc2 and the 0.0f mtc1 after the qmfc2. */

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_vz1caf90_t; /* rg:vu0bind vf0 */
#define vz1caf90 RG_VU0_BIND_VF(0, rgvb_vz1caf90_t)

typedef u128 __attribute__((aligned(4))) rgvb_v4_1caf90_t; /* rg:vu0bind vf4 */
#define v4_1caf90 RG_VU0_BIND_VF(4, rgvb_v4_1caf90_t)


/*rgp*/

#pragma optimization_level 1
#pragma schedule on
#pragma opt_common_subs on

void MatFromRotPos_1caf90(f32 m[4][4], f32 *rot, f32 *pos)
{ RG_VU0_FRAME;
    f32 *r = rot;
    f32 sl;
    f32 z;

    if (r) { r = (f32 *)(s32)(u32)r; }
    v4_1caf90 = *(u128 *)pos;
    _vmul(v4_1caf90, 0x1, vz1caf90, vz1caf90);
    *(u128 *)m[3] = v4_1caf90;
    v4_1caf90 = *(u128 *)r;
    _vmul(v4_1caf90, 0xE, v4_1caf90, v4_1caf90);
    _vaddbc(v4_1caf90, 8, v4_1caf90, v4_1caf90, 4);
    _vaddbc(v4_1caf90, 8, v4_1caf90, v4_1caf90, 2);
    rot = *(f32 **)&v4_1caf90;
    sl = *(f32 *)&v4_1caf90;
    if (r) { r = (f32 *)(s32)(u32)r; }
    z = 0.0f;
    if (z == sl) {
        m[0][0] = 1.0f;
        m[0][1] = z;
        m[0][2] = z;
        m[0][3] = z;
        m[1][0] = z;
        m[1][1] = 1.0f;
        m[1][2] = z;
        m[1][3] = z;
        m[2][0] = z;
        m[2][1] = z;
        m[2][2] = 1.0f;
        m[2][3] = z;
        return;
    }
    {
    f32 b[4] __attribute__((aligned(16)));
    f32 a[4] __attribute__((aligned(16))) = {0};
    f32 *c;

    if (rot) { r = (f32 *)(s32)(u32)r; }
    a[0] = r[1];
    VecSinCos_1cbfb0(b, r);
    VecSinCos_1cbfb0(a, a);
    c = &b[2];
    m[0][0] = a[1] * c[1];
    m[0][1] = a[1] * c[0];
    m[0][2] = -a[0];
    m[1][0] = -b[1] * c[0] + b[0] * a[0] * c[1];
    m[1][1] = b[1] * c[1] + b[0] * a[0] * c[0];
    m[1][2] = b[0] * a[1];
    m[2][0] = b[0] * c[0] + b[1] * a[0] * c[1];
    m[2][1] = -b[0] * c[1] + b[1] * a[0] * c[0];
    m[2][2] = b[1] * a[1];
    m[2][3] = 0.0f;
    m[1][3] = 0.0f;
    m[0][3] = 0.0f;
    }
}
