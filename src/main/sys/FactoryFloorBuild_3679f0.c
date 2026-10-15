#include "types.h"

typedef struct Obj_FUN_003679f0 Obj_FUN_003679f0;

extern Obj_FUN_003679f0 *GetFactoryObj_367f30(Obj_FUN_003679f0 *o);
extern void func_503910(Obj_FUN_003679f0 *a, Obj_FUN_003679f0 *b);

void FactoryFloorBuild_3679f0(Obj_FUN_003679f0 *o)
{
    Obj_FUN_003679f0 *r;

    r = GetFactoryObj_367f30(o);
    if (r != 0) {
        func_503910(r, o);
    }
}
