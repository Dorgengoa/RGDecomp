/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialStateTick_4ee070 1
#include "port/game_protos.h"
#line 1
/* SESSION 37, lane fg37f -- CLOSED, BYTE-IDENTICAL (was 2 bad, 187 words).
 * THE CLOSE IS ONE DELETED STATEMENT: the `return 1;` in the THEN arm of
 * `if (q->f10 == 0)` is gone, so BOTH arms fall through to the function's
 * tail `return 1;`.  It is semantically identical (the arm was the last
 * statement of the mode==1 block).
 * WHY.  The residue was 0x004EE178/17C: ours `b .L004EE344` + `addiu $2,$0,1`
 * (the EXPLICIT-return form), retail `b .L004EE340` + nop (the FALL-THROUGH
 * form).  Measured this session: the four OTHER fall-through exits
 * (0x4EE218/240/254/278) have an EMPTY delay slot in BOTH objects, so this is
 * NOT delay-slot fill-from-target.  mwcc turns a fall-through exit into an
 * explicit return when its SIBLING ARM carries a source-level `return`.  Take
 * the sibling's return away and mwcc re-derives BOTH exits itself -- and it
 * still emits the chained `b epilogue + addiu $2,$0,1` at 0x4EE168 for the
 * first arm, which is exactly retail.  So the explicit/fall-through split at
 * these two sites is mwcc's own LAYOUT decision; writing it into the C is
 * what broke it.
 * MEASURED the same run, same baseline (md5 324b4da80e97, 2 bad):
 *   both arms `return 1;`                          -> 4 bad (a853789c2dd1)
 *   both fall through + a shared `return 1;` inside the f78==2 block
 *                                                  -> LENGTH +1 word
 *   else-arm call spelled `factory_FactoryMaterialClearConfirmAnswer_4f2970(D_00484A58, 1)` -> INERT
 *   a fresh `c2 = c;` for the else arm, declared FIRST and LAST -> INERT
 *     (the s36 grouping x declaration-position twist does not fire on a
 *      residue that is not a register substitution)
 */

#include "types.h"

/* SESSION 23, lane fz23j -- 2 bad, EXACT LENGTH, UNCHANGED.
 * Residue 0x004EE178/17C: ours `b .L004EE344` + `addiu $2,$0,1` in the delay
 * slot; retail `b .L004EE340` + `nop`.  L340 is the shared `addiu $2,$0,1`
 * that falls into the epilogue at L344.
 * The rule retail obeys: an EXPLICIT `return 1;` compiles to a 2-word block
 * {addiu; b epilogue} whose addiu the scheduler sinks into the delay slot
 * (3 such sites, 0x4EE100 / 0x4EE168 / 0x4EE2A8, all byte-correct here); a
 * FALL-THROUGH exit compiles to `b .L004EE340` + nop (5 sites).  Ours turns
 * exactly one fall-through -- the else-arm of `if (q->f10 == 0)` -- into the
 * explicit-return form.
 * MEASURED INERT this lane (each byte-identical to the baseline object):
 *  - `goto tail;` at the end of that else-arm with `tail:` immediately before
 *    the function's final `return 1;`.
 *  - the same plus `goto tail;` at ALL FOUR other fall-through exits (end of
 *    the `(s16)n > 0` block, both mode==2 arms, the f2a70 arm).  mwcc
 *    normalises an explicit goto-to-the-tail to the fall-through CFG, so NO
 *    goto spelling can test this hypothesis -- stop trying it.
 *  - rewriting the whole `mode` chain as `switch (mode) { case 1: ... break;
 *    case 2: ... break; default: ... }` -> 60+ bad: the switch dispatch
 *    materialises 2 before 1 and reorders the entire compare chain.  The
 *    if / else-if chain is correct; do not convert it.
 * (An earlier lane measured dropping the `else` INERT -- same CFG.)
 * The lever is not statement shape at the C level.
 */

typedef struct Ctx {
    u8    pad00[0xA];
    s16   fA;
    s16   fC;
    u8    pad0E[0x11];
    u8    f1F;
    u8    pad20[0x20];
    void *f40;
    void *f44;
    void *f48;
    u8    pad4C[0x2C];
    u8    f78;
} Ctx;

typedef struct View {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} View;

typedef struct Grid {
    u8    pad00[0x70];
    void *f70;
    u8    pad74[0x1C];
    u8    f90;
} Grid;

typedef struct Msg {
    s32 f0;
} Msg;

extern Ctx  *D_00484A58;                        /* _gp - 0x718 */
extern Grid *D_00484A48;                        /* _gp - 0x728 */
extern f32   D_0047D510;                        /* _gp - 0x7C60 */
extern f32   D_0047D50C;                        /* _gp - 0x7C64 */
extern u8 D_004B2570[];

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

s32 factory_FactoryMaterialStateTick_4ee070(s32 unused, s32 start)
{
    void *b;
    void *u;
    void *w;
    View *q;
    Ctx  *c;
    Msg  *m;
    s32   mode;
    s32   n;
    s16   vy;
    s16   vx;

    b = D_00484A58->f40;
    u = D_00484A58->f48;
    w = D_00484A58->f44;
    if (start != 0) {
        UiEntryListSelectByTag_28ea90(w, 0x891C, 0);
        factory_FactoryMaterialCursorBob_4f3a70(D_00484A58, 1, 0);
        UiFadeWidgetAlpha_290690(b, 0x64, 1.0f, D_0047D510, -1.0f);
        factory_FactoryMaterialFrameInit_4f3d80(D_00484A58);
        factory_FactoryMaterialReqListLayout_4f2d50(D_00484A58);
    }
    D_00484A58->f1F = 0;
    if (factory_FactoryMaterialWaitRequest_4f31c0(D_00484A58) == 0) {
        return 1;
    }
    D_00484A58->f1F = 1;
    mode = MenuGridCursorInput_28e170(w, D_004B2570, 6, 0);
    q = ((View *)UiEntryListGetCurrentData_28ec60(w));
    if (mode == 1) {
        c = D_00484A58;
        if (c->f78 == 2) {
            if (q->f10 == 0) {
                factory_FactoryMaterialClearConfirmAnswer_4f2970(c, 0);
            } else {
                factory_FactoryMaterialClearConfirmAnswer_4f2970(c, 1);
            }
        } else {
            vy = q->f12;
            vx = q->f10;
            c->fA = vx;
            c->fC = vy;
            n = factory_FactoryMaterialCellItemCount_4f3370(D_00484A58);
            if ((s16)n > 0) {
                c = D_00484A58;
                UiSetWidgetPos_290f60(*(void *volatile *)&c->f40, 0x77,
                            c->fA * 44 + 7, c->fC * 50 + 74);
                StateMachineSetState_28ede0(u, 0x89A8, 0);
                UiFadeWidgetAlpha_290690(b, 0x64, 0.0f, D_0047D50C, -1.0f);
            }
        }
    } else if (mode == 2) {
        if (D_00484A58->f78 == 2) {
            factory_FactoryMaterialClearConfirmAnswer_4f2970(D_00484A58, 1);
        } else {
            StateMachineSetState_28ede0(u, 0x8976, 0);
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
        factory_FactoryMaterialClearConfirmOpen_4f2a70(D_00484A58);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x80) != 0) {
        if (D_00484A58->f78 == 2) {
            return 1;
        }
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
        m = ((Msg *)FactoryGetRequestPtr_367ec0());
        m->f0 = 1;
        D_00484A48->f90 = 4;
        if (D_00484A48->f70 != 0) {
            StateMachineSetState_28ede0(u, 0x88F4, 0);
        } else {
            StateMachineSetState_28ede0(u, 0x88D6, 0);
        }
        UiFadeWidgetAlpha_290690(b, 0xB0, 0.0f, -0.125f, -1.0f);
    }
    return 1;
}
