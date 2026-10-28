/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndLevelUpLabelUpdate_4ea3f0 1
#include "port/game_protos.h"
#line 1
/* ***** SESSION 45 (n45c9): BYTE-IDENTICAL, 192/192 words, MERGED.
 * 63 bad -> 0 on FIVE edits.  Found by build/wf-normal/s45/mdiff.py, which
 * named the first one in two lines where od.py showed 45 substitutions.
 *
 * 1. WIDGET IS A MEMBER ADDRESS, NOT POINTER ARITHMETIC.
 *      #define WIDGET(o)  ((void *)&(o)->f14)     -- with `u8 f14;` in Obj
 *    not `((void *)((u8 *)(o) + 0x14))`.  mwcc CSE'd the arithmetic form into
 *    a CALLEE-SAVED web and we spent `move a0,s4` at EIGHT call sites; retail
 *    keeps `arg0` in $16 and REMATERIALISES `addiu $4,$16,0x14` at each,
 *    because $4 is call-clobbered.  Worth -5 words.
 *    WARN the `(s8 *)` cast, the `&((u8 *)(o))[0x14]` index form and
 *    `0x10 + 4` are all the ARITHMETIC object -- only a real struct member
 *    changes it.  `s32 f14` and `u8 f14` are the same object.
 *
 * 2. `extra = 0;` MOVES ABOVE THE SWITCH.  Retail spends it in the delay slot
 *    of the PLAIN `beq $4,$3` that dispatches case 3 (`daddu $20,$0,$0`), and
 *    a plain branch's delay slot always executes -- so the statement has to
 *    dominate the switch.
 *
 * 3. `id = i + 0x3F;` MOVES INSIDE case 1 AND case 2, as each arm's FIRST
 *    statement.  m2c had written it TWICE just before a `case` label, which is
 *    unreachable C.  Retail's two `beql` delay slots BOTH hold
 *    `addiu $17,$19,0x3F` -- that is branch-likely THREADING of each target's
 *    first instruction ([[levers.d/mwcc-branch-likely-duplication]]), so it
 *    must BE the first instruction of both arms.  ABOVE the switch it is one
 *    word short; in case 1 only or case 2 only it is one word short.
 *
 * 4. `s32 extra;` IS DECLARED BEFORE `s32 i;`.  60 bad -> 4, and it empties a
 *    clean FOUR-CYCLE of the callee-saved file (retail arg0=$16 id=$17
 *    st=$18 i=$19 extra=$20; we had i=$16 arg0=$17 id=$18 st=$19).  `st` is
 *    the compiler's own `&AT_STATUS(o,0)` CSE, not a source variable.
 *    WARN of the 23 declaration permutations swept, the ONLY thing that
 *    matters is that `extra` precede `i`; every such cell is 4 and every other
 *    is 60.  [[levers.d/mwcc-gpr-decl-order-map]].
 *
 * 5. THE LAST TWO WORDS, and both are one-token rewrites:
 *      `extra + i * 0x29 + 0x46`  ->  `extra + (i * 0x29 + 0x46)`
 *        retail adds the 0x46 to the product FIRST (`addiu $2,$2,0x46` then
 *        `addu $7,$20,$2`); the default left association does it the other way.
 *      `if (i >= 3)`  ->  `if (i > 2)`
 *        THE SAME `slti` EITHER WAY -- but retail puts the result in `$at` and
 *        the `>= K` spelling puts it in `v0`.  WARN `!(i < 3)` and `3 <= i` are
 *        both the `v0` object; only `i > 2` moves it.  A REGISTER lever hiding
 *        in a comparison operator, next to [[levers.d/branch-class-screen]].
 */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_id_L96_T95_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 193 words, ? bad   after: 192 words, 73 bad   (retail 192 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_id_L113_T112_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 194 words, ? bad   after: 193 words, ? bad   (retail 192 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* ===== LANE nd, session 19 -- 6 words LONG -> TWO words LONG (0x308 vs 0x300).
 * TWO levers landed:
 *  1. [[m2c-switch-arm-order]].  retail's chain tests 3, then 2, then 1 with
 *     `beql` INTO each arm => it IS a switch and the SOURCE order is the chain
 *     REVERSED: case 1, case 2, case 3.  m2c had written 3,2,1 and that alone
 *     produced FOUR whole-block moves in n_odiff.  The reorder removed every
 *     one of them and is worth 1 word.
 *  2. `id` is an s32 LOCAL masked AT EACH USE, not a u16 local.  retail:
 *     `addiu $17,$19,0x3F` (unmasked) then `andi $5,$17,0xFFFF` at each of the
 *     eight call sites.  `u16 id` gives a bare `daddu`.  Worth 3 words.
 * ⚠⚠ THIS FILE'S OWN "gr2-park REFUTES the .lit4 hypothesis" PARAGRAPH IS
 * INVALID REASONING.  It concludes the nine D_0047Dxxx are "genuine
 * gp-relative lwc1 externs, hand-verified against the actual disassembly".
 * A `.lit4` POOL ENTRY EMITS THE IDENTICAL `lwc1 $fN,-K($28)` -- the
 * disassembly cannot tell the two apart, so that check has no discriminating
 * power at all.  0x0047D1D0-0x0047D7FF is mwcc's float literal pool and FIVE
 * of the nine are inside it (D_0047D354 = 1.2f, plus D_0047D350, D_0047D344,
 * D_0047D454, D_0047D7C4).  The literal spelling closed normal_ShopMenuBuyRowsRefresh_50b5c0
 * and normal_FieldHudBtlEscStep_4f0cf0 in this same lane.  It is UNTESTED here and is the
 * next arm.  3 round trips spent. */
/* PARKED (session gr11, tag gr11; re-checked session gr2-park): LENGTH-
 * CHANGING, 0x318 vs retail's 0x300 (6 words too long).
 *
 * gr2-park REFUTES the gr11 ".lit4 externs" hypothesis: the two "defined in
 * this object's .lit4" build notes are fully explained by the two existing
 * `cur = 1.9f;` LITERAL statements already in this file (case 1, both
 * copies) -- bytecheck.py emits that exact note whenever a relocation
 * targets a symbol the OBJECT ITSELF defines in .lit4 (i.e. a literal this
 * compile pooled), which is expected and correct for a genuine literal, not
 * a sign of an undiscovered extern.  Do not convert any more of the nine
 * D_0047Dxxx externs to literals on the theory that the lit4 notes are
 * flagging them -- they are not; all nine were hand-verified against the
 * actual disassembly (see below) as genuine gp-relative `lwc1` externs, each
 * at its own distinct offset from $28.
 *
 * gr2-park ALSO hand-verified the `case 2` and `case 3` bodies instruction-
 * for-instruction against asm/overlays/normal/matchings/normal/
 * normal_MenuBattleEndLevelUpLabelUpdate_4ea3f0.s and found NO discrepancy -- every call's argument
 * order, every float constant (1.0f/-1.0f/0.5f materialized via lui+mtc1,
 * the D_0047Dxxx values via lwc1), and the branch-likely / duplicated-
 * delay-slot shape for `if (v <= 1.0f) {...} else if (v >= cur) {...}` all
 * match retail exactly, including the register-reuse trick where `f12`
 * carries 1.0f across a squashed branch-likely delay slot into the
 * fallthrough arm's `func_2905B0(...,1.0f,1.0f,1.0f,-1.0f)` call (mov.s
 * $f13,$f12 / $f14,$f12 with no reload).  Not yet checked in the same depth:
 * `case 1` (status==1)'s FIRST half, from the `id = i+0x3F` /
 * `func_291110` call through the `extra = (i>=3) ? 6 : 0` branch-likely
 * shape (0x004EA418-0x004EA490) -- that's the most likely remaining home for
 * the 6-word overrun and was not fully instruction-matched this session.
 * No source changes made; 1 build round trip spent (unchanged rebuild, to
 * capture the real .lit4 diagnostic instead of guessing). */
#include "types.h"
/* normal 0x004EA3F0 -- per-record status-machine tick over an array of
 * records whose status byte lives at offset 0xF9 (byte-indexed) and whose
 * float record lives at offset 0x34 with a 0xC-byte stride; the shared
 * widget context is the address arg0+0x14. */

typedef struct Obj { u8 pad00[0x8]; s32 f08; u8 pad0C[0x14 - 0xC];
                     u8 f14; } Obj;

#define AT_STATUS(o, i)  (*((s8 *)(o) + 0xF9 + (i)))
#define AT_F34(o, i)     (*(f32 *)((u8 *)(o) + (i) * 0xC + 0x34))
#define WIDGET(o)        ((void *)&(o)->f14)

extern s64   D_0047D1B8;          /* gp - 0x7FB8 */
extern f32   D_0047D354;          /* gp - 0x7E1C */
extern f32   D_0047D910;          /* gp - 0x7860 */
extern f32   D_0047D7C4;          /* gp - 0x79AC */
extern f32   D_0047D914;          /* gp - 0x785C */
extern f32   D_0047D918;          /* gp - 0x7858 */
extern f32   D_0047D454;          /* gp - 0x7D1C */
extern f32   D_0047D350;          /* gp - 0x7E20 */
extern f32   D_0047D900;          /* gp - 0x7870 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_MenuBattleEndLevelUpLabelUpdate_4ea3f0(Obj *arg0)
{
    void *o;
    s32 id;
    s32 extra;
    s32 i;
    f32 v;
    f32 cur;

    for (i = 0; i < arg0->f08; i++) {
        o = (u8 *)arg0 + i;
        extra = 0;
        switch (AT_STATUS(o, 0)) {
        case 1:
            id = i + 0x3F;
            UiSetWidgetsVisibleById_291110(WIDGET(arg0), id, 1, 1);
            if (i > 2) {
                extra = 6;
            }
            UiSetWidgetPos_290f60(WIDGET(arg0), id, 0x49, extra + (i * 0x29 + 0x46));
            UiFadeWidgetAlpha_290690(WIDGET(arg0), id, D_0047D354, D_0047D910, 0.0f);
            UiSetWidgetColor_2905b0(WIDGET(arg0), id, 0.5f, 0.5f, 0.5f, 0.0f);
            cur = 1.9f;
            UiFadeWidgetColor_2904e0(WIDGET(arg0), id, cur, cur, cur, -1.0f, D_0047D7C4);
            cur = 1.9f;
            UiFadeWidgetColor_2904e0(WIDGET(arg0), (u16)(i * 3 + 0x17), cur, cur, cur, -1.0f, D_0047D7C4);
            AT_F34(arg0, i) = 4.0f;
            AT_STATUS(o, 0) = 2;
            break;
        case 2:
            id = i + 0x3F;
            if (((unsigned char)DoubleGreaterEqual_100230(fptodp(UiGetWidgetAlpha_290770(WIDGET(arg0), id)), __builtin_bit_cast(double, (long long)(D_0047D1B8)))) != 0) {
                UiFadeWidgetAlpha_290690(WIDGET(arg0), id, 0.0f, D_0047D914, -1.0f);
                UiFadeWidgetColor_2904e0(WIDGET(arg0), id, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D918);
                UiFadeWidgetColor_2904e0(WIDGET(arg0), (u16)(i * 3 + 0x17), 1.0f, 1.0f, 1.0f, -1.0f, D_0047D918);
                AT_STATUS(o, 0) = 3;
            }
            break;
        case 3:
            id = i * 3 + 0x17;
            v = *((f32 *)UiGetWidgetColor_2904b0(WIDGET(arg0), id));
            if (v <= 1.0f) {
                UiSetWidgetColor_2905b0(WIDGET(arg0), id, 1.0f, 1.0f, 1.0f, -1.0f);
                cur = D_0047D454;
                UiFadeWidgetColor_2904e0(WIDGET(arg0), id, cur, cur, cur, -1.0f, D_0047D350);
            } else {
                cur = D_0047D454;
                if (v >= cur) {
                    UiSetWidgetColor_2905b0(WIDGET(arg0), id, cur, cur, cur, -1.0f);
                    UiFadeWidgetColor_2904e0(WIDGET(arg0), id, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D900);
                }
            }
            break;
        }
    }
}
