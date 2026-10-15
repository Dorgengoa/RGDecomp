#include "types.h"
/* normal 0x004F0B50 -- the TWIN of normal_FUN_004FB110 (same nine pool floats,
 * same 12.0f * func_128FD0 scalar, same four func_290F50 pushes), but with
 * LITERAL ids 0x5B-0x5E and a 0x386 guard, and it advances the object's own
 * 0x388 phase by pi/20 wrapping at 0.0f through -pi.
 *
 * Three arguments; -0x40 is entirely the save area (sq $16/$17/$18 at
 * 0x00/0x10/0x20 + sd $31 at 0x30), NO stack object.  The `swc1 0x388` in the
 * `bc1t` delay slot is the UNCONDITIONAL `+=` store scheduled into the slot.
 * The PRODUCT is its own statement: written inline mwcc contracts it into
 * adda.s/madd.s and retail has mul.s + add.s (the named-product lever).
 * `sll 1 / addu / sll 2 / addu / sll 1` is a strength-reduced `* 26`.
 * The (s32) result goes into its OWN local `k`, NOT back into the parameter
 * `b`.  Assigning it to `b` is 5 bad words -- every FP temp one register low
 * (mtc1 $2,$f1 / mul.s $f1 / mtc1 $17,$f0 / cvt.s.w $f0,$f0 / add.s $f0,$f1
 * where retail has $f2 / $f2 / $f1 / $f0,$f1 / $f2) because reusing `b`'s
 * home lets mwcc collapse the mtc1 and cvt temps onto one register.  Ten
 * other spellings are INERT against the base object 4e1d48bc (named call
 * result, named cast local either declaration order, unused local before or
 * after, named phase local, swapped mul operands, implicit cast, const 12.0f,
 * cast-first, `t += (f32)b`), and writing all ten pool floats as LITERALS is
 * a live-but-equal 5 (08a753d0, retarget fired on 10 sites).
 * 0x3F000000 0.5f, 0x3E800000 0.25f, 0x3E000000 0.125f, 0x41400000 12.0f.
 */

typedef struct Obj {
    u8  pad000[0x386];
    s16 f386;
    f32 f388;
    u8  pad38C[0x394 - 0x38C];
    s16 f394;
} Obj;

extern f32 D_0047D1FC;            /* 3.1415927  gp - 0x7F74 */
extern f32 D_0047D278;            /* 0.8        gp - 0x7EF8 */
extern f32 D_0047D5BC;            /* 0.025      gp - 0x7BB4 */
extern f32 D_0047D950;            /* 0.035      gp - 0x7820 */
extern f32 D_0047DA4C;            /* 0.015      gp - 0x7724 */
extern f32 D_0047DA50;            /* 0.005      gp - 0x7720 */
extern f32 D_0047DA54;            /* 0.15707964 gp - 0x771C */
extern f32 D_0047DA58;            /* 0.38       gp - 0x7718 */
extern f32 D_0047DA5C;            /* 0.32       gp - 0x7714 */
extern f32 D_0047DA60;            /* 0.28       gp - 0x7710 */

extern f32  func_128FD0(f32 x);
extern void func_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern void func_290F50(void *a, u16 id, s32 c, s32 d, s32 e, f32 x);

void normal_FieldHudBtlEscArrowBob_4f0b50(Obj *p, s32 b, s32 c)
{
    f32 t;
    s32 k;

    if (p->f386 != 0) {
        func_290690(p, 0x5B, D_0047D278, D_0047D950, -1.0f);
        func_290690(p, 0x5C, 0.5f, D_0047D5BC, -1.0f);
        func_290690(p, 0x5D, 0.25f, D_0047DA4C, -1.0f);
        func_290690(p, 0x5E, 0.125f, D_0047DA50, -1.0f);
        p->f388 = p->f388 + D_0047DA54;
        if (p->f388 > 0.0f) {
            p->f388 = p->f388 - D_0047D1FC;
        }
        t = 12.0f * func_128FD0(p->f388);
        k = (s32)(t + (f32)b);
        c = c + p->f394 * 26;
        func_290F50(p, 0x5B, k, c, 0, 0.5f);
        func_290F50(p, 0x5C, k, c, 0, D_0047DA58);
        func_290F50(p, 0x5D, k, c, 0, D_0047DA5C);
        func_290F50(p, 0x5E, k, c, 0, D_0047DA60);
    }
}
