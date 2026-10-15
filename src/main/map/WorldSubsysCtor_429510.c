#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00429510 Obj_FUN_00429510;

extern void WorldSubsysClear_429500(Obj_FUN_00429510 *);

Obj_FUN_00429510 *WorldSubsysCtor_429510(Obj_FUN_00429510 *o)
{
    WorldSubsysClear_429500(o);
    return o;
}
