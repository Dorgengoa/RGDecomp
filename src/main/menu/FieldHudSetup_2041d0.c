#include "types.h"

extern const u8 D_00527020[];
extern const u8 D_004BC250[];
extern const u8 D_004BBC80[];
extern void func_4F79E0(const u8 *p);
extern void func_506EF0(const u8 *p);
extern void func_506FC0(void);
extern void MenuBattleStackInit_206820(void);
extern void MenuBattleIconStackInit_206710(void);
extern void BattleCmdResRequest_204f70(void);
extern void func_4F71A0(const u8 *p, const u8 *q);
extern void func_4F4790(const u8 *p);
extern void func_4F2A20(const u8 *p, const u8 *q);

void FieldHudSetup_2041d0(void)
{
    func_4F79E0(D_00527020);
    func_506EF0(D_004BC250);
    func_506FC0();
    MenuBattleStackInit_206820();
    MenuBattleIconStackInit_206710();
    BattleCmdResRequest_204f70();
    func_4F71A0(D_00527020, D_004BBC80);
    func_4F4790(D_00527020);
    func_4F2A20(D_00527020, D_004BBC80);
}
