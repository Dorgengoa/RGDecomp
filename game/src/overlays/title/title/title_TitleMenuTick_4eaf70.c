/* rgp:protos */
#define RGP_SELF_title_TitleMenuTick_4eaf70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EAF70 -- the OPTIONS-screen tick, and the largest
 * function in the overlay at 736 instructions.
 *
 * `enter` rebuilds the row highlight from the current selection; the rest runs
 * every frame: the attract timeout, the pad poll that arms the confirm, the
 * selection-changed path that re-lays the four rows and re-cues audio, the
 * fade ramp, and finally the hand-off that picks the next screen from the
 * selection.  D_004803AC is the selected row (1..4) and D_0048419C the
 * widescreen flag, which shifts every row by four pixels.
 *
 * THE SAME GLOBAL IS DISPATCHED TWICE, AND THE TWO DISPATCHES ARE DIFFERENT
 * CONSTRUCTS.  Both read D_004803AC and both have arms 1..4:
 *  - 0x004EB528 is a SWITCH.  Its chain runs 4,3,2,1 (reverse source order)
 *    and each `beql` delay slot carries THAT CASE'S OWN STORE.
 *  - 0x004EBA34 is an if/else-if CHAIN.  Its chain runs 1,2,3,4 (source order)
 *    and each `bnel` delay slot carries the NEXT GUARD'S CONSTANT.
 * => Read the delay slot, not the arm count.  Writing either one as the other
 * is the right length and the wrong bytes.
 *
 * PARKED at 5 words, RIGHT LENGTH, on two residues -- both allocation, both
 * with three-plus spellings measured and a byte-for-byte identical object:
 *
 * 1. FOUR words are the $at class.  At 0x004EB21C and 0x004EB27C retail puts a
 *    guard's `slti` in $1 and we put it in $2, and the `bnel` that reads it
 *    follows.  Retail keeps the compared value AND the previous compare live
 *    across the branch; we let the first one die and reuse its register.  This
 *    is the SAME residue that parks title_FUN_004EBAF0 / 004EAB10 / 004EAD40,
 *    so the four functions are 4,600 bytes on one fix.
 *    Tried here: nested `if` instead of `&&`, dropping the `c` local and
 *    re-reading D_00484164.  Both give an identical object.
 *    Measured over all five overlays: a compare feeding a branch-likely lands
 *    in $2/$3 669 times and in $at 308 times, so it is NOT a rule about the
 *    branch kind -- it is real register pressure and the pressure comes from
 *    somewhere this reading has not found.
 *
 * 2. ONE word is the negating multiply at 0x004EB950: retail
 *    `mul.s $f0, $f1, $f0` against our `mul.s $f0, $f0, $f1`, with both
 *    operands already in the right registers.  Four spellings
 *    (`X * -1.0f`, `-1.0f * X`, the reload form, and a named local for the
 *    load) all give the identical object -- mwcc canonicalises a commutative
 *    float multiply, exactly as [[subsystem-decomp-track]] records.
 *
 * WHY D_004803B4 IS `volatile`: retail stores it TWICE in a row, first the raw
 * D_0047D564 and then that value negated, and mwcc deletes the first as a dead
 * store in every non-volatile spelling -- which is a LENGTH defect, not a byte
 * one, so the unit could not even be scored.  `volatile` on the declaration is
 * what keeps it; a `*(volatile f32 *)&` CAST DOES NOT (measured).  ⚠ This is a
 * fourth shape of the volatile lever -- anti-DEAD-STORE, next to the three
 * anti-CSE shapes -- and it is INFERRED from the object, not proven from the
 * game: the reading is consistent because the other two accesses to the same
 * global in this function still match with it applied.
 *
 * ⚠ objdump ELIDES RUNS OF IDENTICAL WORDS as `...`, so the two hazard `nop`s
 * mwcc puts between `div.s $f12` and a `jal` read as MISSING.  Pass -z.  That
 * cost a wrong "we are 2 words short here" reading; the reference corpus says
 * `div.s` before a control transfer carries 2 nops ~50 times and never 0.
 *
 * SESSION 3c -- everything further that was measured and moved NOTHING (the
 * object is byte-for-byte identical unless a length is quoted):
 *   $at sites: a named local for the compared global at site 2; the first
 *     compare materialised into a `u8` (LONGER, 0xb88); both together (0xb88).
 *   the multiply: `D_0047D564 * kNegOne` with a file-static `const f32`, and
 *     the two neighbouring stores reordered two ways.
 *   ⚠ `-D_0047D564`, `-D_004803B4` and `0.0f - D_0047D564` are all THREE WORDS
 *     SHORTER (0xb74) -- mwcc emits `neg.s`/`sub.s` for those -- so retail's
 *     `mul.s` really is a literal multiply by -1.0f and only its fs/ft order
 *     is open.  That is the commutative-float canonicalisation class, which
 *     [[subsystem-decomp-track]] already records as not reachable by operand
 *     order; seven spellings now agree.
 *
 * ★★ THE WORKED EXAMPLE FOR THE $at CLASS, AND WHERE IT STOPS.  The matched
 * main unit MenuCharaAbilityPageSetRowRange_341ba0 emits `slti $1, $3, 0x7 / beql $1, $0` from
 * `t2 = o->m74; if ((t2 < 7) != 0) { r->m0E = t2 - 1; } else { ... }` -- the
 * COMPARED VALUE IS LIVE IN THE ARM, so the compare needs a third register and
 * takes $at.  All 22 $at-compare sites across every matched unit in the tree
 * (5,262 scanned) are that same shape.
 * ⚠ This function's site at 0x004EB27C is NOT: the loaded D_00484164 is dead
 * the instant the compare reads it, on both edges.  So "keep the compared value
 * live" is a real rule, it is confirmed 22/22, and it does not explain this
 * site or 0x004EB21C.  That is where the class stands.
 */

typedef struct Sel {
    u8 pad0[0x12];
    s16 f12;
} Sel;

typedef struct Widget {
    u8 pad0[0xE];
    s16 fE;
    u8 pad10[6];
    s16 f16;
} Widget;

extern f32 D_0047D1FC;
extern f32 D_0047D248;
extern f32 D_0047D278;
extern f32 D_0047D35C;
extern f32 D_0047D518;
extern f32 D_0047D564;
extern f32 D_0047D56C;
extern f32 D_0047D574;
extern u8 D_004803A4;
extern s16 D_004803AC;
extern f32 D_004803B0;
extern volatile f32 D_004803B4;
extern f32 D_004803B8;
extern void *D_004803D0[2];
extern void *D_00484154;
extern void *D_00484158;
extern void *D_0048415C;
extern void *D_00484160;
extern s32 D_00484164;
extern s32 D_00484168;
extern s16 D_0048416C;
extern void *D_00484170;
extern s16 D_00484178;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;
extern f32 D_00484190;
extern s16 D_00484194;
extern s16 D_00484198;
extern s16 D_0048419C;
extern s16 D_004841A0;
extern s16 D_004841A4;
extern u8 D_004841A8;
extern u8 D_004B2570;
extern void *const title_D_004F1400[4];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleMenuTick_4eaf70(s32 enter)
{
    Sel *o;
    Widget *w;
    s32 n;
    s32 c;
    s32 k;
    s16 h;
    s16 v;
    f32 f;
    f32 r;
    f32 neg;

    if (enter != 0) {
        D_00484168 = 0;
        UiEntryListSelectByTag_28ea90(D_0048415C, 0x7531, 0);
        MenuGridCursorInput_28e170(D_0048415C, (void *)&D_004B2570, 5, 0);
        o = ((Sel *)UiEntryListGetCurrentData_28ec60(D_0048415C));
        if (IsTgsDemoBuild_207f20() != 0) {
            D_004803AC = 1;
            UiSetWidgetPos_290f60(D_00484170, 2, 0xB4, 0x136);
        } else {
            n = -(o->f12 * (D_0048419C * 4));
            if (o->f12 == 0) {
                D_004803AC = 1;
                UiSetWidgetPos_290f60(D_00484170, 2, 0xB4, n + 0x136);
                UiSetWidgetAlpha_2907a0(D_00484170, 3, 1.0f);
                UiSetWidgetAlpha_2907a0(D_00484170, 4, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 5, D_0047D248);
            }
            if (o->f12 == 1) {
                D_004803AC = 2;
                UiSetWidgetPos_290f60(D_00484170, 2, 0xB4, n + 0x14E);
                UiSetWidgetAlpha_2907a0(D_00484170, 3, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 4, 1.0f);
                UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 5, D_0047D248);
            }
            if (o->f12 == 2) {
                UiSetWidgetPos_290f60(D_00484170, 2, 0xB4, n + 0x166);
                UiSetWidgetAlpha_2907a0(D_00484170, 3, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 4, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 5, D_0047D248);
                if (D_0048419C != 0) {
                    D_004803AC = 3;
                    UiSetWidgetAlpha_2907a0(D_00484170, 0x66, 1.0f);
                } else {
                    D_004803AC = 4;
                    UiSetWidgetAlpha_2907a0(D_00484170, 5, 1.0f);
                }
            }
            if (o->f12 == 3) {
                D_004803AC = 4;
                UiSetWidgetPos_290f60(D_00484170, 2, 0xB4, n + 0x17E);
                UiSetWidgetAlpha_2907a0(D_00484170, 3, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 4, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
                UiSetWidgetAlpha_2907a0(D_00484170, 5, 1.0f);
            }
        }
        D_0048416C = 0;
        D_00484164 = 0;
    }
    if (D_004803A4 != 1) {
        return 0;
    }
        c = D_00484164;
        if (c >= 0x6C2) {
            title_TitleMenuFadeOut_4ecd40(D_00484160);
            D_0048416C = 0;
        } else if (c > 0xC3 && D_0048416C == 0) {
            title_TitleMenuShow_4ecd80(D_00484160);
            if (IsTgsDemoBuild_207f20() != 0) {
                D_00484168 = 0;
                UiSetWidgetAlpha_2907a0(D_00484170, 2, 0.0f);
            }
            D_0048416C = 1;
        }
        if (D_00484164 > 0x1E &&
            (PadIsTriggered_1839f0((void *)&D_004B2570, 0x40) != 0 ||
             PadIsTriggered_1839f0((void *)&D_004B2570, 0x800) != 0) &&
            D_0048416C == 0) {
            title_TitleMenuShow_4ecd80(D_00484160);
            if (IsTgsDemoBuild_207f20() != 0) {
                D_00484168 = 0;
                UiSetWidgetAlpha_2907a0(D_00484170, 2, 0.0f);
            }
            D_0048416C = 1;
        }
        if (D_00484188 == 1 && D_0048418C == 0 && D_0048416C != 0) {
            k = MenuGridCursorInput_28e170(D_0048415C, (void *)&D_004B2570, 5, 0);
            o = ((Sel *)UiEntryListGetCurrentData_28ec60(D_0048415C));
            if (IsTgsDemoBuild_207f20() != 0) {
                f = Sinf_128fd0(D_0047D1FC * (f32)D_00484168 / 60.0f);
                if (f <= D_0047D564) {
                    f = D_0047D564;
                }
                UiSetWidgetAlpha_2907a0(D_00484170, 2, f);
                D_00484168 = (D_00484168 + 1) % 60;
                if (k == 1 || PadIsTriggered_1839f0((void *)&D_004B2570, 0x800) != 0) {
                    GameSceneSoundSlot6PlaySeVol_1d05c0(GetCurrentScene_1f5be0(), 0, 1.0f);
                    D_00484178 = 1;
                    D_0048418C = 1;
                }
            } else {
                n = -(o->f12 * (D_0048419C * 4));
                if (k == 1) {
                    McEndSession_372d60();
                    D_004841A8 = 0;
                    D_004841A4 = 0;
                    if (PadIsHeld_183a20((void *)&D_004B2570, 8) == 0 && o->f12 == 0) {
                        McSaveMergedFlagsClear_3730f0();
                    }
                    h = D_004841A0;
                    if (h != D_0048419C) {
                        D_0048419C = h;
                        w = ((Widget *)UiEntryListFindByTag_28ea40(D_0048415C, 0x7531));
                        if (D_0048419C != 0) {
                            w->fE = 3;
                            if (w->f16 == 2) {
                                w->f16 = 3;
                            }
                        } else {
                            w->fE = 2;
                            if (w->f16 == 3) {
                                w->f16 = 2;
                            }
                        }
                        n = -(o->f12 * (D_0048419C * 4));
                    }
                    if (o->f12 == 0) {
                        GameSceneSoundSlot6PlaySeVol_1d05c0(GetCurrentScene_1f5be0(), 0, 1.0f);
                    } else {
                        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 2, 0, 1.0f);
                    }
                    v = D_004803AC;
                    D_00484178 = 1;
                    switch (v) {
                    case 1:
                        D_0048418C = 1;
                        break;
                    case 2:
                        D_0048418C = 2;
                        break;
                    case 3:
                        D_0048418C = 3;
                        break;
                    case 4:
                        D_0048418C = 4;
                        break;
                    default:
                        D_0048418C = 0;
                        break;
                    }
                }
                if (o->f12 == 0) {
                    D_004803AC = 1;
                    UiMoveWidgetUniform_290f50(D_00484170, 2, 0xB4, n + 0x136, D_0047D278, 0);
                    UiSetWidgetAlpha_2907a0(D_00484170, 3, 1.0f);
                    UiSetWidgetAlpha_2907a0(D_00484170, 4, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 5, D_0047D248);
                }
                if (o->f12 == 1) {
                    D_004803AC = 2;
                    UiMoveWidgetUniform_290f50(D_00484170, 2, 0xB4, n + 0x14E, D_0047D278, 0);
                    UiSetWidgetAlpha_2907a0(D_00484170, 3, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 4, 1.0f);
                    UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 5, D_0047D248);
                }
                if (o->f12 == 2) {
                    UiMoveWidgetUniform_290f50(D_00484170, 2, 0xB4, n + 0x166, D_0047D278, 0);
                    UiSetWidgetAlpha_2907a0(D_00484170, 3, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 4, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 5, D_0047D248);
                    if (D_0048419C != 0) {
                        D_004803AC = 3;
                        UiSetWidgetAlpha_2907a0(D_00484170, 0x66, 1.0f);
                    } else {
                        D_004803AC = 4;
                        UiSetWidgetAlpha_2907a0(D_00484170, 5, 1.0f);
                    }
                }
                if (o->f12 == 3) {
                    D_004803AC = 4;
                    UiMoveWidgetUniform_290f50(D_00484170, 2, 0xB4, n + 0x17E, D_0047D278, 0);
                    UiSetWidgetAlpha_2907a0(D_00484170, 3, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 4, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
                    UiSetWidgetAlpha_2907a0(D_00484170, 5, 1.0f);
                }
            }
        }
        if (enter == 0 && D_00484178 != 2) {
            if (title_TitleMovieUpdate_4f04c0() != 0) {
                title_TitleMovieRelease_4f0440();
                D_004803B0 = 1.0f;
                D_004803B4 = D_0047D56C;
                D_00484194 = 0;
                D_00484198 = 0;
                D_00484164 = 0;
                title_TitleMenuWidgetsSetup_4ece80(D_00484160, D_00484170);
                D_0048417C = 2;
                D_00484188 = 0;
                D_0048418C = 0;
                UiSetWidgetsVisibleById_291110(D_00484170, 1, 0, 1);
                title_TitleMoviePlay_4f0600(title_D_004F1400[D_0048417C], D_00484154, 1,
                                   D_004803D0[D_0048417C]);
            } else {
                D_00484164 = D_00484164 + 1;
            }
        }
        if (D_0048418C != 0) {
            if (D_004803B0 < 0.5f) {
                UiFadeWidgetAlpha_290690(D_00484170, 2, 0.0f, D_0047D574, -1.0f);
                D_00484194 = D_00484194 + 1;
                if (D_00484194 >= 5) {
                    k = 0x1E;
                    if (IsTgsDemoBuild_207f20() == 0 &&
                        (D_004803AC == 1 || D_004803AC == 3)) {
                        k = 0x46;
                    }
                    r = 1.0f / (f32)(k + 0xA);
                    D_00484190 = -r;
                    UiFadeWidgetAlpha_290690(D_00484170, 1, 0.0f, r, -1.0f);
                    ScreenFadeOutColor_1cf730(GetCurrentScene_1f5be0(), k, 0.0f, 0.0f, 0.0f);
                }
            } else {
                f = D_004803B0 + D_004803B4;
                D_004803B0 = f;
                if (f >= D_0047D35C) {
                    D_004803B0 = D_0047D35C;
                    neg = -1.0f;
                    D_004803B4 = D_0047D564;
                    D_004803B4 = D_004803B4 * neg;
                }
                UiSetWidgetColor_2905b0(D_00484170, 2, D_004803B0, D_004803B0, D_004803B0,
                            -1.0f);
            }
        }
        f = D_004803B8 + D_00484190;
        D_004803B8 = f;
        title_TitleMovieSetVolume_4f05d0(f);
        f = UiGetWidgetAlpha_290770(D_00484170, 1);
        if (f >= 1.0f) {
            D_00484188 = 1;
        } else if (f <= 0.0f && D_00484188 == 1) {
            if (D_00484178 != 0) {
                title_TitleMovieStop_4f0480();
                title_TitleMovieRelease_4f0440();
                D_00484164 = 0;
                D_004803B8 = 1.0f;
                D_00484190 = 0.0f;
                if (IsTgsDemoBuild_207f20() != 0) {
                    StateMachineSetState_28ede0(D_00484158, 0xF, 1);
                } else {
                    v = D_004803AC;
                    if (v == 1) {
                        D_0048417C = 0;
                        D_00484188 = 2;
                    } else if (v == 2) {
                        StateMachineSetState_28ede0(D_00484158, 7, 1);
                    } else if (v == 3) {
                        D_00484188 = 2;
                        D_0048417C = 0;
                    } else if (v == 4) {
                        StateMachineSetState_28ede0(D_00484158, 0xB, 1);
                    }
                }
            }
    } else if (f <= D_0047D518 && D_00484188 == 1 && D_00484178 != 0) {
        D_00484178 = 2;
    }
    return 1;
}
