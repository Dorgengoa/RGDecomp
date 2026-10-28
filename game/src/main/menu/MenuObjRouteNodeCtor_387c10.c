/* rgp:protos */
#define RGP_SELF_MenuObjRouteNodeCtor_387c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00387c10 Obj_FUN_00387c10;

/*rgp*/

Obj_FUN_00387c10 *MenuObjRouteNodeCtor_387c10(Obj_FUN_00387c10 *o)
{
    PlacePointInit_3869f0(o);
    return o;
}
