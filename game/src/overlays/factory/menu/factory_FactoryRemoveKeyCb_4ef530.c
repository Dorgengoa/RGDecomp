/* rgp:protos */
#define RGP_SELF_factory_FactoryRemoveKeyCb_4ef530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EF530 -- 88 B / 22 words, 1 branch, 4 calls.
 *
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy01 seed batch.
 *
 * THE FAMILY KEY, measured on this unit.  The duplicated `ld $31` is NOT two
 * source returns tail-merged -- it is what mwcc emits for a SINGLE trailing
 * `return K` whose guard becomes a branch-LIKELY: the epilogue restore is the
 * annullable filler in the `beql` delay slot, and the shared tail from
 * `addiu $2,$0,K` is simply the one and only epilogue.
 *
 * An explicit early `return 1;` (round trip 1 of this lane, tag fy01) is the
 * measured NEGATIVE: it costs TWO EXTRA WORDS, 0x60 vs 0x58, because mwcc
 * refuses the likely-branch and emits `bne $2,$0,+3 / nop` then
 * `b <exit> / addiu $2,$0,1`, leaving exactly ONE `ld $31`.
 *
 * * `func_1B9520(func_207DF0(), 5, 0, 1.0f)` is copied verbatim from
 *   byte-identical factory_FactoryMaterialClearConfirmOpen_4f2a70; the float takes $f12 regardless of
 *   its argument position, so the (p, s32, s32, f32) and (p, f32, s32, s32)
 *   prototypes are the SAME object -- 004fb840 uses the other one.
 * * `nop` in func_207DF0's delay slot: the only candidate filler is the
 *   `lui 0x3F800000`, and it cannot go there because it targets $2, which
 *   still holds the return value the next instruction copies into $4.
 */

extern u8 D_004B2570[];
extern void    *D_00484A54;                     /* _gp - 0x71C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryRemoveKeyCb_4ef530(void)
{
    if (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
        factory_FactoryRemoveDialogOpen_4fcee0(D_00484A54);
    }
    return 1;
}
