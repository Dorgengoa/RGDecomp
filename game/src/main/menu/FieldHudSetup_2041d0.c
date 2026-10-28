/* rgp:protos */
#define RGP_SELF_FieldHudSetup_2041d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00527020[];
extern u8 D_004BC250[];
extern u8 D_004BBC80[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
