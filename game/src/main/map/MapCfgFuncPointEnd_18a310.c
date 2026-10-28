/* rgp:protos */
#define RGP_SELF_MapCfgFuncPointEnd_18a310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004812E4;
extern u8 *D_00481250;
extern u8 *D_00481254;
/*rgp*/
/*rgp*/

s32 MapCfgFuncPointEnd_18a310(void)
{
    u8 *p;
    u8 *q;
    u8 *a;

    if (D_004812E4 != 0) {
        p = D_00481254;
        if (p == 0) {
            return 0;
        }
        q = ((u8 *)ListNodeGetData_18a370(p));
        if (q == 0) {
            return 0;
        }
        a = q + 0x114;
    } else {
        a = D_00481250 + 0x1664;
    }
    FuncDataTableCalcKindFlags_18fef0(a);
    return 1;
}
