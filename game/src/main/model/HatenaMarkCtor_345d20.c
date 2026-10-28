/* rgp:protos */
#define RGP_SELF_HatenaMarkCtor_345d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00345d20 Obj_FUN_00345d20;

/*rgp*/

Obj_FUN_00345d20 *HatenaMarkCtor_345d20(Obj_FUN_00345d20 *o)
{
    HatenaMarkReset_345bd0(o);
    return o;
}
