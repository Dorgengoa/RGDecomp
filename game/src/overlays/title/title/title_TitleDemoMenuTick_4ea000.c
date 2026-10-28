/* rgp:protos */
#define RGP_SELF_title_TitleDemoMenuTick_4ea000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EA000 -- the New Game / Continue / Options cursor.
 *
 * Polls the pad through func_28E170 (1 = down, 2 = up), moves the highlight
 * between the three rows, and once a row is committed (D_0048418C) runs the
 * confirm flash and hands off.  D_004803AC is the selected row and
 * D_00484178 the confirm latch, with 0xFF meaning "the extra fourth row".
 *
 * The idle timeout compares against 120.0f * D_0045B078, an absolute-addressed
 * const float outside the gp window.
 *
 * ★★★★★★ SOLVED (session 3f).  The last word was retail's
 * `daddiu $17, $0, 0x64` against our `addiu`, and the cause is the TYPE of the
 * widget id, not the constant.  Three things had to be true together:
 *   1. the widget id is a SEPARATE local from the pad result -- they share $17
 *      because their live ranges are disjoint, not because they are one
 *      variable;
 *   2. it is `u16`.  An UNSIGNED NARROW type is what makes mwcc materialise a
 *      constant with `daddiu` rather than `addiu`; and
 *   3. the three callees take it as `u16` too.  With an `s32` parameter the
 *      u16 -> int promotion is a zero-extending `andi` that mwcc sinks to the
 *      JOIN of the two arms -- one word long, and it also pushed the constant
 *      into $3 so the arms no longer wrote $17 directly.
 * ⚠ Measured and NOT the answer: `u32`, `0x64L`, `100U`, `(u16)0x64` on an
 * s32 local (all still 1 word); `long`, `unsigned long`, `s64` (+8, the
 * sibling assignment then needs a conversion); `s64` with the callees widened
 * (+5); one `u16` variable for BOTH roles with `func_28E170` returning `u16`
 * (+2, the return then needs truncating).
 * ★ How it was found, and it is the reusable part: `daddiu rX, $0, imm`
 * occurs in 660 of the tree's 20,195 reference listings and in ZERO of the
 * 5,262 matched units -- our toolchain had never been asked for it.  A corpus
 * scan for the same shape found `normal_FieldHudLogClose_4f88b0`, where the identical
 * `daddiu $17,$0,0x7A` is paired with `addiu $3,$17,1 / andi $17,$3,0xFFFF`,
 * which is the u16 wraparound idiom and named the type.
 * ★★★★ FOUR STRUCTURAL FIXES TOOK THIS FROM `len` TO ONE WORD, and three of
 * them are BLOCK ORDER, not spelling:
 *  1. In the D_0048418C != 0 section the `D_00484178 != 0xFF` body is
 *     PHYSICALLY LAST in retail, reached by a forward branch, with the
 *     `== 0xFF` body falling through and the long 290690/290F50 chain in the
 *     middle.  Writing it as m2c does -- `!= 0xFF` first -- keeps the call
 *     sequence correct and redistributes seventeen call gaps.  This one edit
 *     took ogap.py's divergent-gap count from 17 to 3.
 *  2. The tail's `== 0xFF` arm is likewise the fall-through.
 *  3. `D_004803AC = t;` after an if/else must be written as a STORE INSIDE
 *     BOTH ARMS -- retail duplicates it, the joined form is two words short.
 *     Same shape as the `return 1` corollary in [[overlay-c-pipeline]].
 *  4. ★ Two adjacent stores to different gp globals: mwcc REORDERS them
 *     freely, so the source order does not set the store order -- but it does
 *     set which value gets $2 and which $3.  Swapping
 *     `D_00484178 = 0xFF; D_0048418C = D_004803AC;` was worth EIGHT words
 *     across two sites, and permuting the three statements of the arm at
 *     0x004EA0D4 scored 4 / 1 / 4 / 5 / 5 / 5 -- one order out of six.
 */

typedef struct Sel {
    u8 pad0[0x12];
    s16 f12;
} Sel;

extern f32 D_0045B078;
extern f32 D_0047D248;
extern f32 D_0047D35C;
extern f32 D_0047D464;
extern f32 D_0047D51C;
extern f32 D_0047D520;
extern f32 D_0047D52C;
extern f32 D_0047D540;
extern f32 D_0047D544;
extern s16 D_004803AC;
extern void *D_00484158;
extern void *D_0048415C;
extern void *D_00484170;
extern s16 D_00484178;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;
extern u8 D_004B2570;

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

s32 title_TitleDemoMenuTick_4ea000(void *unused, s32 first)
{
    Sel *o;
    s32 id;
    u16 wid;
    f32 v;
    s16 t;

    if (first != 0) {
        PadIdleTimerReset_2f5ac0();
    }
    if (D_0048418C == 0) {
        id = MenuGridCursorInput_28e170(D_0048415C, (void *)&D_004B2570, 0, 0);
        o = ((Sel *)UiEntryListGetCurrentData_28ec60(D_0048415C));
        PadIdleTimerUpdate_2f5a60();
        if (PadIdleTimerGet_2f5ab0() > 120.0f * D_0045B078) {
            D_0048418C = D_004803AC;
            D_00484178 = 0xFF;
        } else if (id == 1 && D_0048418C == 0) {
            PadIdleTimerReset_2f5ac0();
            D_0048418C = D_004803AC;
            if (title_TitleDemoPvRowEnabledMaybe_4ed340() != 0 && o->f12 == 2) {
                D_00484178 = 0xFF;
                D_0048417C = 3;
                wid = 0x64;
            } else {
                D_00484178 = 1;
                wid = D_004803AC + 0x61;
            }
            UiSetWidgetColor_2905b0(D_00484170, wid, D_0047D464, D_0047D464, D_0047D464, 1.0f);
            UiFadeWidgetColor_2904e0(D_00484170, wid, D_0047D35C, D_0047D35C, D_0047D35C, 1.0f,
                        D_0047D520);
            UiFadeWidgetAlpha_290690(D_00484170, 0x65, 0.0f, D_0047D540, -1.0f);
        } else if (id == 2 && D_0048418C == 0) {
            PadIdleTimerReset_2f5ac0();
            D_0048418C = D_004803AC;
            D_00484178 = 0xFF;
        }
        if (D_0048418C == 0) {
            if (o->f12 == 0) {
                UiSetWidgetColor_2905b0(D_00484170, 0x62, 1.0f, 1.0f, 1.0f, 1.0f);
                UiSetWidgetColor_2905b0(D_00484170, 0x63, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                UiSetWidgetColor_2905b0(D_00484170, 0x64, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                D_004803AC = 1;
            }
            if (o->f12 == 1) {
                UiSetWidgetColor_2905b0(D_00484170, 0x62, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                UiSetWidgetColor_2905b0(D_00484170, 0x63, 1.0f, 1.0f, 1.0f, 1.0f);
                UiSetWidgetColor_2905b0(D_00484170, 0x64, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                if (title_TitleDemoPvRowEnabledMaybe_4ed340() != 0) {
                    D_004803AC = 4;
                } else {
                    D_004803AC = 2;
                }
            }
            if (o->f12 == 2) {
                UiSetWidgetColor_2905b0(D_00484170, 0x62, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                UiSetWidgetColor_2905b0(D_00484170, 0x63, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                UiSetWidgetColor_2905b0(D_00484170, 0x64, 1.0f, 1.0f, 1.0f, 1.0f);
                D_004803AC = 4;
            }
        }
    }
    if (D_0048418C != 0) {
        if (D_00484178 == 0xFF) {
            if (title_TitleDemoPvRowEnabledMaybe_4ed340() != 0 && D_0048417C == 3) {
                v = *((f32 *)UiGetWidgetColor_2904b0(D_00484170, 0x64));
                if (v >= D_0047D35C) {
                    UiFadeWidgetColor_2904e0(D_00484170, 0x64, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D51C);
                } else if (v <= 1.0f) {
                    UiFadeWidgetAlpha_290690(D_00484170, 0x61, 0.0f, D_0047D544, -1.0f);
                }
            } else {
            UiFadeWidgetAlpha_290690(D_00484170, 0x62, 0.0f, D_0047D52C, -1.0f);
            UiMoveWidgetUniform_290f50(D_00484170, 0x62, 0x100, 0, 20.0f, 1);
            UiFadeWidgetAlpha_290690(D_00484170, 0x63, 0.0f, D_0047D52C, -1.0f);
            UiMoveWidgetUniform_290f50(D_00484170, 0x63, 0x1C8, 0, 20.0f, 1);
            UiFadeWidgetAlpha_290690(D_00484170, 0x64, 0.0f, D_0047D52C, -1.0f);
            UiMoveWidgetUniform_290f50(D_00484170, 0x64, 0x290, 0, 20.0f, 1);
            UiSetWidgetsVisibleById_291110(D_00484170, 0x65, 0, 1);
            UiFadeWidgetAlpha_290690(D_00484170, 0x61, 0.0f, D_0047D51C, -1.0f);
            ScreenFadeOutColor_1cf730(GetCurrentScene_1f5be0(), 0xA, 0.0f, 0.0f, 0.0f);
            }
        } else {
            wid = D_004803AC + 0x61;
            v = *((f32 *)UiGetWidgetColor_2904b0(D_00484170, wid));
            if (v >= D_0047D35C) {
                UiFadeWidgetColor_2904e0(D_00484170, wid, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D51C);
            } else if (v <= 1.0f) {
                UiFadeWidgetAlpha_290690(D_00484170, 0x61, 0.0f, D_0047D544, -1.0f);
            }
        }
    }
    if (UiGetWidgetAlpha_290770(D_00484170, 0x61) <= 0.0f) {
        if (D_00484178 == 0xFF) {
            D_00484178 = 0;
            title_TitleSceneOverlayModeOff_4eaa00();
            StateMachineSetState_28ede0(D_00484158, 4, 0);
        } else {
            D_0048417C = 0;
            D_00484188 = 2;
            D_00484178 = 0;
        }
    }
    return 1;
}
