#include "types.h"

typedef struct Obj_FUN_0018bec0 Obj_FUN_0018bec0;

extern Obj_FUN_0018bec0 *D_00481254;
extern s32 D_004812E4;
extern Obj_FUN_0018bec0 *ListNodeGetData_18a370(Obj_FUN_0018bec0 *p);
extern void NodeObjCalcBounds_194500(Obj_FUN_0018bec0 *p);

s32 MapCfgPartsEnd_18bec0(void)
{
    Obj_FUN_0018bec0 *p;
    Obj_FUN_0018bec0 *q;

    p = D_00481254;
    if (p == 0) {
        return 0;
    }
    D_004812E4 = 0;
    q = ListNodeGetData_18a370(p);
    if (q == 0) {
        return 0;
    }
    NodeObjCalcBounds_194500(q);
    D_00481254 = 0;
    return 1;
}
