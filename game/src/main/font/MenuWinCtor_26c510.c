/* rgp:protos */
#define RGP_SELF_MenuWinCtor_26c510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0026c510 Obj_FUN_0026c510;

/*rgp*/

Obj_FUN_0026c510 *MenuWinCtor_26c510(Obj_FUN_0026c510 *o)
{
    MenuWinInit_26c450(o);
    return o;
}
