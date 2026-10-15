#include "types.h"

extern const u8 D_00527020[];
extern const u8 D_004BC250[];
extern void func_4F6ED0(const u8 *p);
extern void func_506B70(const u8 *p, s32 n);
extern void func_4F1940(const u8 *p);
extern void BtlChgMenuCloseThunk_4f9d70(void);

void FieldHudHideAll_203e20(void)
{
    func_4F6ED0(D_00527020);
    func_506B70(D_004BC250, 0x59DC);
    func_4F1940(D_00527020);
    BtlChgMenuCloseThunk_4f9d70();
}
