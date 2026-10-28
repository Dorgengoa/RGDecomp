/* rgp:protos */
#define RGP_SELF_normal_InsectEntryRankCursorBob_523600 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00523600 -- the phase-advance / func_290F50 readout family; the
 * matched normal_FUN_004FCF10 is the template.  The two gp floats at
 * -0x7DA0 / -0x7F74 are MAIN's `.lit4` POOL, not variables: they are written
 * as the literals 0.1570796371f and 3.14159274f and the link retargets them.
 * Score with build/wf-normal/mg/mg_score.py -- plain dv_osbuild.py reads the
 * unresolved `@N` GPREL field as a bad word. */

typedef struct Rec {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[0x10 - 8];
    s16 f10;
    s16 f12;
} Rec;

extern f32 D_004849C8;            /* gp - 0x7A8 */
extern u8  normal_D_00528180[];

/*rgp*/
/*rgp*/

s32 normal_InsectEntryRankCursorBob_523600(Rec *r, s32 unused, s32 x, s32 y)
{
    f32 t;

    D_004849C8 += 0.1570796371f;
    if (D_004849C8 > 0.0f) {
        D_004849C8 -= 3.14159274f;
    }
    t = 6.0f * Sinf_128fd0(D_004849C8);
    UiMoveWidgetUniform_290f50(normal_D_00528180, 0x10, (s32)((f32)x + (t + (f32)(r->f00 + r->f10 * r->f04))), y + (r->f02 + r->f12 * r->f06), 0.5f, 0

);
    return 1;
}
