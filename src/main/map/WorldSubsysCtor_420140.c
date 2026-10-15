#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00420140 Obj_FUN_00420140;

extern void WorldSubsysClear_420130(Obj_FUN_00420140 *);

Obj_FUN_00420140 *WorldSubsysCtor_420140(Obj_FUN_00420140 *o)
{
    WorldSubsysClear_420130(o);
    return o;
}
