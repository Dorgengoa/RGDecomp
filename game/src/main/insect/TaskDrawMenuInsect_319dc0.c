/* rgp:protos */
#define RGP_SELF_TaskDrawMenuInsect_319dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00319dc0 Obj_FUN_00319dc0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void TaskDrawMenuInsect_319dc0(void)
{
    Obj_FUN_00319dc0 *o;

    o = ((Obj_FUN_00319dc0 *)InsectBattleGet_31a8d0());
    if (o == 0) {
        return;
    }
    func_50A530(o);
    func_50A460(o);
    if (func_50DA40(o, 0x1D) != 0) {
        func_4F5FC0(o, 1);
    }
    if (func_50DA40(o, 0x1C) != 0) {
        func_4F5FC0(o, 0);
    }
}
