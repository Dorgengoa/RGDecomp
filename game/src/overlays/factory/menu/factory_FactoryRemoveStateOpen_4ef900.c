/* rgp:protos */
#define RGP_SELF_factory_FactoryRemoveStateOpen_4ef900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EF900 -- 240 B / 60 words, 4 branches, 8 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 *
 * SWITCH cell of the family key (lane fy01): there IS an unconditional
 * `b .L004EF9DC` whose delay slot holds `ld $31, 0x20($29)`, and the guard
 * `beql $2,$0` sits exactly two rows above it with the BODY's own first
 * instruction (`daddu $4,$17,$0`) annulled into its slot -- so the source is
 * `switch (D_00484BA8) { case 0: ... break; } return 1;` with ONE trailing
 * `return 1`, not an early return and not a plain `if`.
 *
 * * The two context fields are read into locals BEFORE the `start` guard and
 *   mwcc emits the two loads in REVERSE source order: assign 0x68 FIRST to get
 *   retail's `lw $16,0x70` ahead of the `lw $17,0x68` that rides the
 *   (non-likely) `beqz $5` delay slot.
 * * `factory_FactoryRemoveOpen_4fcf80` is passed the GLOBAL, re-read as `lw $4,-0x71C($28)`
 *   in the jal delay slot, not the named local -- mwcc does not CSE a gp load
 *   across a call.
 * * The out-params are `s32 x; s32 y;` in that declaration order: mwcc lays
 *   stack locals out in REVERSE declaration order, so x lands at 0x3C($29) and
 *   y at 0x38($29), which is what retail passes in $6/$7.
 * * The two range tests are NESTED ifs, not a `&&` join -- both are plain
 *   `bnez ... / nop` past the arm, the same shape as byte-identical
 *   factory_FactoryMaterialStateClose_4ee360.
 */

typedef struct Ctx {
    u8    pad00[0x68];
    void *f68;                                  /* +0x68 */
    u8    pad6C[0x4];
    void *f70;                                  /* +0x70 */
} Ctx;

extern Ctx *D_00484A54;                         /* _gp - 0x71C */
extern s32  D_00484BA8;                         /* _gp - 0x5C8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryRemoveStateOpen_4ef900(s32 unused, s32 start)
{
    void *w;
    void *ctx;
    s32   x;
    s32   y;

    w = D_00484A54->f68;
    ctx = D_00484A54->f70;
    if (start != 0) {
        UiSetWidgetVisible_290010(w, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(3);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        UiSetWidgetVisible_290010(w, 0x53, 1, -1);
        UiFadeWidgetAlpha_290690(w, 0x53, 1.0f, 0.125f, 0.0f);
        factory_FactoryRemoveOpen_4fcf80(D_00484A54);
        D_00484BA8 = 0;
    }
    switch (D_00484BA8) {
    case 0:
        UiGetWidgetPos_2910a0(w, 0xC, &x, &y);
        if (x == 0) {
            if (y == 0) {
                D_00484BA8 = -1;
                StateMachineSetState_28ede0(ctx, 0x8962, 0);
            }
        }
        break;
    }
    return 1;
}
