#include "types.h"
/* normal 0x0050C550 -- the equip-slot arrow/cursor layout for the 0x7532
 * panel.  D_00527D30 is indexed by `o->f16 + o->f1A` (the same table
 * normal_FUN_0050B5C0 walks); the row's first word is the descriptor and three
 * guards on it all return 0.  `o->f16 < 4` picks the upper or lower half of
 * the 8-row grid: the two arms differ only in the row offset (+0x92 vs -0xE),
 * the two arrow x's and the sign of func_290BD0's fourth argument.
 * 1.0f / 0.0f / -1.0f are materialised lui+mtc1 (their low half is zero) while
 * the middle argument comes from MAIN's float pool at gp-0x7E24 / -0x7DA8, so
 * those two stay `extern f32` ([[mwcc-float-literal-pool]]).
 *
 * ****** SESSION 25, THE LEVER THAT CLOSED IT: the func_3CE690 and func_3D4610
 * guards are ONE `||`, not two consecutive `if`s.  A `||` whose body is a
 * `return K` compiles to a PAIR of shapes that two separate guards cannot
 * produce:
 *   operand 1 -> `bnel $2,$0,EPILOGUE` with `daddu $2,$0,$0` in the ANNULLED
 *                slot  (2 words -- the return value rides the likely branch)
 *   operand 2 -> `beql $2,$0,BODY` with the body's first instruction in the
 *                annulled slot, then a REAL three-word block
 *                `daddu $2,$0,$0 / b EPILOGUE / nop` -- the return value
 *                materialised BEFORE the branch, delay slot EMPTY.
 * Written as two `if`s, whichever guard is spelled `return 0` sinks the
 * constant into the `b`'s delay slot and the unit is ONE WORD SHORT; whichever
 * is spelled `goto zero` gets operand 1's 2-word form.  The 2^3 exit lattice
 * over the three guards reaches the right length at 9 bad and 1-short at a
 * single word, and NEITHER closes -- only the `||` does.
 * The oracle is MERGED normal_FUN_004F53D0, whose `if (x0 != x1 || y0 != y1)
 * return 0;` carries both shapes in one byte-identical function.
 * See normal_FUN_005115C0, which the same lever took from 1-short to right
 * length. */

typedef struct Hdl { u8 pad00[0x16]; s16 f16; u8 pad18[2]; s16 f1A; } Hdl;
typedef struct Ent { void *f00; } Ent;

extern void *D_004845CC;          /* gp - 0xBA4 */
extern void *D_004845D0;          /* gp - 0xBA0 */
extern f32   D_0047D34C;          /* gp - 0x7E24 */
extern f32   D_0047D3C8;          /* gp - 0x7DA8 */
extern Ent  *D_00527D30[];

extern Hdl  *func_28EA40(void *p, s32 id);
extern void  func_28F930(void *w, u16 id, s32 a, s32 b);
extern void  func_28FC90(void *w, u16 id, s32 a, s32 b);
extern void  func_28FCD0(void *w, u16 id, s32 a, s32 b);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290BD0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d);
extern void  func_290F60(void *w, u16 id, s32 x, s32 y);
extern s32   func_3CE690(Ent *p);
extern s32   func_3D4610(void *e);
extern void  normal_ShopMenuBuyItemStatusLayout_50be30(Ent *p);

s32 normal_ShopMenuBuyRowHintShow_50c550(s32 a)
{
    Ent  *p;
    void *v;
    Hdl  *o;
    s16   r;

    if (a != 0) {
        o = func_28EA40(D_004845D0, 0x7532);
        p = D_00527D30[o->f16 + o->f1A];
        normal_ShopMenuBuyItemStatusLayout_50be30(p);
        v = p->f00;
        if (v == 0) {
            return 0;
        }
        if (func_3CE690(p) != 0 || func_3D4610(v) != 0) {
            return 0;
        }
        func_28FCD0(D_004845CC, 0x50, 0x54, 9);
        r = o->f16;
        if (r < 4) {
            func_290F60(D_004845CC, 0x50, 0x7E, r * 0x1C + 0x92);
            func_28FC90(D_004845CC, 0x50, -0xE, 9);
            func_28F930(D_004845CC, 0x50, 0xF0, 9);
            func_290BD0(D_004845CC, 0x50, 0x40, -1, 9, 0);
        } else {
            func_290F60(D_004845CC, 0x50, 0x7E, r * 0x1C - 0xE);
            func_28FC90(D_004845CC, 0x50, 0x67, 9);
            func_28F930(D_004845CC, 0x50, 0xE0, 9);
            func_290BD0(D_004845CC, 0x50, 0x40, 1, 9, 0);
        }
        func_290690(D_004845CC, 0x50, 1.0f, D_0047D34C, -1.0f);
        return 1;
    }
    func_290690(D_004845CC, 0x50, 0.0f, D_0047D3C8, -1.0f);
    return 1;
}
