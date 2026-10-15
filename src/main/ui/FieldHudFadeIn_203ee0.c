#include "types.h"

extern void func_4F6F00(const u8 *);
extern void func_506D50(const u8 *, f32, f32);
extern void func_4F11D0(const u8 *, f32, f32);
extern void func_4F08A0(const u8 *);
extern const u8 D_004BC250[];
extern const u8 D_00527020[];

void FieldHudFadeIn_203ee0(void)
{
    func_4F6F00(D_00527020);
    func_506D50(D_004BC250, 1.0f, 10.0f);
    func_4F11D0(D_00527020, 1.0f, 10.0f);
    func_4F08A0(D_00527020);
}
