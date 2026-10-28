/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuStateMain_4eb4d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EB4D0 -- 2060 B.  The factory menu per-frame state
 * machine: an 11-arm `switch` on the u8 phase byte `D_00484A94` (_gp - 0x6DC),
 * with a nested 9-arm `switch` on `D_00484A90` (_gp - 0x6E0) inside arm 4 that
 * picks which help/label string id to hand to func_28EDE0.
 *
 * gp base is 0x00485170 -- calibrated against src/overlays/factory/
 * factory_FactoryMenuRowsSlideOut_4eb320.c, which records D_00484A44 = _gp - 0x72C and
 * D_00484A90 = _gp - 0x6E0.
 *
 * * The FLOAT gp slots in this unit are all inside the mwcc .lit4 LITERAL POOL
 *   (0x0047D1FC-0x0047D7FF), not globals, so they are written as literals:
 *     _gp - 0x7E14 = 0x0047D35C = 1.9f     _gp - 0x7D30 = 0x0047D440 = 0.3f
 *     _gp - 0x7C60 = 0x0047D510 = 0.4f     _gp - 0x7C58 = 0x0047D518 = 0.2f
 *     _gp - 0x7C54 = 0x0047D51C = -0.1f    _gp - 0x7C50 = 0x0047D520 = 0.1f
 *   1.0f / -1.0f / -0.125f have zero low halves and come from `lui`.
 *
 * * m2c called the two inner dispatches "irregular switch"es.  They are NOT
 *   switches: 0x004EB5D4-0x004EB658 is a plain if/else-if chain whose middle
 *   arm is `else if (v == 6 && func_1839F0(D_004B2570, 0x10) != 0)`.  The `&&`
 *   short-circuit is what makes the failing 0x10 test fall into the `v == 1`
 *   test (the duplicated `addiu $2, $0, 0x1` at .L004EB654 and in the `bnel`
 *   delay slot is the tell).
 *
 * * 0x004B2570 is the INCOMPLETE ARRAY `extern u8 D_004B2570[]` -- the project
 *   spelling used with these same two callees under src/bodies.  splat prints
 *   the resolved `lui $4, 0x4B` / `addiu $4, $4, 0x2570` because the overlay is
 *   already linked, but it is an ADDRESS: as a plain integer constant mwcc
 *   emits `lui $2, 0x4B` / `ori $4, $2, 0x2570` instead, in TWO registers.
 *
 * ==== STATE, lane fz23f, 2026-08-31: 515/515 words, 8 wrong.  FIRST EVER
 * MEASUREMENT of this unit -- it had never been compiled from any path.  The
 * file that was staged here was RAW m2c OUTPUT with 18 unresolved `?` types
 * and `saved_reg_gp->unk-6DC` pseudo-syntax; this is a full rewrite.
 *
 * SIX of the 8 wrong words are PURE .lit4 -- the whole word matches except the
 * 16-bit immediate of a `lwc1`, which reads 0 because the literal pool is
 * defined in THIS object.  `f_olink` retargets those against retail's pool
 * (`pk_obytecheck` cannot), so they are LINK-ADJUDICATED, not a residue:
 *     0x004EB6F4 (1.9f)  0x004EB748 (0.3f)  0x004EB814 (0.2f)
 *     0x004EB838 (-0.1f) 0x004EBA74 (0.4f)  0x004EBAA0 (0.1f)
 *
 * THE ONLY REAL RESIDUE IS TWO WORDS, at 0x004EB6EC/0x004EB6F0 in case 1 --
 * the `add.s` OPERAND ORDER:
 *     retail  lwc1 $f2, -0x4944($gp)   ours  lwc1 $f2, <lit4 0.3f>
 *             lwc1 $f1, <lit4 0.3f>          lwc1 $f1, -0x4944($gp)
 *     both then  add.s $f1, $f2, $f1
 * i.e. retail loads the VARIABLE into $f2 and the LITERAL into $f1; we do the
 * reverse.  mwcc COMMUTED our `D_0048082C + 0.3f`.  The control is case 2 four
 * words below: `D_0048082C - 0.3f` is non-commutative, mwcc kept the order,
 * and its `lwc1 $f2, -0x4944($gp)` MATCHES retail exactly.  UNTRIED (no round
 * trips left): write case 1 as `t = 0.3f + D_0048082C;` so the commute lands
 * back on retail's order.  That is a 2-word, length-neutral fix and it would
 * leave nothing but the link-adjudicated .lit4 words.
 *
 * FOUR LEVERS PAID HERE, all of them recorded ones:
 *  1. "Name the handle FIRST" -- BOTH missing words in the first compile were
 *     mwcc filling `jal func_367EC0`'s DELAY SLOT with a hoisted right-hand
 *     side (`lw $s0, 0x70($v0)` at 0x004EB684, `addiu $s0, $0, 0xD` at
 *     0x004EB980), where retail has a `nop`.  mwcc evaluates an assignment's
 *     RHS first; splitting the call into its own statement (`q = func_367EC0();`
 *     then `q[4] = ...` / `*q = 0xD;`) forces the call first and restores the
 *     nop.  The same fix applied to `ent = func_28EA40(..); ent->f16 = ..;`
 *     in case 6, which also turned our narrowed `lh` back into retail's `lw`.
 *  2. The incomplete array `extern u8 D_004B2570[]` (see above) -- 7 sites.
 *  3. [[insect-dispatch-branch-polarity]] in case 10: retail FALLS THROUGH to
 *     the `f14 == 0` arm, so it is `if (..f14 == 0) f(1); else f(0);`.
 *  4. The .lit4 pool table -- every gp float slot here is a literal.
 *
 * INSTRUMENT NOTE: `build/f21_proto.py`'s RETAIL column is armed and correct
 * (it confirmed every prototype), but its DRAFT column printed "(none)" for
 * every callee -- including on the CLOSED unit factory_FactoryMenuRowsSlideOut_4eb320, which has
 * explicit externs.  That half of the screen is DEAD; do not read its "(none)"
 * as "no wrong prototype".  `build/f21_loops.py` reported "0 converted", which
 * is correct: this unit has no loops at all.
 *
 * * The switch-1 DEFAULT branches to .L004EBCCC, one word PAST the `ld $31`,
 *   because mwcc put the `ld` in the `beql` delay slot.  That is codegen, not
 *   a second return path.
 */

typedef struct Scene {
    u8    pad00[0x64];
    void *f64;
    void *f68;
    void *f6C;
    u8    pad70[0x4];
    s32   f74;
} Scene;

typedef struct Obj728 {
    u8  pad00[0x70];
    s32 f70;
    u8  pad74[0x1C];
    u8  f90;
} Obj728;

typedef struct Obj720 {
    u8 pad00[0x70];
    u8 f70;
} Obj720;

typedef struct Ent {
    u8  pad00[0x14];
    s16 f14;
    s16 f16;
} Ent;

extern u8      D_004B2570[];
extern void   *D_004807E4;                      /* _gp - 0x498C */
extern void   *D_004807EC;                      /* _gp - 0x4984 */
extern u8      D_004807FC;                      /* _gp - 0x4974 */
extern f32     D_0048082C;                      /* _gp - 0x4944 */
extern Scene  *D_00484A44;                      /* _gp - 0x72C  */
extern Obj728 *D_00484A48;                      /* _gp - 0x728  */
extern Obj720 *D_00484A50;                      /* _gp - 0x720  */
extern u8      D_00484A84;                      /* _gp - 0x6EC  */
extern s32     D_00484A90;                      /* _gp - 0x6E0  */
extern u8      D_00484A94;                      /* _gp - 0x6DC  */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMenuStateMain_4eb4d0(s32 arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 v;
    s16 st;
    f32 t;
    s32 *q;
    Ent *ent;

    if (arg1 != 0 && D_00484A94 == 0) {
        UiEntryListSelectByTag_28ea90(D_00484A44->f68, 0x88B8, 0);
    }
    if (D_00484A84 != 0 && UiGetWidgetAlpha_290770(D_004807E4, 0x1A) <= 0.0f) {
        UiSetWidgetVisible_290010(D_004807E4, 0x1A, 0, -1);
        UiSetWidgetVisible_290010(D_004807EC, 0x97, 0, -1);
        UiSetWidgetAlpha_2907a0(D_004807EC, 0x97, 1.0f);
        D_00484A84 = 0;
    }
    switch (D_00484A94) {
    case 0:
        v = MenuGridCursorInput_28e170(D_00484A44->f68, D_004B2570, 4, 0);
        if (D_004807FC == 0) {
            factory_FactoryMenuTexReloadPoll_4ebe90();
        } else if (v == 2) {
            factory_FactoryMenuRowsSlideOut_4eb320();
            D_00484A90 = 8;
            D_00484A94 = 3;
        } else if (v == 6 && PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
            SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 6, 0, 1.0f);
            factory_FactoryMenuRowsSlideOut_4eb320();
            D_00484A90 = 8;
            D_00484A94 = 3;
        } else if (v == 1) {
            st = ((Ent *)UiEntryListFindByTag_28ea40(D_00484A44->f68, 0x88B8))->f16;
            D_00484A90 = st;
            if (st == 7) {
                q = ((s32 *)FactoryGetRequestPtr_367ec0());
                q[4] = D_00484A48->f70;
                if (factory_FactoryProduceCheck_4eb070() == 0) {
                    D_00484A94 = 8;
                    break;
                }
                UiEntryListSelectByTag_28ea90(D_00484A44->f68, 0x894E, 0);
            } else if (st == 6) {
                factory_FactoryMenuQuitConfirmOpen_4ea870();
            }
            D_00484A94 = 1;
            D_0048082C = 1.0f;
        }
        break;
    case 1:
        t = D_0048082C;
        t = t + 0.3f;
        D_0048082C = t;
        if (t >= 1.9f) {
            D_0048082C = 1.9f;
            D_00484A94 = 2;
        }
        t = D_0048082C;
        UiSetWidgetColor_2905b0(D_00484A44->f64, 0x19, t, t, t, 1.0f);
        break;
    case 2:
        t = D_0048082C - 0.3f;
        D_0048082C = t;
        if (t <= 1.0f) {
            D_0048082C = 1.0f;
            if (D_00484A90 == 6) {
                D_00484A94 = 0xA;
            } else {
                D_00484A94 = 3;
                factory_FactoryMenuRowsSlideOut_4eb320();
            }
            UiFadeWidgetAlpha_290690(D_00484A44->f64, 0x19, 0.0f, -0.125f, -1.0f);
        }
        t = D_0048082C;
        UiSetWidgetColor_2905b0(D_00484A44->f64, 0x19, t, t, t, 1.0f);
        break;
    case 3:
        UiGetWidgetPos_2910a0(D_00484A44->f64, 4, &a, &b);
        if (a < -0x7C && b == 0) {
            UiMoveWidgetUniform_290f50(D_00484A44->f64, 1, -0x30, -0xF, 0.2f, 0);
            UiFadeWidgetAlpha_290690(D_00484A44->f64, 1, 0.0f, -0.1f, -1.0f);
            D_00484A94 = 4;
        }
        break;
    case 4:
        UiGetWidgetPos_2910a0(D_00484A44->f64, 1, &a, &b);
        if (a == -0x30 && b == -0xF) {
            factory_FactoryMenuHideHeader_4f1220(D_00484A44);
            switch (D_00484A90) {
            case 0:
                D_00484A48->f90 = 0;
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x88D6, 0);
                break;
            case 1:
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x8912, 0);
                break;
            case 2:
                D_00484A50->f70 = 0;
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x8930, 0);
                break;
            case 3:
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x894E, 0);
                break;
            case 4:
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x896C, 0);
                break;
            case 5:
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x89C6, 0);
                break;
            case 6:
                q = ((s32 *)FactoryGetRequestPtr_367ec0());
                *q = 0xD;
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x88C2, 0);
                UiSetWidgetVisible_290010(D_00484A44->f64, 0x1A, 0, -1);
                break;
            case 7:
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x89E4, 0);
                break;
            case 8:
                D_00484A50->f70 = 1;
                StateMachineSetState_28ede0(D_00484A44->f6C, 0x8930, 0);
                D_00484A90 = ((Ent *)UiEntryListFindByTag_28ea40(D_00484A44->f68, 0x88B8))->f16;
                break;
            }
            D_00484A94 = 5;
        }
        break;
    case 5:
        UiSetWidgetVisible_290010(D_00484A44->f64, 1, 1, -1);
        UiSetWidgetVisible_290010(D_00484A44->f64, 0x1A, 0, -1);
        UiSetWidgetVisible_290010(D_00484A44->f64, 0xC, 0, -1);
        UiMoveWidgetUniform_290f50(D_00484A44->f64, 1, -1, -1, 0.4f, 0);
        UiFadeWidgetAlpha_290690(D_00484A44->f64, 1, 1.0f, 0.1f, -1.0f);
        UiSetWidgetAlpha_2907a0(D_00484A44->f64, 0x19, 1.0f);
        UiSetWidgetPos_290f60(D_00484A44->f64, 3, -0xAA, 0);
        D_00484A94 = 7;
        break;
    case 6:
        UiGetWidgetPos_2910a0(D_00484A44->f64, 0xA, &a, &b);
        if (a == 0 && b == 0) {
            D_00484A94 = 0;
            UiEntryListSelectByTag_28ea90(D_00484A44->f68, 0x88B8, 1);
            D_00484A44->f74 = D_00484A90;
            ent = ((Ent *)UiEntryListFindByTag_28ea40(D_00484A44->f68, 0x88B8));
            ent->f16 = D_00484A90;
        }
        break;
    case 7:
        UiGetWidgetPos_2910a0(D_00484A44->f64, 1, &a, &b);
        if (a == -1 && b == -1) {
            factory_FactoryMenuRowsSlideIn_4eb3c0();
            D_00484A94 = 6;
        }
        break;
    case 8:
        factory_FactoryMenuCursorBob_4f0f30(D_00484A44, 0);
        if (PadIsTriggered_1839f0(D_004B2570, 0x20) != 0 || PadIsTriggered_1839f0(D_004B2570, 0x40) != 0) {
            D_00484A84 = 1;
            UiFadeWidgetAlpha_290690(D_00484A44->f64, 0x1A, 0.0f, -0.125f, -1.0f);
            D_00484A94 = 0;
        }
        break;
    case 9:
        if (PadIsTriggered_1839f0(D_004B2570, 0x20) != 0 || PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
            D_00484A94 = 5;
        }
        break;
    case 10:
        v = MenuGridCursorInput_28e170(D_00484A44->f68, D_004B2570, 0, 0);
        if (v == 2) {
            factory_FactoryMenuQuitConfirmClose_4eacd0(0);
        } else if (v == 1) {
            D_00484A84 = 1;
            if (((Ent *)UiEntryListFindByTag_28ea40(D_00484A44->f68, 0x88C2))->f14 == 0) {
                factory_FactoryMenuQuitConfirmClose_4eacd0(1);
            } else {
                factory_FactoryMenuQuitConfirmClose_4eacd0(0);
            }
        }
        break;
    }
    return 1;
}
