/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintViewClose_4eef80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EEF80 -- start the panel's slide-in, then poll it:
 * once the tween reports its end position, latch the "done" flag, stop the
 * three animations and run the completion hook.
 * 264 bytes, 68 instructions, 4 conditional branches, 8 calls (br/ins 0.059).
 *
 * * TWIN of `factory_FactoryBlueprintListClose_4ef2b0` at ratio 0.971 -- the same poller over a
 * different done-flag (`_gp - 0x5F4`), and clearing a byte in the context
 * instead of calling `factory_FactoryBlueprintViewRestore_4fa760`.  Found by ranking the OPEN
 * population against ITSELF.
 *
 * ! The guard tests `$5`, the SECOND integer parameter, and `$4` is never read
 * -- the unused-parameter shape from
 * `levers.d/factory-unused-first-parameter.md`.
 *
 * * The two float constants arrive as `lui` + `mtc1`, which is how mwcc
 * materialises a float LITERAL that is not in the constant pool; `0.0f` gets
 * `mtc1 $0` for free.
 *
 * * The done-flag test is an EARLY RETURN, not an `if (flag == 0) { body }`:
 * retail branches to a SECOND epilogue with `b` + its own `ld $31`, and the
 * wrapped form gives a `bnel` skip that is three words short.
 *
 * * The stack pair is read off the FRAME: `a` at 0x1C is declared before `b` at
 * 0x18 because mwcc allocates locals downward in declaration order.
 *
 * !! PARKED -- RIGHT LENGTH (66 words), 5 bad, deliberately NOT in
 * `config/ocunits/factory.txt`.  The residue is a TAIL-MERGE tie-break: both
 * return sites return the literal 1, and mwcc has to choose which three-word
 * suffix to share.
 *     retail  b DONE / ld $31 ...  ld $31 ; DONE: addiu $2,$0,1 ; jr
 *     ours    b DONE / addiu $2 ... addiu $2 ; DONE: ld $31      ; jr
 * The `bnel`-vs-`bne` at the `a == -0xAA` compare follows from the same choice:
 * the constant we sink into that delay slot is retail's `nop`.
 * TEN spellings over two probe builds, none below 5: `a == -0xAA && b == 0`
 * (5), `goto done` (-1), the guard inverted inside the `if` (+1), two early
 * returns for the compares (+2), one early return plus a nested test (+1), a
 * named `r = 1` result variable (5), a `return 1` inside the `a` arm (7), an
 * `else if` (+1), and the whole body wrapped in `if (flag == 0)` with its own
 * `return 1` (-1).
 * => [[insect-scheduler-tiebreak]] reached through the EPILOGUE.  Its twin
 * `004EF2B0` is deliberately NOT written: it would inherit the same residue.
 */

typedef struct Ctx {
    u8    pad00[0x80];
    void *f80;
} Ctx;

extern Ctx *D_00484A48;                         /* _gp - 0x728  */
extern s32  D_00484B84;                         /* _gp - 0x5EC  */
extern void *D_004807E8;                        /* _gp - 0x4988 */
extern f32  D_0047D4E4;                         /* _gp - 0x7C8C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryBlueprintViewClose_4eef80(s32 unused, s32 start)
{
    s32 a;
    s32 b;

    if (start != 0) {
        factory_FactoryMenuCaptionSlideOut_4eb1d0();
        UiMoveWidgetUniform_290f50(D_00484A48->f80, 0x1F, 0x200, 0x36, D_0047D4E4, 0);
        UiFadeWidgetAlpha_290690(D_00484A48->f80, 0x1F, 0.0f, -0.125f, -1.0f);
        D_00484B84 = 0;
    }
    switch (D_00484B84) {
    case 0:
        UiGetWidgetPos_2910a0(D_00484A48->f80, 0xC, &a, &b);
        if (a == -0xAA) {
            if (b == 0) {
                D_00484B84 = -1;
                UiSetWidgetVisible_290010(D_00484A48->f80, 0xC, 0, -1);
                UiSetWidgetVisible_290010(D_00484A48->f80, 0x1F, 0, -1);
                UiSetWidgetVisible_290010(D_004807E8, 0x97, 0, -1);
                factory_FactoryBlueprintViewRestore_4fa760(D_00484A48);
                factory_FactoryBlueprintReturnToCaller_4eeb90();
            }
        }
        break;
    }
    return 1;
}
