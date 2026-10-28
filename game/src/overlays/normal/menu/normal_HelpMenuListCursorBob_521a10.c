/* rgp:protos */
#define RGP_SELF_normal_HelpMenuListCursorBob_521a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00521A10 -- advance the shared phase, wrap it by pi, and place the
 * widget at the box's corner plus its scaled extent.  `6.0f * sinf(phase)` is
 * a NAMED local (used in the one big sum but written once), and the two
 * s16 products are the `mult` / `mult1` pipeline pair.  Both floats are
 * mwcc .lit4 POOL ENTRIES and are spelled as LITERALS. */

typedef struct Box {
    s16 f00; s16 f02; s16 f04; s16 f06;
    u8  pad08[0x10 - 0x08];
    s16 f10; s16 f12;
} Box;

extern f32 D_004849C8;            /* gp - 0x7A8 */

extern u8 normal_D_00528180[];

/*rgp*/
/*rgp*/

s32 normal_HelpMenuListCursorBob_521a10(Box *p, void *b, s32 c, s32 d)
{
    f32 s;

    D_004849C8 += 0.1570796371f;
    if (D_004849C8 > 0.0f) {
        D_004849C8 -= 3.141592741f;
    }
    s = 6.0f * Sinf_128fd0(D_004849C8);
    UiMoveWidgetUniform_290f50(normal_D_00528180, 0x2C, (s32)((f32)c + (s + (f32)(p->f00 + p->f10 * p->f04))), d + (p->f02 + p->f12 * p->f06), 0.5f, 0

);
    return 1;
}
