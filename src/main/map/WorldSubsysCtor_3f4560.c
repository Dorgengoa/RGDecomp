#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_003f4560 Obj_FUN_003f4560;

extern void WorldSubsysClear_3f4550(Obj_FUN_003f4560 *);

Obj_FUN_003f4560 *WorldSubsysCtor_3f4560(Obj_FUN_003f4560 *o)
{
    WorldSubsysClear_3f4550(o);
    return o;
}
