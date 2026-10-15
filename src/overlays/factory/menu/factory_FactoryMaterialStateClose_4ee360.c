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

extern void factory_FactoryMenuCaptionSlideOut_4eb1d0(void);
extern void factory_FactoryMaterialFrameScroll_4f3a40(View *v);
extern void func_28EDE0(void *ctx, s32 id, s32 a);
extern void func_290010(void *w, s32 id, s32 a, s32 b);
extern void func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void func_2910A0(void *w, s32 id, s32 *x, s32 *y);
extern void func_291110(void *w, s32 id, s32 a, s32 b);

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
        func_290F50(w, 0xB0, 0x200, 0xAF, 0, D_0047D4E4);
        func_290690(w, 0xB0, 0.0f, -0.125f, -1.0f);
        func_291110(w, 0x63, 0, 1);
    }
    factory_FactoryMaterialFrameScroll_4f3a40(D_00484A58);
    func_2910A0(D_00484A58->f40, 0xC, &x, &y);
    if (x == -0xAA) {
        if (y == 0) {
            func_28EDE0(D_00484A58->f48, 0x88CC, 0);
            func_290010(w, 0xC, 0, -1);
            func_290010(w, 0x69, 0, -1);
            func_290010(w, 0xB0, 0, -1);
            func_290010(w, 0x67, 0, -1);
            D_00484A58->f1F = 0;
        }
    }
    return 1;
}
