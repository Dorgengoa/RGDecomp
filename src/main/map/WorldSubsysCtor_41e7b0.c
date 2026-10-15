#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0041e7b0 Obj_FUN_0041e7b0;

extern void WorldSubsysClear_41e7a0(Obj_FUN_0041e7b0 *);

Obj_FUN_0041e7b0 *WorldSubsysCtor_41e7b0(Obj_FUN_0041e7b0 *o)
{
    WorldSubsysClear_41e7a0(o);
    return o;
}
