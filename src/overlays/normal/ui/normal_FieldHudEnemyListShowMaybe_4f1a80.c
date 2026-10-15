#include "types.h"
/* normal 0x004F1A80 -- CLOSED 2026-09-01 (s22).  Three blocks draw the same row
 * (the item, its shadow id-5 and its glow id-10) and each passes the SAME
 * y expression `i * 30 + 0xB4`.  Retail RECOMPUTES it in all three; mwcc CSEs
 * it unless each block SPELLS IT DIFFERENTLY, and there must be THREE distinct
 * spellings for three blocks:
 *
 *   block1  i * 30 + 0xB4
 *   block2  (s32)((u32)i * 30) + 0xB4
 *   block3  (s32)((u32)(i * 15) * 2 + 0xB4)      <- the s22 addition
 *
 * With block3 spelled `(s32)((u32)i * 30 + 0xB4)` it still folded with block2
 * and the unit was ONE WORD SHORT -- and the shortfall did NOT look like a CSE:
 * it read as ours saving one MORE callee-saved register (an extra sq/lq pair)
 * than retail, with retail spending 6 words recomputing where we spent 3 moves.
 * ⚠ A CSE this compiler makes and retail does not can present as a REGISTER
 * COUNT difference at a length that is only one word off.  Ten spellings were
 * swept for block3; two reach the right length and only this one is close.
 *
 * THE LAST 40 WORDS WERE A DECLARATION-ORDER ROTATION, and here decl order IS
 * the axis (contrast [[mwcc-loop-counter-priority]], where it is a null): the
 * residue was a 3-cycle over $17/$18/$19 with ours i=$17,id=$19 and retail
 * i=$19,id=$17.  All 24 permutations of the 4 locals were built -- 6 distinct
 * objects at 22/28/32/40/41 bad -- and every one of the FOUR with `i` FIRST is
 * the MATCH.  `id`, `a`, `b` are passed VERBATIM as call arguments and `i` is
 * not, which is [[mwcc-decl-order-tiebreak]]'s precondition.
 */
#include "types.h"
/* WARNING PARKED at TEN WORDS SHORT (166 of 176) -- deliberately NOT in
 * config/ocunits/normal.txt.  Every call, constant, guard and block is exact.
 * The residue is one CSE: retail RECOMPUTES the y expression `i*30 + 0xB4`
 * (sll/subu/sll/addiu, four words) at each of the three blocks, parking it in
 * whichever register the next id has not taken; ours computes it ONCE and
 * keeps it, so we are eight words short there and two more in the rotation
 * that follows.  Both compilations use SEVEN callee-saved registers, so it is
 * not pressure -- it is the same cost-model split normal_ShopMenuSellTabsLayout_50e980 is
 * parked on, and these two units are the class.
 * MEASURED NEGATIVE: THE WHOLE COMPILER-KNOB AXIS -- n_knob.py --all, 488
 * variants over the 244 recognised pragmas in both polarities
 * (build/n_knob_1a80_all.log), 468 INERT and 20 live, and NOT ONE reaches the
 * 0x2b8 length. */
/* normal 0x004F1A80 -- lays out the map's location list.  For each of the
 * p->f47A live entries it raises three stacked widgets -- the label (id), its
 * shadow (id - 5) and its glow (id - 10) -- at x = i*100 + 0x1F4, y = i*30 +
 * 0xB4, each with its own alpha, gp tint and 28/26/24 point size, and clears
 * the entry's f47C slot.  Everything is shown or hidden together on p->f382.
 *
 * `id` is a u16 LOCAL: `daddiu $18,$0,0x4A` initialises it, passing it costs a
 * bare `daddu` with no mask, and both `id - 5` and `id - 10` pay the promotion
 * `andi $22,$18,0xFFFF` ONCE before their own `andi` -- the multi-use half of
 * the u16 widget-id rule recorded on normal_FUN_004F57F0.
 * The x expression is computed ONCE and parked in a callee-saved register; the
 * y expression is RECOMPUTED at each of the three blocks because the register
 * that held it is taken by the next id.  Both are written inline.
 * func_290F50 takes SIX arguments with the float LAST, in $f12 (EABI keeps the
 * float and integer sequences independent) -- the same prototype
 * normal_FUN_0050FB60 records.
 * `lbu $2,0x382($20)` is re-read before each of the three guards, and the
 * third one rides the loop's own `bnel` LIKELY SLOT. */

typedef struct Obj {
    u8   pad000[0x382];
    u8   f382;
    u8   pad383[0x47A - 0x383];
    s16  f47A;
    s16  f47C[1];
    u8   pad47E[0x4A8 - 0x47E];
    s16  f4A8;
} Obj;

extern f32 D_0047D278;            /* gp - 0x7EF8 */
extern f32 D_0047DCFC;            /* gp - 0x7474 */
extern f32 D_0047DD00;            /* gp - 0x7470 */
extern f32 D_0047DD04;            /* gp - 0x746C */

extern void func_290690(Obj *p, u16 id, f32 x, f32 y, f32 z);
extern void func_2907A0(Obj *p, u16 id, f32 x);
extern void func_290F50(Obj *p, u16 id, s32 a, s32 b, s32 c, f32 x);
extern void func_290F60(Obj *p, u16 id, s32 x, s32 y);
extern void func_291110(Obj *p, u16 id, s32 c, s32 d);

void normal_FieldHudEnemyListShowMaybe_4f1a80(Obj *p, u8 mode)
{
    s32 i;
    u16 id;
    u16 a;
    u16 b;

    p->f4A8 = 1;
    p->f382 = mode;
    id = 0x4A;
    for (i = 0; i < p->f47A; i++) {
        if (p->f382 == 0) {
            func_291110(p, id, 0, 1);
        } else {
            func_291110(p, id, 1, 1);
        }
        func_2907A0(p, id, 0.0f);
        func_290F60(p, id, i * 100 + 0x1F4, i * 30 + 0xB4);
        func_290690(p, id, D_0047D278, D_0047DCFC, -1.0f);
        func_290F50(p, id, 0xA0, i * 30 + 0xB4, 1, 28.0f);
        a = id - 5;
        if (p->f382 == 0) {
            func_291110(p, a, 0, 1);
        } else {
            func_291110(p, a, 1, 1);
        }
        func_2907A0(p, a, 0.0f);
        func_290F60(p, a, i * 100 + 0x1F4, (s32)((u32)i * 30) + 0xB4);
        func_290690(p, a, 0.5f, D_0047DD00, -1.0f);
        func_290F50(p, a, 0xA0, (s32)((u32)i * 30) + 0xB4, 1, 26.0f);
        b = id - 10;
        if (p->f382 == 0) {
            func_291110(p, b, 0, 1);
        } else {
            func_291110(p, b, 1, 1);
        }
        func_2907A0(p, b, 0.0f);
        func_290F60(p, b, i * 100 + 0x1F4, (s32)((u32)(i * 15) * 2 + 0xB4));
        func_290690(p, b, 0.25f, D_0047DD04, -1.0f);
        func_290F50(p, b, 0xA0, (s32)((u32)(i * 15) * 2 + 0xB4), 1, 24.0f);
        p->f47C[i] = 0;
        id++;
    }
}
