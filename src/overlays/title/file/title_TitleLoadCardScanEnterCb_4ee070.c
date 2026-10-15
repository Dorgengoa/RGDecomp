#include "types.h"

/* title.bin overlay, 0x004EE070 -- a straight run of six calls with constant
 * arguments and one byte store that rides in a call's delay slot.
 */

extern u8 D_0048421C;
extern void func_37B460(s32 a);
extern void func_37B800(s32 a);
extern void func_37B9E0(s32 a);
extern void title_TitleLoadSlotListRefreshMaybe_4edeb0(s16 a);
extern void title_TitleLoadShowMsg_4eeb60(s32 a);
extern void title_TitleSetNoAnalogPause_4f13b0(s32 a);

s32 title_TitleLoadCardScanEnterCb_4ee070(void)
{
    func_37B460(0x43);
    func_37B800(-1);
    title_TitleLoadSlotListRefreshMaybe_4edeb0(0);
    D_0048421C = 0;
    func_37B9E0(0);
    title_TitleLoadShowMsg_4eeb60(3);
    title_TitleSetNoAnalogPause_4f13b0(1);
    return 1;
}
