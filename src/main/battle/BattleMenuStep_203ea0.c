#include "types.h"

extern const u8 D_00527020[];
extern const u8 D_004BC250[];
extern void func_4F7D00(const u8 *p);
extern void func_4F56D0(const u8 *p);
extern void func_506C10(const u8 *p);

void BattleMenuStep_203ea0(void)
{
    func_4F7D00(D_00527020);
    func_4F56D0(D_00527020);
    func_506C10(D_004BC250);
}
