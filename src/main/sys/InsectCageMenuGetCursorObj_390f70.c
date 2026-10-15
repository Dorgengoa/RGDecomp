#include "types.h"

extern s32 D_004E94A0[];
extern s32 InsectCageMenuGetCursorSlot_391000(void);

s32 InsectCageMenuGetCursorObj_390f70(void)
{
    s32 r = InsectCageMenuGetCursorSlot_391000();
    if (r < 0) goto zero;
    if (r < 5) goto ok;
zero:
    return 0;
ok:
    return D_004E94A0[r];
}
