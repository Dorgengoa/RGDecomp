/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialStateClose_4ee360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EE360 -- the per-tick handler for panel id 0x8980
 * (dispatch table entry at main 0x00454F..).  324 bytes, 81 instructions,
 * 4 conditional branches, 9 calls.
 *
 * Third member of the 004ED6D0 / 004EDC10 / 004EE360 twin family; transcribed
 * from the confirmed seed `src/wf/factory/factory_FactoryMaterialQtyOpen_4ed6d0.c` with the
 * out-parameter tail borrowed from the already-matched
 * `src/overlays/factory/factory_FactoryPartsStateClose_4ecbf0.c`.
 *
 * * The first parameter is never read; the opening flag arrives in `$5`.
 * * The `w == 0` guard is the INVERTED early return (`bnez $16` INTO the body,
 *   failure falls through to `b <epilogue>` with `daddu $2,$0,$0` in the slot).
 * * `lw $4,-0x718($28)` appears twice -- once in the `beql` likely slot and
 *   once at the merge -- because it IS the merge instruction, i.e. the argument
 *   of `factory_FactoryMaterialFrameScroll_4f3a40`, not an argument of the guarded call.
 * * FIVE separate gp reads of `D_00484A58` in the listing, five in the source:
 *   `->f40` (w), the bare pointer, `->f40` again for func_2910A0, `->f48`, and
 *   `->f1F`.  mwcc does not CSE the gp load across a call, so the second
 *   `->f40` must be written out rather than reusing `w`.
 * * `-0x7C8C` is `D_0047D4E4` in mwcc's .lit4 pool -- the same pool entry
 *   004ECBF0 and 004EEF80 already use with func_290F50.
 * * `bnel`/`bnez` PAST the arm = if/else chain, case order AS WRITTEN; the
 *   `addiu $2,$0,1` in the `bnel` slot is the likely-slot copy of the ONE
 *   trailing `return 1;`.
 */

typedef struct View {
    u8    pad00[0x1F];
    u8    f1F;
    u8    pad20[0x20];
    void *f40;
    void *f44;
    void *f48;
} View;

extern View *D_00484A58;                        /* _gp - 0x718  */
extern f32   D_0047D4E4;                        /* _gp - 0x7C8C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialStateClose_4ee360(s32 unused, s32 start)
{
    void *w;
    s32   x;
    s32   y;

    w = D_00484A58->f40;
    if (w == 0) {
        return 0;
    }
    if (start != 0) {
        factory_FactoryMenuCaptionSlideOut_4eb1d0();
        UiMoveWidgetUniform_290f50(w, 0xB0, 0x200, 0xAF, D_0047D4E4, 0);
        UiFadeWidgetAlpha_290690(w, 0xB0, 0.0f, -0.125f, -1.0f);
        UiSetWidgetsVisibleById_291110(w, 0x63, 0, 1);
    }
    factory_FactoryMaterialFrameScroll_4f3a40(D_00484A58);
    UiGetWidgetPos_2910a0(D_00484A58->f40, 0xC, &x, &y);
    if (x == -0xAA) {
        if (y == 0) {
            StateMachineSetState_28ede0(D_00484A58->f48, 0x88CC, 0);
            UiSetWidgetVisible_290010(w, 0xC, 0, -1);
            UiSetWidgetVisible_290010(w, 0x69, 0, -1);
            UiSetWidgetVisible_290010(w, 0xB0, 0, -1);
            UiSetWidgetVisible_290010(w, 0x67, 0, -1);
            D_00484A58->f1F = 0;
        }
    }
    return 1;
}
