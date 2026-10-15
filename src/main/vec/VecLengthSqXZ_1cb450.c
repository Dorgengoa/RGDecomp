#include "types.h"
typedef unsigned __int128 u128;

/* s88m ol1a: pure-C replacement of the former asm function.  Retail's SDK
   macro returns the scalar through $a1 (qmfc2.ni $5 / mtc1 $5).  C route:
   optimization_level 1 keeps params as PHYSICAL registers once read, so the
   pointer pun of the bound vf4 written INTO param `b` is `qmfc2.ni a1`;
   opt_common_subs lets the float pun reuse it (mtc1 a1,f0) as long as `b`
   stays live into a later block (two zero-word splits, removed post-RA). */

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cb450 asm("vf4");

#pragma optimization_level 1
#pragma schedule on
#pragma opt_common_subs on

f32 VecLengthSqXZ_1cb450(u128 *a, u128 *b)
{
    f32 r;

    if (b) { a = (u128 *)(s32)(u32)a; }
    v4_1cb450 = *a;
    _vmul(v4_1cb450, 0xA, v4_1cb450, v4_1cb450);
    _vaddbc(v4_1cb450, 8, v4_1cb450, v4_1cb450, 2);
    b = *(u128 **)&v4_1cb450;
    r = *(f32 *)&v4_1cb450;
    if (a) { r = -(-r); }
    if (b) { r = -(-r); }
    return r;
}
