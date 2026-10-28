/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintAskClear_4fae70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FAE70 -- leave the parts screen: play the exit
 * cue, move the panel to state 6, rebuild it and retire three widgets.
 * 160 bytes, 40 instructions, 2 branches, 6 calls.
 *
 * * The `Panel` container is `factory_FactoryBlueprintConfirm_4fb840`'s verbatim -- `f70` the
 *   selection handle, `f7C` the `u8` state, `f80` the widget handle.
 * * Two early returns: `bnez $3` PAST the body on the state and `beql $3, $0`
 *   with `ld $31` in the likely slot on the handle.
 * * `func_1B9520(void *s, f32 g, s32 a, s32 b)` is the merged spelling from
 *   `factory_FactoryBlueprintConfirm_4fb840`; the `func_207DF0()` result is NESTED here.
 * * `sb $2, 0x7C($16)` rides `factory_FactoryBlueprintDialogLayout_4f7ed0`'s delay slot, so the
 *   state store PRECEDES the rebuild call in source.
 * * `daddu $7, $6, $0` on the first `func_291110` is mwcc noticing both
 *   trailing arguments are 1 -- one constant, two registers.
 */

typedef struct Panel {
    u8    pad00[0x70];
    s32   f70;
    u8    pad74[0x8];
    u8    f7C;
    u8    pad7D[0x3];
    void *f80;
} Panel;

extern void *D_004807EC;                        /* _gp - 0x4984 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintAskClear_4fae70(Panel *o)
{
    if (o->f7C != 0) {
        return;
    }
    if (o->f70 == 0) {
        return;
    }
    SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
    o->f7C = 6;
    factory_FactoryBlueprintDialogLayout_4f7ed0(o);
    UiSetWidgetsVisibleById_291110(D_004807EC, 0x97, 1, 1);
    UiSetWidgetsVisibleById_291110(o->f80, 0x40, 0, 1);
    UiSetWidgetsVisibleById_291110(o->f80, 0x26, 0, 1);
}
