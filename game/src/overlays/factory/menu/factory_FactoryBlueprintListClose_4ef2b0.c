/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintListClose_4ef2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EF2B0 -- 264 B / 66 words, 4 branches, 8 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 *
 * TWIN of factory_FUN_004EEF80 (ratio 0.971): the same slide-in poller over a
 * different done-flag (-0x5F4 vs -0x5EC), clearing a context byte AFTER the
 * completion hook instead of calling factory_FactoryBlueprintViewRestore_4fa760 before it.
 *
 * 004EEF80's park header says this twin was "deliberately NOT written: it
 * would inherit the same residue".  That is OVERTURNED by lane fy01's family
 * key.  The residue there was an explicit early `return 1;` guard, which gets
 * the block LAYOUT right but inverts the shared epilogue: `addiu $2,$0,1` gets
 * stolen into the `b`'s delay slot and `ld $31` is left leading the tail.  The
 * listing's discriminator is that the `beql` guard sits exactly TWO rows above
 * the `b <tail>` -- an EMPTY fall-through -- which is a `switch` with one arm,
 * and the ONE trailing `return 1` then puts `ld $31` in the `b`'s slot:
 *
 *     beql $2,$0,.L004EF320 / lw $2,-0x728($28)   <- BODY's first insn annulled
 *     b .L004EF3AC          / ld $31,0x0($29)
 *
 * * `$4` is never read; the start flag arrives in `$5`.
 * * NO named local for the handle: every use is a fresh `lw $2,-0x728($28)` /
 *   `lw $4,0x80($2)` pair, because mwcc does not CSE a gp load across a call.
 * * `s32 a; s32 b;` in that order -> a at 0x1C($29), b at 0x18($29); stack
 *   locals are allocated in REVERSE declaration order.
 * * The `-1` in `$7` is shared by the flag store and func_290010's fourth
 *   argument; that is the scheduler, not a source-level temporary.
 */

typedef struct Ctx {
    u8    pad00[0x6D];
    u8    f6D;                                  /* +0x6D */
    u8    pad6E[0x12];
    void *f80;                                  /* +0x80 */
} Ctx;

extern Ctx  *D_00484A48;                        /* _gp - 0x728  */
extern s32   D_00484B7C;                        /* _gp - 0x5F4  */
extern void *D_004807E8;                        /* _gp - 0x4988 */
extern f32   D_0047D4E4;                        /* _gp - 0x7C8C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryBlueprintListClose_4ef2b0(s32 unused, s32 start)
{
    s32 a;
    s32 b;

    if (start != 0) {
        factory_FactoryMenuCaptionSlideOut_4eb1d0();
        UiMoveWidgetUniform_290f50(D_00484A48->f80, 0x1F, 0x200, 0x36, D_0047D4E4, 0);
        UiFadeWidgetAlpha_290690(D_00484A48->f80, 0x1F, 0.0f, -0.125f, -1.0f);
        D_00484B7C = 0;
    }
    switch (D_00484B7C) {
    case 0:
        UiGetWidgetPos_2910a0(D_00484A48->f80, 0xC, &a, &b);
        if (a == -0xAA) {
            if (b == 0) {
                D_00484B7C = -1;
                UiSetWidgetVisible_290010(D_00484A48->f80, 0xC, 0, -1);
                UiSetWidgetVisible_290010(D_00484A48->f80, 0x1F, 0, -1);
                UiSetWidgetVisible_290010(D_004807E8, 0x97, 0, -1);
                factory_FactoryBlueprintReturnToCaller_4eeb90();
                D_00484A48->f6D = 0;
            }
        }
        break;
    }
    return 1;
}
