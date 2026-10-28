/* rgp:protos */
#define RGP_SELF_normal_TransHunterBountyListCursorBobCb_51f2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051F2B0 -- per-frame swing driver.  The float pool entries at
 * gp-0x7DB8 / gp-0x7F74 / gp-0x7D74 / gp-0x7F30 are .lit4 entries and must be
 * written as literals; the mul.s/add.s pair (not madd.s) plus the plain
 * cvt.w.s says the 8.0f product is NAMED in a local. */

typedef struct Box {
    s16 f00; s16 f02; s16 f04; s16 f06;
    u8  pad08[8];
    s16 f10; s16 f12;
} Box;

extern void *D_00484710;          /* gp - 0xA60  */
extern f32   D_004848A8;          /* gp - 0x8C8  */
extern f32   D_004848C8;          /* gp - 0x8A8  */
extern f32   D_00480760;          /* gp - 0x4A10 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransHunterBountyListCursorBobCb_51f2b0(Box *p)
{
    f32 prod;
    f32 t;

    D_004848A8 = D_004848A8 + 0.078539819f;
    if (D_004848A8 > 0.0f) {
        D_004848A8 = D_004848A8 - 3.14159274f;
    }
    prod = 8.0f * Sinf_128fd0(D_004848A8);
    UiMoveWidgetUniform_290f50(D_00484710, 0x764D, (s32)(prod + (f32)(p->f00 + p->f10 * p->f04)), p->f02 + p->f12 * p->f06, 0.25f, 0

);

    D_004848C8 = D_004848C8 + 0.104719758f * D_00480760;
    if (D_004848C8 > 3.14159274f || D_004848C8 < 0.0f) {
        if (D_004848C8 > 3.14159274f) {
            D_004848C8 = 3.14159274f;
        } else {
            D_004848C8 = 0.0f;
        }
        D_00480760 = D_00480760 * -1.0f;
    }
    t = 0.2f + D_004848C8 / 3.14159274f;
    if (t > 1.0f) {
        t = 1.0f;
    }
    UiSetWidgetAlpha_2907a0(D_00484710, 0x764B, t);
    return 1;
}
