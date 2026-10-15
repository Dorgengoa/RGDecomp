#include "types.h"
/* normal 0x0050E740 -- the map/party screen's phase-in.  `b != 0` arms the
 * 0x19/0x1A frames, measures the party size through func_3E7E10, clamps the
 * two icon counts, then lays the four 0x4F slots out; `b == 0` falls straight
 * through to the 0x7535 hand-off.  Both paths return 1; the D_00527D30 guard
 * is the only `return 0`.
 *
 * `$4` is never read -- the f(void *, s32) state-handler family.
 * `swc1 $f0, -0xB3C($28)` sits in func_290F60's DELAY SLOT and captures
 * normal_ShopMenuScrollBarLayout_50b2a0's f32 result, not func_290F60's.
 * `slti $1,$16,0x9` and `slti $1,$16,0x3` both write $at and in both the
 * BRANCH TARGET is the `>=` arm -- so the `<` arm is the one written first.
 * `addiu $6,$0,1 / daddu $7,$6,$0` is the shared-constant spelling.
 * `mov.s $f15,$f12` + `mov.s $f14,$f13` is one 1.0f reaching arguments 3 and 6
 * and one gp float reaching arguments 4 and 5.
 *
 * TWO MEASURED LEVERS HERE, both worth carrying:
 * 1. `extern s32 D_00527D30` goes to SMALL DATA and gives one `lw ..($28)`;
 *    retail's `lui %hi / lw %lo` needs a declared size ABOVE the threshold.
 *    Measured: `s32` and `s32[2]` (8 B) stay gp-relative; `s32[]` (incomplete)
 *    and a 16-byte struct do not.  The threshold sits between 8 and 16.
 * 2. func_290F60's arguments 3 and 4 are `s32`, NOT `s16`.  The `lh` comes
 *    from the MEMBER's type.  Declaring the PARAMETERS s16 costs no
 *    instructions but MATERIALISES ARGUMENT 1 FIRST instead of last -- a pure
 *    3-word rotation, `lw $4,gp` ahead of the two `lh`s.  Six other spellings
 *    (named locals before and after the if, a pointer alias, a local for
 *    argument 1) were inert at 3 bad; the parameter type was the whole lever.
 * `n - 1` is written INLINE at all three uses: a named local for it costs 4
 * words, because mwcc then keeps it live across both arms. */

typedef struct Icon { s16 f00; s16 f02; u8 pad04[6]; s16 f0A; u8 pad0C[2];
                      s16 f0E; } Icon;

extern s32 D_00527D30[];

extern void *D_004845C4;          /* gp - 0xBAC */
extern void *D_004845C8;          /* gp - 0xBA8 */
extern void *D_004845CC;          /* gp - 0xBA4 */
extern void *D_004845D0;          /* gp - 0xBA0 */
extern f32   D_00484634;          /* gp - 0xB3C */
extern s16   D_00484638;          /* gp - 0xB38 */
extern s32   D_00484644;          /* gp - 0xB2C */
extern f32   D_0047D4C8;          /* gp - 0x7CA8 */
extern f32   D_0047D488;          /* gp - 0x7CE8 */

extern void  func_291110(void *a, u16 b, s32 c, s32 d);
extern void  func_28F930(void *a, u16 b, s32 c, s32 d);
extern void  func_290F60(void *a, u16 b, s32 c, s32 d);
extern void  func_290F50(void *a, u16 b, s32 c, s32 d, s32 e, f32 f);
extern void  func_290690(void *a, u16 b, f32 c, f32 d, f32 e);
extern void  normal_ShopMenuBuyListBuild_50ba50(void);
extern void  normal_ShopMenuBuyRowsRefresh_50b5c0(s32 a);
extern void  func_28EA90(void *a, s32 b, s32 c);
extern s32   func_1FEDE0(void);
extern s32   func_3E7E10(s32 a);
extern f32   normal_ShopMenuScrollBarLayout_50b2a0(s32 a, s32 b, s32 c, s32 d);
extern Icon *func_28EC60(void *a);
extern void  func_2907A0(void *a, u16 b, f32 c);
extern void  normal_ShopMenuRowInfoShow_509460(s32 a, s32 b, s32 c, s32 d, s32 e, f32 f);
extern void  func_28EF30(void *a, u16 b, s32 c, s32 d, s32 e);
extern void  func_290BD0(void *a, u16 b, s32 c, s32 d, s32 e, s32 f);
extern void  func_2905B0(void *a, u16 b, f32 c, f32 d, f32 e, f32 g);
extern void  normal_ShopMenuDiscountIconRefresh_50b140(void);
extern void  func_28EDE0(void *a, s32 b, s32 c);

s32 normal_ShopMenuBuyListOpenState_50e740(void *a, s32 b)
{
    s32   n;
    Icon *p;
    s32   i;

    if (b != 0) {
        func_291110(D_004845C8, 0x19, 1, 1);
        func_28F930(D_004845C8, 0x19, 0x9E, 0);
        func_291110(D_004845C8, 0x1A, 1, 1);
        func_290F60(D_004845C8, 0x1A, 0x200, 0x4A);
        func_290F50(D_004845C8, 0x1A, 0x46, 0x4A, 0, D_0047D4C8);
        func_290690(D_004845C8, 0x1A, 1.0f, 0.0625f, 0.0f);
        normal_ShopMenuBuyListBuild_50ba50();
        normal_ShopMenuBuyRowsRefresh_50b5c0(0);
        func_28EA90(D_004845D0, 0x7532, 1);
        n = func_3E7E10(func_1FEDE0());
        D_00484634 = normal_ShopMenuScrollBarLayout_50b2a0(0xE6, 8, n, 0);
        func_290F60(D_004845C8, 0x25, 0, 0);
        p = func_28EC60(D_004845D0);
        if (n < 9) {
            p->f0A = n - 1;
            p->f0E = n - 1;
        } else {
            p->f0A = 7;
            p->f0E = n - 1;
        }
        func_290F60(D_004845C8, 0x2F, p->f00, p->f02);
        func_291110(D_004845CC, 0x50, 1, 1);
        func_2907A0(D_004845CC, 0x50, 0.0f);
        if (D_00527D30[0] == 0) {
            return 0;
        }
        normal_ShopMenuRowInfoShow_509460(D_00527D30[0], 0x34, 0x33, 0x56, 0x15E, D_0047D488);
        i = 0;
        do {
            func_28EF30(D_004845CC, 0x4F, 0x20, 1, i);
            if (i < 3) {
                func_290BD0(D_004845CC, 0x4F, 8, 1, i, 0);
            }
            i = i + 1;
        } while (i < 4);
        func_2905B0(D_004845CC, 0x4F, 1.0f, D_0047D4C8, D_0047D4C8, 1.0f);
        normal_ShopMenuDiscountIconRefresh_50b140();
        D_00484644 = 0;
        D_00484638 = 0;
    }
    func_28EDE0(D_004845C4, 0x7535, 0);
    return 1;
}
