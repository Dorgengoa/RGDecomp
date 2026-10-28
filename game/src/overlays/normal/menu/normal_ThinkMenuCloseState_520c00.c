/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuCloseState_520c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00520C00 -- twin of normal_FUN_0050FFB0 (identical 160 B / -0x10
 * frame / guard-on-`b` / returns 1) but with THREE func_290690 calls on one
 * handle and a float-tested tail instead of a func_28EDE0 post.
 *
 * The first two calls carry -0.0625f inline (`lui 0xBD80`, low half zero); the
 * third takes the gp literal D_0047DD30.  The tail is UNGUARDED:
 * `mtc1 $0,$f1 / c.le.s $f0,$f1` with `bc1fl` PAST the two `sb $0` stores, so
 * the source test is `<= 0.0f` and the stores are the fall-through side.
 */

extern f32   D_0047DD30;          /* gp - 0x7440 */
extern void *D_00484920;          /* gp - 0x850  */
extern u8    D_00484938;          /* gp - 0x838  */
extern u8    D_00484954;          /* gp - 0x81C  */

/*rgp*/
/*rgp*/

s32 normal_ThinkMenuCloseState_520c00(void *a, s32 b)
{
    if (b != 0) {
        UiFadeWidgetAlpha_290690(D_00484920, 0x7532, 0.0f, -0.0625f, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484920, 0x7531, 0.0f, -0.0625f, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484920, 0x753D, 0.0f, D_0047DD30, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(D_00484920, 0x7532) <= 0.0f) {
        D_00484938 = 0;
        D_00484954 = 0;
    }
    return 1;
}
