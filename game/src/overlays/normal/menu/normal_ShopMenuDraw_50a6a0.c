/* rgp:protos */
#define RGP_SELF_normal_ShopMenuDraw_50a6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050A6A0 -- two overlay objects re-registered when the gp mode word
 * is exactly 2.  The `dsll32/dsra32 ..,16` off the plain `lh` is the recorded
 * s32-local + explicit (s16) cast shape. */
extern u8 normal_D_00527C40[];
extern u8 normal_D_00527C60[];
extern s16 D_004845E0;                /* gp - 0xB90 */
/*rgp*/

void normal_ShopMenuDraw_50a6a0(void)
{
    s32 mode = D_004845E0;

    if (mode != 0) {
        if ((s16)mode == 2) {
            UiDrawWidgets_291910(normal_D_00527C40);
            UiDrawWidgets_291910(normal_D_00527C60);
        }
    }
}
