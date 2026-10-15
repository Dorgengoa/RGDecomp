#include "types.h"

/* title.bin overlay, 0x004EE8C0 -- two calls, one to a sibling overlay
 * function and one into main, then return 1.
 */

extern void *D_004841E8;
extern void title_TitleLoadFadeWidgets_4eda30(s32 a);
extern void func_28EA90(void *a, s32 b, s32 c);

s32 title_TitleLoadSlotListCancel_4ee8c0(void)
{
    title_TitleLoadFadeWidgets_4eda30(2);
    func_28EA90(D_004841E8, 0x7532, 0);
    return 1;
}
