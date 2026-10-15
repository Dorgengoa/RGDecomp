#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_003f9410 Obj_FUN_003f9410;

extern void WorldSubsysClear_3f9400(Obj_FUN_003f9410 *);

Obj_FUN_003f9410 *WorldSubsysCtor_3f9410(Obj_FUN_003f9410 *o)
{
    WorldSubsysClear_3f9400(o);
    return o;
}
