/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintViewOpen_4ef090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EF090 -- 312 B / 78 words, 4 branches, 10 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 *
 * SWITCH cell (lane fy01's family key): `b .L004EF1BC / ld $31,0x0($29)` with
 * the `beql $2,$0` guard two rows above it, annulling the body's own
 * `lw $2,-0x728($28)`.  ONE trailing `return 1`.
 *
 * * NO named local for the handle: every use is a fresh `lw $2,-0x728($28)` /
 *   `lw $4,0x80($2)`, because mwcc does not CSE a gp load across a call.
 * * `-0x7EF8` is `D_0047D278` in mwcc's .lit4 literal pool, so the fifth
 *   argument of func_290F50 is an EXTERN float, not a written literal.
 * * `s32 a; s32 b;` -> a at 0x1C($29), b at 0x18($29).
 */

typedef struct Ctx {
    u8    pad00[0x80];
    void *f80;                                  /* +0x80 */
    u8    pad84[0x4];
    void *f88;                                  /* +0x88 */
} Ctx;

extern Ctx *D_00484A48;                         /* _gp - 0x728  */
extern s32  D_00484B80;                         /* _gp - 0x5F0  */
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

s32 factory_FactoryBlueprintViewOpen_4ef090(s32 unused, s32 start)
{
    s32 a;
    s32 b;

    if (start != 0) {
        UiSetWidgetVisible_290010(D_00484A48->f80, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(0);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        UiSetWidgetVisible_290010(D_00484A48->f80, 0x1F, 1, -1);
        UiSetWidgetVisible_290010(D_00484A48->f80, 0x20, 0, -1);
        UiSetWidgetPos_290f60(D_00484A48->f80, 0x1F, 0x200, 0x36);
        UiMoveWidgetUniform_290f50(D_00484A48->f80, 0x1F, 0x37, 0x36, D_0047D278, 0);
        UiFadeWidgetAlpha_290690(D_00484A48->f80, 0x1F, 1.0f, 0.125f, 0.0f);
        factory_FactoryBlueprintViewInit_4fa8c0(D_00484A48);
        D_00484B80 = 0;
    }
    switch (D_00484B80) {
    case 0:
        UiGetWidgetPos_2910a0(D_00484A48->f80, 0xC, &a, &b);
        if (a == 0) {
            if (b == 0) {
                D_00484B80 = -1;
                StateMachineSetState_28ede0(D_00484A48->f88, 0x8908, 0);
            }
        }
        break;
    }
    return 1;
}
