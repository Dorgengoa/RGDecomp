/* rgp:protos */
#define RGP_SELF_VecDistSq_1cb3c0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
typedef rg_u128 u128;

/* s88m ol1a: pure-C replacement of the former asm function.  Retail's SDK
   macro returns the scalar through $a1 (qmfc2.ni $5 / mtc1 $5).  C route:
   optimization_level 1 keeps params as PHYSICAL registers once read, so the
   pointer pun of the bound vf4 written INTO param `b` is `qmfc2.ni a1`;
   opt_common_subs lets the float pun reuse it (mtc1 a1,f0) as long as `b`
   stays live into a later block (two zero-word splits, removed post-RA). */

#pragma vu0_mmi_reg_binding on
typedef u128 __attribute__((aligned(4))) rgvb_v4_1cb3c0_t; /* rg:vu0bind vf4 */
#define v4_1cb3c0 RG_VU0_BIND_VF(4, rgvb_v4_1cb3c0_t)

typedef u128 __attribute__((aligned(4))) rgvb_v5_1cb3c0_t; /* rg:vu0bind vf5 */
#define v5_1cb3c0 RG_VU0_BIND_VF(5, rgvb_v5_1cb3c0_t)


#pragma optimization_level 1
#pragma schedule on
#pragma opt_common_subs on

f32 VecDistSq_1cb3c0(u128 *a, u128 *b)
{ RG_VU0_FRAME;
    f32 r;

    v4_1cb3c0 = *a;
    v5_1cb3c0 = *b;
    _vsub(v4_1cb3c0, 0xE, v4_1cb3c0, v5_1cb3c0);
    _vmul(v4_1cb3c0, 0xE, v4_1cb3c0, v4_1cb3c0);
    _vaddbc(v4_1cb3c0, 8, v4_1cb3c0, v4_1cb3c0, 4);
    _vaddbc(v4_1cb3c0, 8, v4_1cb3c0, v4_1cb3c0, 2);
    b = *(u128 **)&v4_1cb3c0;
    r = *(f32 *)&v4_1cb3c0;
    if (a) { r = -(-r); }
    if (b) { r = -(-r); }
    return r;
}
