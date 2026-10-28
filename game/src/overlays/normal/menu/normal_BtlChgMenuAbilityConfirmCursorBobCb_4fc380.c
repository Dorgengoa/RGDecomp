/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuAbilityConfirmCursorBobCb_4fc380 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FC380 -- MATCH (session 32, lane nc32k).  The phase-advance /
 * func_290F50 readout family.  The two gp floats at -0x7DA0 / -0x7F74 are
 * mwcc's `.lit4` POOL, not variables: written as the literals 0.1570796371f
 * and 3.14159274f, and the link retargets them.  Score with
 * build/wf-normal/s32/nscore.py -- dv_osbuild.py reads the unresolved `@N`
 * GPREL field as a bad word.
 *
 * THE LEVER (s21-s32 residue was a 5-word ROTATION of the prologue: retail
 * issues the global's `lwc1 $f2,-0xC78($28)` FIRST, above `sd $31`; every
 * plain-extern spelling issues it LAST).  A load of a PLAIN gp extern may
 * alias the prologue's stack stores, so mwcc pins it below `sd $31`/`sq $16`.
 * Declaring the object `const` with an explicit `section(".sdata")` puts it in
 * the "modifies nothing" alias class (the same lever that closed
 * factory_FactoryCameraUpdate_5050c0), so the load hoists into the prologue exactly as
 * retail schedules it; the stores then go through a cast.  Plain `extern
 * const` without the section attribute is lui-addressed and costs 5 words.
 * The FIRST read is volatile-pinned so it is created before the .lit4
 * constant (otherwise the two lwc1 swap slots), and the constant is added
 * with a COMPOUND assign on the local, which is what puts the global in the
 * add's `fs` field (`add.s $f1,$f2,$f1`); `dd + K` and `K + dd` are one
 * object and both leave `add.s $f1,$f1,$f2`.
 * MEASURED: 1,134 arms this session -- 34 statement/operand spellings, 493 +
 * 503 pragma arms (all 243 mwcc pragma names x on/off, twice, at two
 * baselines: the scheduler-knob axis is a null here), 30 alias/const/volatile
 * spellings, 52 const-section x read-site x seed spellings. */
typedef struct Rec {
    u8  pad000[0x10];
    s16 f10;
} Rec;

extern f32 D_004844F8 __attribute__((section(".sdata")));   /* gp - 0xC78 */
extern void *D_0048449C;                                          /* gp - 0xCD4 */

/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuAbilityConfirmCursorBobCb_4fc380(Rec *r)
{
    s16 v;
    f32 t;
    f32 dd;

    v = r->f10;
    dd = (*(volatile f32*)&D_004844F8);
    dd += 0.1570796371f;
    (*(f32*)&D_004844F8) = dd;
    if ((*(f32*)&D_004844F8) > 0.0f) {
        (*(f32*)&D_004844F8) = (*(f32*)&D_004844F8) - 3.14159274f;
    }
    t = 12.0f * Sinf_128fd0((*(f32*)&D_004844F8));
    UiMoveWidgetUniform_290f50(D_0048449C, 0x48, (s32)(t + (f32)(v * 95 + 131)), 0x38, 0.5f, 0
);
    return 1;
}
