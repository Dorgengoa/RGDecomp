/* rgp:protos */
#define RGP_SELF_TaskStepInsect_31a110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void TaskStepInsect_31a110(void)
{
    s32 v;

    v = InsectBattleGet_31a8d0();
    if (v != 0) {
        func_50A810(v);
        func_50C4B0(v);
        if (func_50DA40(v, 0x2B) != 0) {
            func_50A9F0(v);
        } else {
            func_50B5E0(v);
            func_50B8D0(v);
            func_50C100(v);
            func_50B6C0(v);
            func_50B630(v);
        }
    }
    InsectBattleLoadStep_319780();
}
