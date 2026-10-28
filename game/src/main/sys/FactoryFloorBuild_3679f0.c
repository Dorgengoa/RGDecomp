/* rgp:protos */
#define RGP_SELF_FactoryFloorBuild_3679f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_003679f0 Obj_FUN_003679f0;

/*rgp*/
/*rgp*/

void FactoryFloorBuild_3679f0(Obj_FUN_003679f0 *o)
{
    Obj_FUN_003679f0 *r;

    r = ((Obj_FUN_003679f0 *)GetFactoryObj_367f30());
    if (r != 0) {
        func_503910(r, o);
    }
}
