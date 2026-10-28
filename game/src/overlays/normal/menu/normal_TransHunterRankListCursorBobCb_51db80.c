/* rgp:protos */
#define RGP_SELF_normal_TransHunterRankListCursorBobCb_51db80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051DB80 -- the 0x764A/0x764B gauge tick.  The `adda.s`/`madd.s`
 * pair is retail's own contraction, so that product stays INLINE; the first
 * product (8.0f * func_128FD0) is a separate mul.s/add.s and therefore has to
 * be a NAMED local ([[normal-named-product-local]]).
 */

extern void *D_00484710;          /* gp - 0xA60  */
extern f32   D_004848A8;          /* gp - 0x8C8  */
extern f32   D_004848C8;          /* gp - 0x8A8  */
extern f32   D_00480760;          /* gp - 0x4A10 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransHunterRankListCursorBobCb_51db80(s16 *p)
{
    f32 v;
    f32 r;
    f32 prod;

    D_004848A8 = D_004848A8 + 0.078539818525314331f;
    if (D_004848A8 > 0.0f) {
        D_004848A8 = D_004848A8 - 3.1415927410125732f;
    }
    prod = 8.0f * Sinf_128fd0(D_004848A8);
    UiMoveWidgetUniform_290f50(D_00484710, 0x764A, (s32)((f32)p[0] + prod), p[1] + p[9] * p[3], 0.25f, 0
);
    v = D_004848C8 + 0.10471975803375244f * D_00480760;
    D_004848C8 = v;
    if (v > 3.1415927410125732f || v < 0.0f) {
        if (v > 3.1415927410125732f) {
            D_004848C8 = 3.1415927410125732f;
        } else {
            D_004848C8 = 0.0f;
        }
        D_00480760 = D_00480760 * -1.0f;
    }
    r = 0.20000000298023224f + D_004848C8 / 3.1415927410125732f;
    if (r > 1.0f) {
        r = 1.0f;
    }
    UiSetWidgetAlpha_2907a0(D_00484710, 0x764B, r);
    normal_TransHunterPlayerRowPulse_51d780();
    return 1;
}
