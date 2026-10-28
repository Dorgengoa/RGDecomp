/* rgp:protos */
#define RGP_SELF_MapCfgPartsEnd_18bec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_0018bec0 Obj_FUN_0018bec0;

extern Obj_FUN_0018bec0 *D_00481254;
extern s32 D_004812E4;
/*rgp*/
/*rgp*/

s32 MapCfgPartsEnd_18bec0(void)
{
    Obj_FUN_0018bec0 *p;
    Obj_FUN_0018bec0 *q;

    p = D_00481254;
    if (p == 0) {
        return 0;
    }
    D_004812E4 = 0;
    q = ((Obj_FUN_0018bec0 *)ListNodeGetData_18a370(p));
    if (q == 0) {
        return 0;
    }
    NodeObjCalcBounds_194500(q);
    D_00481254 = 0;
    return 1;
}
