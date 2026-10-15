#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_004127d0 Obj_FUN_004127d0;

extern void WorldSubsysClear_412770(Obj_FUN_004127d0 *);

Obj_FUN_004127d0 *WorldSubsysCtor_4127d0(Obj_FUN_004127d0 *o)
{
    WorldSubsysClear_412770(o);
    return o;
}
