#include "types.h"

extern s16 D_004836A8 __attribute__((section(".sdata")));
extern const u8 D_004E96B0[];
extern void UiDrawWidgets_291910(const u8 *p);

void CompleteCheckMenuDraw_39e850(void)
{
    s32 v;

    v = D_004836A8;
    if (v == 0) {
        return;
    }
    if ((s16)v == 2) {
        UiDrawWidgets_291910(D_004E96B0);
    }
}
