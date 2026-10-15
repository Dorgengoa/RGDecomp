#include "types.h"

/* Stack locals are allocated in REVERSE declaration order: x1@0x3C ..
   y2@0x30, so declare x1,y1,x2,y2. */

extern void *UiPageGetLayout_289b60(void *a);
extern void  UiGetWidgetPos_2910a0(void *h, void *b, s32 *x, s32 *y);
extern void  UiGetWidgetTargetPos_290d90(void *h, void *b, s32 *x, s32 *y);

s32 UiPageWidgetAtTargetPos_2899b0(void *a, void *b)
{
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    void *h;

    h = UiPageGetLayout_289b60(a);
    if (h == 0) {
        return 0;
    }
    UiGetWidgetPos_2910a0(h, b, &x1, &y1);
    UiGetWidgetTargetPos_290d90(h, b, &x2, &y2);
    if (x1 == x2 && y1 == y2) {
        return 1;
    }
    return 0;
}
