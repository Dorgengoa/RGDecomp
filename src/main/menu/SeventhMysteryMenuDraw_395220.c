#include "types.h"

extern s16 D_00483488 __attribute__((section(".sdata")));
extern const u8 D_004E9550[];
extern void UiDrawWidgets_291910(const u8 *p);

void SeventhMysteryMenuDraw_395220(void)
{
    s32 v;

    v = D_00483488;
    if (v == 0) {
        return;
    }
    if ((s16)v == 2) {
        UiDrawWidgets_291910(D_004E9550);
    }
}
