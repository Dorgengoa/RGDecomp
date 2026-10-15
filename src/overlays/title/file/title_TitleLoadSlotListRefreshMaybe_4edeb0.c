#include "types.h"

/* title.bin overlay, 0x004EDEB0 -- tail call into main: func_3783C0(o, 1) */

extern void func_3783C0(s16 a, s32 b);

void title_TitleLoadSlotListRefreshMaybe_4edeb0(s16 a)
{
    func_3783C0(a, 1);
}
