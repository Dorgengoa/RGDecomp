/* rgp:protos */
#define RGP_SELF_insect_InsectBattleConfirmDialogOpen_50eaf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050EAF0 -- 876 bytes, 219 instructions, 28 calls, 8 conditional
 * branches.  The 0xC379 dialogue-box layout routine: it sizes the box from the
 * measured text extent, clamps the two gp size globals, then places six widgets
 * relative to them.  MATCHED in ix34s10 (object e8c907bd, len 0x36c).
 *
 * TWO LEVERS closed it, and neither pays without the other:
 *
 *  1. STORE ORDER.  D_00480E90 is stored BEFORE D_00480E94 in the source and
 *     mwcc's scheduler INVERTS the pair, so retail's `sh $v0,-17116($gp)`
 *     (E94) issues first and the E90 store is the one free to sink into the
 *     clamp-1 `beq` delay slot at 0050EBBC.  Written the other way round --
 *     which is how every draft since ix23 wrote it -- the scheduler sinks the
 *     E94 store instead and x9C has to be re-loaded from 156($sp) at the join.
 *
 *  2. Both clamps are a plain store-then-`if`, NOT a ternary.  The ternary
 *     stores unconditionally at the join, mwcc dead-store-eliminates the first
 *     store, the delay slot goes `nop` and the merge value becomes a phi in
 *     $v1 (that was the 7-word ix24/ix25 park).  With the `if` there is no phi,
 *     the clamp constant lands in $v0 as retail has it, and the join value has
 *     to come out of memory.
 *
 * The join read stays the SECOND SPELLING `*(s16 *)((s8 *)&D_00480E94 - 4)`:
 * that is what stops mwcc forwarding the just-stored value and buys retail's
 * `lh $v0,-17120($gp)` at 0050EBE0 plus its duplicate in the clamp-2 `beql`
 * annulled slot at 0050EBD4.  The plain `D_00480E90` read there is +1 word.
 * (An equivalent MATCH, object 20e5470a, spells the pair as ONE small-data
 * object -- `extern s16 D_00480E90[3];` with [0] and [2] -- and then needs no
 * second spelling at all, because a store to one element kills the other.)
 *
 * E94 volatile is REQUIRED; E90 must stay non-volatile.
 *
 * Everything else was already confirmed byte-exact: the seven signed `/ 2`
 * divides (`bgez / addiu 1 / sra 1` -- a `>> 1` would fold to a bare `sra`),
 * the gp handle hoist, the (u8)!(x != 0) bool, and the two UNSIZED externs
 * D_004DB150 / insect_D_00526004 (an incomplete array type is never small data, so
 * both take %hi/%lo, which is what retail has).
 */

typedef struct Box {
    s16 f0;                     /* +0x00 */
    s16 f2;                     /* +0x02 */
    s32 f4;                     /* +0x04 */
    u8  pad08[2];
    s8  fA;                     /* +0x0A */
} Box;

extern s16 D_00480E90;
extern volatile s16 D_00480E94;
extern u8  D_004DB150[];
extern u8  insect_D_00526004[];

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
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleConfirmDialogOpen_50eaf0(s32 a, s32 b, void *c, s32 d)
{
    s32 x9C;
    s32 x98;
    s32 x94;
    s32 x90;
    Box *q;
    void *o;
    void *h;
    s32 n;
    void *g;
    void *m;
    s32 w;

    o = InsectBattleGet_31a8d0();
    h = insect_D_00526004;
    g = (u8 *)o + 0x5054;
    m = (u8 *)o + 0x4F90;
    n = ((s32)insect_InsectMsgGet_512b70(c, d));
    q = ((Box *)UiGetWidgetText_28f620(h, 0xC379, 0));
    q->f4 = n;
    x9C = 0;
    x98 = 0;
    TextStyleInitWithFontType_2931c0(D_004DB150, (long long)(q->fA));
    FontMeasureString_26daf0(D_004DB150, n, &x9C, &x98);
    D_00480E90 = x9C + 0x28;
    D_00480E94 = x98 + 0x3A;
    if (D_00480E90 < 0x118) {
        D_00480E90 = 0x118;
    }
    if (D_00480E94 < 0x50) {
        D_00480E94 = 0x50;
    }
    w = *(s16 *)((s8 *)&D_00480E94 - 4) - x9C;
    q->f0 = w / 2;
    q->f2 = 0xC;
    UiWindowFrameLayoutMaybe_392bb0(g, UiFindWidget_290460(h, 0xC379), D_00480E90, D_00480E94, 1);
    UiSpriteListFillColumnMaybe_3939e0(g, UiFindWidget_290460(h, 0xC37A), 1, 1,
                (f32)(D_00480E90 - 0x20), 0.0f);
    insect_InsectCursorSetPushPage_511cf0(m, 7, 1);
    if (insect_InsectBattleTestFlag_50da40(o, 0x11) != 0) {
        insect_InsectBattleClearFlag_50da90(o, 0x11);
        insect_InsectCursorSetSetCell_511c50(m, 1, 0);
    }
    insect_InsectCursorSetGetCurCell_511a90(m, &x94, &x90);
    InsectUiConfirmButtonSetSelectedMaybe_392b20(g, UiFindWidget_290460(h, 0xC37B), (u8)!(x94 != 0));
    InsectUiConfirmButtonSetSelectedMaybe_392b20(g, UiFindWidget_290460(h, 0xC37C), x94);
    UiSetWidgetPos_290f60(h, 0xC379, (a - D_00480E90) / 2,
                (b - D_00480E94) / 2 + 0x40);
    UiSetWidgetPos_290f60(h, 0xC37A, 0x10, x98 + 0xA);
    UiSetWidgetPos_290f60(h, 0xC37B, D_00480E90 / 2 - 0x4A, x98 + 0x14);
    UiSetWidgetPos_290f60(h, 0xC37C, D_00480E90 / 2 + 0x16, x98 + 0x14);
    UiSetWidgetAlpha_2907a0(h, 0xC378, 0.0f);
    UiFadeWidgetAlpha_290690(h, 0xC378, 1.0f, 0.125f, -1.0f);
    UiSetWidgetAlpha_2907a0(h, 0xC37E, 0.0f);
    UiFadeWidgetAlpha_290690(h, 0xC37E, 1.0f, 0.125f, -1.0f);
    UiSetWidgetVisible_290010(h, 0xC378, 1, -1);
    UiSetWidgetVisible_290010(h, 0xC37E, 1, -1);
}
