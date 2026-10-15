#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_003ff5c0 Obj_FUN_003ff5c0;

extern void WorldSubsysClear_3ff5a0(Obj_FUN_003ff5c0 *);

Obj_FUN_003ff5c0 *WorldSubsysCtor_3ff5c0(Obj_FUN_003ff5c0 *o)
{
    WorldSubsysClear_3ff5a0(o);
    return o;
}
