#include "types.h"
#pragma opt_common_subs off

extern s32 MinimapSlotIsActive_322510(s32);
extern void MinimapDrawEntries_329460(s32, s32, f32);

void MinimapMgrDraw_321fa0(void *self, s32 arg1, f32 f0)
{
    s32 a;
    s32 b;

    a = *(s32 *)((u8 *)self + 0x510);
    if (a != 0 && MinimapSlotIsActive_322510(a) != 0) {
        MinimapDrawEntries_329460(*(s32 *)((u8 *)self + 0x510), arg1, f0);
    }
    b = *(s32 *)((u8 *)self + 0x514);
    if (b != 0 && MinimapSlotIsActive_322510(b) != 0) {
        MinimapDrawEntries_329460(*(s32 *)((u8 *)self + 0x514), arg1, f0);
    }
}
