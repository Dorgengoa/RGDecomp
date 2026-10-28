/* rgp:protos */
#define RGP_SELF_factory_FactoryMoveStateOpen_4ee910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EE910 -- 292 B / 73 words, 4 branches, 8 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 *
 * SWITCH cell (lane fy01's family key): `b .L004EEA20 / ld $31,0x20($29)` with
 * the `beql $2,$0` guard exactly two rows above it, annulling the body's own
 * `daddu $4,$17,$0`.  ONE trailing `return 1`.
 *
 * * Assign the 0x60 field FIRST (reverse emission order): retail's
 *   `lw $16,0x68` then `lw $17,0x60` in the `beqz $5` delay slot.
 * * The inner `D_00484A50->f70 == 1` test is a PLAIN `if` inside the start
 *   arm -- `bnel` PAST the arm, so it is an if-chain, and the annulled slot
 *   holds the fall-through's own `daddu $4,$17,$0`.  `lbu` means the field is
 *   `u8`.
 * * `s32 x; s32 y;` -> x at 0x3C($29), y at 0x38($29).
 */

typedef struct Ctx {
    u8    pad00[0x60];
    void *f60;                                  /* +0x60 */
    u8    pad64[0x4];
    void *f68;                                  /* +0x68 */
    u8    pad6C[0x4];
    u8    f70;                                  /* +0x70 */
} Ctx;

extern Ctx *D_00484A50;                         /* _gp - 0x720 */
extern s32  D_00484B28;                         /* _gp - 0x648 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMoveStateOpen_4ee910(s32 unused, s32 start)
{
    void *w;
    void *ctx;
    s32   x;
    s32   y;

    w = D_00484A50->f60;
    ctx = D_00484A50->f68;
    if (start != 0) {
        UiSetWidgetVisible_290010(w, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(2);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        if (D_00484A50->f70 == 1) {
            UiFadeWidgetAlpha_290690(w, 0xC, 0.0f, 1.0f, -1.0f);
        }
        UiSetWidgetVisible_290010(w, 0x4D, 1, -1);
        UiFadeWidgetAlpha_290690(w, 0x4D, 1.0f, 0.125f, 0.0f);
        factory_FactoryMoveOpen_4f45a0(D_00484A50);
        D_00484B28 = 0;
    }
    switch (D_00484B28) {
    case 0:
        UiGetWidgetPos_2910a0(w, 0xC, &x, &y);
        if (x == 0) {
            if (y == 0) {
                D_00484B28 = -1;
                StateMachineSetState_28ede0(ctx, 0x8944, 0);
            }
        }
        break;
    }
    return 1;
}
