/* rgp:protos */
#define RGP_SELF_ScreenFadeBlockCtor_1c6f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_001c6f00 Obj_FUN_001c6f00;

/*rgp*/

Obj_FUN_001c6f00 *ScreenFadeBlockCtor_1c6f00(Obj_FUN_001c6f00 *o)
{
    ScreenFadeBlockInit_178490(o);
    return o;
}
