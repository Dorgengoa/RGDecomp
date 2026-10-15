#include "types.h"

/* Variant -> 64-bit ("double in a GPR") converter.  The tag is at +0x00 and the
   payload at +0x08; the ACCESS WIDTH of each arm's load is the union member:
   lb / lbu / lh / lhu / lw / lw / ld / ld / lwc1 / ld.

   jtbl_00463600 is 11 entries and the identity permutation, but index 0 points
   at the block at 0x0036F78C, which is also the `default:` body ($2 = 0) -- so
   `case 0` shares the default label, and the out-of-range `beql` inlines that
   body into its delay slot (`daddu $2,$0,$0`).  Writing `case 0:` explicitly
   is what pins the table's base at 0 (retail has a bare `sltiu $1,$2,0xB` with
   no `addiu $2,$2,-N` ahead of it).

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  VariantGetDouble_36f6c0  00463600  2C   # jtbl_00463600, 11 cases */

extern s64 litodp(s32);
extern s64 UIntToDouble_100320(u32);
extern s64 S64ToDouble_13a998(s64);
extern s64 U64ToDouble_100370(u64);
extern s64 fptodp(f32);

union Val {
    s8 vs8;
    u8 vu8;
    s16 vs16;
    u16 vu16;
    s32 vs32;
    u32 vu32;
    s64 vs64;
    u64 vu64;
    f32 vf32;
};

struct Var {
    s32 tag;
    u8 pad004[0x4];
    union Val u;
};

s64 VariantGetDouble_36f6c0(struct Var *p0)
{
    switch (p0->tag) {
    case 1:
        return litodp(p0->u.vs8);
    case 2:
        return UIntToDouble_100320(p0->u.vu8);
    case 3:
        return litodp(p0->u.vs16);
    case 4:
        return UIntToDouble_100320(p0->u.vu16);
    case 5:
        return litodp(p0->u.vs32);
    case 6:
        return UIntToDouble_100320(p0->u.vu32);
    case 7:
        return S64ToDouble_13a998(p0->u.vs64);
    case 8:
        return U64ToDouble_100370(p0->u.vu64);
    case 9:
        return fptodp(p0->u.vf32);
    case 10:
        return p0->u.vs64;
    case 0:
    default:
        return 0;
    }
}
