#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0041c830 Obj_FUN_0041c830;

extern void WorldSubsysClear_41c820(Obj_FUN_0041c830 *);

Obj_FUN_0041c830 *WorldSubsysCtor_41c830(Obj_FUN_0041c830 *o)
{
    WorldSubsysClear_41c820(o);
    return o;
}
