#include "types.h"
typedef unsigned __int128 u128;

/* s88m ol1a: pure-C replacement of the former asm function.  Retail's SDK
   macro returns the scalar through $a1 (qmfc2.ni $5 / mtc1 $5).  C route:
   optimization_level 1 keeps params as PHYSICAL registers once read, so the
   pointer pun of the bound vf4 written INTO param `b` is `qmfc2.ni a1`;
   opt_common_subs lets the float pun reuse it (mtc1 a1,f0) as long as `b`
   stays live into a later block (two zero-word splits, removed post-RA). */

#pragma vu0_mmi_reg_binding on
extern u128 v4_1cba40 asm("vf4");
extern u128 v5_1cba40 asm("vf5");
extern u128 v6_1cba40 asm("vf6");

#pragma optimization_level 1
#pragma schedule on
#pragma opt_common_subs on

f32 VecDotDiff_1cba40(u128 *a, u128 *b, u128 *c)
{
    f32 r;

    v4_1cba40 = *(volatile u128 *)a;
    v5_1cba40 = *(volatile u128 *)b;
    v6_1cba40 = *(volatile u128 *)c;
    if (c) { a = (u128 *)(s32)(u32)a; }
    _vsub(v4_1cba40, 0xF, v4_1cba40, v5_1cba40);
    _vmul(v4_1cba40, 0xE, v4_1cba40, v6_1cba40);
    _vaddbc(v4_1cba40, 8, v4_1cba40, v4_1cba40, 4);
    _vaddbc(v4_1cba40, 8, v4_1cba40, v4_1cba40, 2);
    b = *(u128 **)&v4_1cba40;
    r = *(f32 *)&v4_1cba40;
    if (a) { r = -(-r); }
    if (b) { r = -(-r); }
    return r;
}
