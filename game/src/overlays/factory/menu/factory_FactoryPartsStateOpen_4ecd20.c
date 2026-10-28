/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsStateOpen_4ecd20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004ECD20 -- 364 B / 91 words, 5 branches, 12 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.  Same context
 * (_gp - 0x724) as factory_FUN_004ECBF0.
 *
 * SWITCH cell (lane fy01 family key): `b .L004ECE78 / ld $31,0x20($29)` with
 * the `beql $2,$0` guard exactly two rows above it, annulling the body own
 * `daddu $4,$17,$0`.  ONE trailing `return 1`.
 *
 * * Assign the 0x8C field FIRST -- loads are emitted in REVERSE source order,
 *   giving `lw $16,0x94` then `lw $17,0x8C` in the `beqz $5` delay slot.
 * * `func_290460` returns a POINTER (the skip is followed by `lw $4,0x20($2)`).
 * * `-0x7EF8` is `D_0047D278` in the mwcc .lit4 literal pool.
 * * `s32 x; s32 y;` -> x at 0x3C($29), y at 0x38($29).
 */

typedef struct Slot {
    u8    pad00[0x20];
    void *f20;                                  /* +0x20 */
} Slot;

typedef struct Ctx {
    u8    pad00[0x8C];
    void *f8C;                                  /* +0x8C */
    u8    pad90[0x4];
    void *f94;                                  /* +0x94 */
} Ctx;

extern Ctx *D_00484A4C;                         /* _gp - 0x724  */
extern s32  D_00484AB8;                         /* _gp - 0x6B8  */
extern f32  D_0047D278;                         /* _gp - 0x7EF8 */

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

s32 factory_FactoryPartsStateOpen_4ecd20(s32 unused, s32 start)
{
    Slot *s;
    void *w;
    void *ctx;
    s32   x;
    s32   y;

    w = D_00484A4C->f8C;
    ctx = D_00484A4C->f94;
    if (start != 0) {
        UiSetWidgetVisible_290010(w, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(1);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        UiSetWidgetVisible_290010(w, 0x41, 1, -1);
        s = ((Slot *)UiFindWidget_290460(w, 0x42));
        if (s != 0) {
            if (s->f20 != 0) {
                UiLayoutPanelFrame_28d580(s->f20, 0, 0, 0x95, 0x170, 0);
            }
        }
        UiSetWidgetPos_290f60(w, 0x41, 0x200, 0x36);
        UiSetWidgetPos_290f60(w, 0x45, -0xE, 0);
        UiMoveWidgetUniform_290f50(w, 0x41, 0xE, 0x36, D_0047D278, 0);
        UiFadeWidgetAlpha_290690(w, 0x41, 1.0f, 0.125f, 0.0f);
        factory_FactoryPartsOpen_4f0920(D_00484A4C);
        D_00484AB8 = 0;
    }
    switch (D_00484AB8) {
    case 0:
        UiGetWidgetPos_2910a0(w, 0xC, &x, &y);
        if (x == 0) {
            if (y == 0) {
                D_00484AB8 = -1;
                StateMachineSetState_28ede0(ctx, 0x8926, 0);
            }
        }
        break;
    }
    return 1;
}
