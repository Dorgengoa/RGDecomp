/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintClearChosen_4faf10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FAF10 -- 49 words, BYTE-IDENTICAL.
 *
 * SOLVED 2026-08-31: 0x0047D4E4 is NOT a global, it is an entry in MAIN's
 * `.lit4` FLOAT LITERAL POOL (word 0x3E23D70B = 0.1600000113).  Spelling it as
 * `extern f32 D_0047D4E4` pins the `lwc1` at its use (mwcc must order a global
 * load against the surrounding stores); spelling it as a LITERAL makes it a
 * known constant with no alias hazard, and it hoists into the prologue slot
 * between `sd $31` and `sq $16` -- which is retail's schedule.  That single
 * spelling is the whole four-word "gp-float prologue rotation" residue that
 * the 17-cell sweep recorded here previously could not move, because every one
 * of those 17 cells held the EXTERN spelling fixed.
 * See levers.d/mwcc-float-literal-pool.md and build/lit4_im07.py.
 *
 * !! `0.16f` is the WRONG literal: mwcc rounds it to 0x3E23D70A, one ULP below
 * retail's pool word.  0.1600000113f / 0.16000001f both give 0x3E23D70B.
 *
 * !! Scoring: plain dv_osbuild reports 2 bad words (the two gp immediates read
 * as C78C0000) because the scorer cannot place the object's own `.lit4`.
 * With the pool retarget (build/lit4_im07.py, both sites -> 0x0047D4E4) it is
 * 0 bad.  factory's olink already performs that retarget.
 */

typedef struct Job { u8 pad00[0x10]; s32 f10; } Job;

typedef struct Scr {
    u8    pad00[0x70];
    s32   f70;
    s32   f74;
    s16   f78;
    s16   f7A;
    u8    pad7C[0x4];
    void *f80;
} Scr;


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintClearChosen_4faf10(Scr *o)
{
    UiMoveWidgetUniform_290f50(o->f80, 0x91, 0x200, 0x191, 0.1600000113f, 0);
    UiFadeWidgetAlpha_290690(o->f80, 0x91, 0.0f, -0.125f, -1.0f);
    UiMoveWidgetUniform_290f50(o->f80, 0x29, 0xEB, 0, 0.1600000113f, 0);
    UiFadeWidgetAlpha_290690(o->f80, 0x29, 0.0f, -0.125f, -1.0f);
    UiSetWidgetsVisibleById_291110(o->f80, 0x23, 0, 1);
    o->f70 = 0;
    o->f74 = 0;
    o->f78 = 0;
    o->f7A = 0;
    ((Job *)FactoryGetRequestPtr_367ec0())->f10 = 0;
}
