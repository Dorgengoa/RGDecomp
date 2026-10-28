/* rgp:protos */
#define RGP_SELF_normal_HelpMenuDraw_522f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00522F80 -- byte-for-byte twin of normal_FUN_005242D0.  The
 * dsll32/dsra32 pair off the plain `lh` is the s32-local + explicit (s16)
 * cast shape, not an s16 local. */

extern s16 D_004849C0;            /* gp - 0x7B0 */

extern u8 normal_D_00528180[];
extern u8 normal_D_005281A0[];

/*rgp*/

void normal_HelpMenuDraw_522f80(void)
{
    s32 st = D_004849C0;

    if (st != 0) {
        if ((s16)st == 2) {
            UiDrawWidgets_291910(normal_D_00528180);
            UiDrawWidgets_291910(normal_D_005281A0);
        }
    }
}
