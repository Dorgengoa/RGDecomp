#include "types.h"
/* normal 0x0050A6A0 -- two overlay objects re-registered when the gp mode word
 * is exactly 2.  The `dsll32/dsra32 ..,16` off the plain `lh` is the recorded
 * s32-local + explicit (s16) cast shape. */
extern const u8 D_00527C40[];
extern const u8 D_00527C60[];
extern s16 D_004845E0;                /* gp - 0xB90 */
extern void func_291910(const void *p);

void normal_ShopMenuDraw_50a6a0(void)
{
    s32 mode = D_004845E0;

    if (mode != 0) {
        if ((s16)mode == 2) {
            func_291910(D_00527C40);
            func_291910(D_00527C60);
        }
    }
}
