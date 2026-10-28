/* rgp:protos */
#define RGP_SELF_normal_TransWarpPreviewTexSet_51a9d0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* normal 0x0051A9D0 -- the shop price/quantity caption: formats a two-field
 * number into a 0x20-byte stack buffer, hands it to the 0x75D8 widget and
 * turns the widget on.  `v == -1` is the "no item" case: the widget is turned
 * OFF and the function returns 0.
 *
 * Three `div`s, two `break 0,7` pairs: retail was built with
 * `#pragma divbyzerocheck on`, and the pair is emitted for `/` but NOT for
 * `%` -- the `div/mfhi` at 0x0051AA28 has no check because it is the modulo
 * of the SAME divisor mwcc has already proved non-zero at 0x0051AA14. */

extern void *D_00484710;          /* gp - 0xA60 */
extern char normal_D_00526830[];

extern void Sprintf_1343b8(void *dst, const char *fmt, ...);
/*rgp*/
/*rgp*/

extern s32 normal_TransWarpPreviewTexSet_51a9d0(s32 v);

s32 normal_TransWarpPreviewTexSet_51a9d0(s32 v)
{
    char buf[0x20] __attribute__((aligned(16)));

    if (v == -1) {
        UiSetWidgetsVisibleById_291110(D_00484710, 0x75D8, 0, 1);
        return 0;
    }
    Sprintf_1343b8(buf, normal_D_00526830, v / 100, (v / 10) % 10);
    UiSetWidgetTexName_290ac0(D_00484710, 0x75D8, buf);
    UiSetWidgetsVisibleById_291110(D_00484710, 0x75D8, 1, 1);
    return 1;
}
