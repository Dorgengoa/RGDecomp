/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintListOpen_4ef3c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EF3C0 -- 360 B / 90 words, 6 branches, 11 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 * Same context (_gp - 0x728) as factory_FUN_004EF090 / 004EF2B0.
 *
 * SWITCH cell (lane fy01's family key): `b .L004EF51C / ld $31,0x0($29)` with
 * the `beql $2,$0` guard two rows above it, annulling the body's own
 * `lw $2,-0x728($28)`.  ONE trailing `return 1`.
 *
 * * `func_290460` returns a POINTER, not a flag: the `beql $2,$0` skip is
 *   followed by `lw $4,0x20($2)` off that same $2.  Name it, then test its
 *   `f20` in a nested `if` -- the annulled slot holds the MERGE's re-read of
 *   the gp global, which is the tell that the skip clears both tests.
 * * NO named local for the handle: every use re-reads `lw $2,-0x728($28)` and
 *   `lw $4,0x80($2)`.
 * * `-0x7EF8` is `D_0047D278` in mwcc's .lit4 literal pool.
 * * `s32 a; s32 b;` -> a at 0x1C($29), b at 0x18($29).
 */

typedef struct Slot {
    u8    pad00[0x20];
    void *f20;                                  /* +0x20 */
} Slot;

typedef struct Ctx {
    u8    pad00[0x6D];
    u8    f6D;                                  /* +0x6D */
    u8    pad6E[0x12];
    void *f80;                                  /* +0x80 */
    u8    pad84[0x4];
    void *f88;                                  /* +0x88 */
} Ctx;

extern Ctx *D_00484A48;                         /* _gp - 0x728  */
extern s32  D_00484B78;                         /* _gp - 0x5F8  */
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

s32 factory_FactoryBlueprintListOpen_4ef3c0(s32 unused, s32 start)
{
    s32   a;
    s32   b;
    Slot *s;

    if (start != 0) {
        UiSetWidgetVisible_290010(D_00484A48->f80, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(0);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        UiSetWidgetVisible_290010(D_00484A48->f80, 0x1F, 1, -1);
        s = ((Slot *)UiFindWidget_290460(D_00484A48->f80, 0x20));
        if (s != 0) {
            if (s->f20 != 0) {
                UiLayoutPanelFrame_28d580(s->f20, 0, 0, 0x199, 0x12C, 0);
            }
        }
        UiSetWidgetPos_290f60(D_00484A48->f80, 0x1F, 0x200, 0x36);
        UiMoveWidgetUniform_290f50(D_00484A48->f80, 0x1F, 0x37, 0x36, D_0047D278, 0);
        UiFadeWidgetAlpha_290690(D_00484A48->f80, 0x1F, 1.0f, 0.125f, 0.0f);
        factory_FactoryBlueprintListInit_4fbab0(D_00484A48);
        D_00484B78 = 0;
    }
    switch (D_00484B78) {
    case 0:
        UiGetWidgetPos_2910a0(D_00484A48->f80, 0xC, &a, &b);
        if (a == 0) {
            if (b == 0) {
                D_00484B78 = -1;
                StateMachineSetState_28ede0(D_00484A48->f88, 0x88EA, 0);
                D_00484A48->f6D = 1;
            }
        }
        break;
    }
    return 1;
}
