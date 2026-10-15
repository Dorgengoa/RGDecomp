#include "types.h"
/* insmenu 0x004F5F30 -- two calls, return 1. */
extern const u8 D_004FA1A0[];
extern void insmenu_InsectVsLoadWidgetsFade_4f6ac0(s32 a);
extern void func_28EA90(const void *a, s32 b, s32 c);
s32 insmenu_InsectVsLoadSlotListCancel_4f5f30(void)
{
    insmenu_InsectVsLoadWidgetsFade_4f6ac0(2);
    func_28EA90(D_004FA1A0, 0x88B9, 0);
    return 1;
}
