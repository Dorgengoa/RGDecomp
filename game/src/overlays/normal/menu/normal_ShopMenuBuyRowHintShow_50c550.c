/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyRowHintShow_50c550 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050C550 -- the equip-slot arrow/cursor layout for the 0x7532
 * panel.  normal_D_00527D30 is indexed by `o->f16 + o->f1A` (the same table
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
extern Ent  *normal_D_00527D30[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyRowHintShow_50c550(s32 a)
{
    Ent  *p;
    void *v;
    Hdl  *o;
    s16   r;

    if (a != 0) {
        o = ((Hdl *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7532));
        p = normal_D_00527D30[o->f16 + o->f1A];
        normal_ShopMenuBuyItemStatusLayout_50be30(p);
        v = p->f00;
        if (v == 0) {
            return 0;
        }
        if (((unsigned char)ShopRowIsLocked_3ce690(p)) != 0 || ((unsigned char)ItemRecKindIs19_3d4610(v)) != 0) {
            return 0;
        }
        UiSetSpriteX_28fcd0(D_004845CC, 0x50, 0x54, 9);
        r = o->f16;
        if (r < 4) {
            UiSetWidgetPos_290f60(D_004845CC, 0x50, 0x7E, r * 0x1C + 0x92);
            UiSetSpriteY_28fc90(D_004845CC, 0x50, -0xE, 9);
            UiSetSpriteU_28f930(D_004845CC, 0x50, 0xF0, 9);
            UiSetSpriteFlags_290bd0(D_004845CC, 0x50, (long long)(0x40), -1, 9, 0);
        } else {
            UiSetWidgetPos_290f60(D_004845CC, 0x50, 0x7E, r * 0x1C - 0xE);
            UiSetSpriteY_28fc90(D_004845CC, 0x50, 0x67, 9);
            UiSetSpriteU_28f930(D_004845CC, 0x50, 0xE0, 9);
            UiSetSpriteFlags_290bd0(D_004845CC, 0x50, (long long)(0x40), 1, 9, 0);
        }
        UiFadeWidgetAlpha_290690(D_004845CC, 0x50, 1.0f, D_0047D34C, -1.0f);
        return 1;
    }
    UiFadeWidgetAlpha_290690(D_004845CC, 0x50, 0.0f, D_0047D3C8, -1.0f);
    return 1;
}
