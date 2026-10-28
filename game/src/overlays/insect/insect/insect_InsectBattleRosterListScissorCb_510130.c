/* rgp:protos */
#define RGP_SELF_insect_InsectBattleRosterListScissorCb_510130 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510130 -- 440 bytes, 110 instructions, 11 calls, 6 conditional
 * branches, br/ins 0.055.  From x_band.py's branch-light band; no jalr, no
 * float, not a 0050d6a0 family member.
 *
 *  - `daddu $23, $8, $0` in the prologue is ARGUMENT FIVE
 *    (insect-decl -- EABI passes eight integer arguments in $4..$11), so the
 *    prototype has three parameters nothing in the body reads;
 *  - `insect_D_00525FF0` is HOISTED into $16 with a `lui`/`addiu` pair used once, and
 *    the null test on it survives -- insect-extern-handle-hoist's hoist
 *    polarity, so the handle is a named local;
 *  - the three guards are EARLY RETURNS, not nesting: each `bnel` skips a
 *    two-word `b <epilogue>` / `daddu $2,$0,$0` block of its own;
 *  - `lw $16, 0x9C($29)` ONCE, right after func_290FC0, and `$16` alive to
 *    the far arm: the out-parameter's value is COPIED to a named local.  Read
 *    inline it is an address-taken variable and mwcc re-loads it at the second
 *    use, which costs the eighth callee-saved register and three words;
 *  - `beql $23, $0, .L00510278` sends the arg-5-is-zero case to the SECOND
 *    block, so the fall-through -- the `if` body -- is the non-zero arm;
 *  - `slt $2, $18, $20` lands in a GPR and not $at, which is at-compare-class's
 *    `>=` token;
 *  - every field of the packed argument is `dsll32 0 / dsra32 0` first: the
 *    terms are `(s64)` casts of s32 expressions, not 64-bit arithmetic.
 */

typedef struct Node {
    u8  pad00[0x20];
    s32 f20;                        /* +0x20 */
} Node;

extern u8 insect_D_00525FF0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBattleRosterListScissorCb_510130(s32 c, s32 a1, s32 a2, s32 a3, s32 f)
{
    s32   ox;
    s32   oy;
    s32   x;
    s32   m;
    s32   gw;
    s32   gh;
    s32   w;
    s32   v;
    s32   h;
    u8   *hh;
    Node *p;

    m = GetDrawCtx_15de80();
    gw = DrawEnvGetWidth_1451e0(m);
    gh = DrawEnvGetHeight_1451d0(m);
    hh = insect_D_00525FF0;
    if (hh == 0) {
        return 0;
    }
    p = ((Node *)UiFindWidget_290460(hh, 0x7549));
    if (p == 0) {
        return 0;
    }
    if (p->f20 == 0) {
        return 0;
    }
    UiGetWidgetAbsPos_290fc0(hh, 0x7549, &ox, &oy);
    x = ox;
    w = x + 0x1C0;
    v = oy + 6;
    h = v + 0x8A;
    if (w >= gw) {
        w = gw;
    }
    if (h >= gh) {
        h = gh;
    }
    if (f != 0) {
        GsPktOpenPrim_13f730(c, 6);
        GsPktWriteAD_13ec80(c, 0x40, (s64)(x + 2) | ((s64)(w - 2) << 16)
                             | ((s64)(v + 2) << 32) | ((s64)(h - 2) << 48));
        GsPktClose_13f5b0(c);
    } else {
        GsPktOpenPrim_13f730(c, 6);
        GsPktWriteAD_13ec80(c, 0x40, ((s64)(gw - 1) << 16) | ((s64)(gh - 1) << 48));
        GsPktClose_13f5b0(c);
    }
    return 1;
}
