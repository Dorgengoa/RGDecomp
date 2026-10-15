#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_002d1c60 Obj_FUN_002d1c60;

extern void UskMemoryRefInit_42d030(Obj_FUN_002d1c60 *);

Obj_FUN_002d1c60 *NavMgrCtor_2d1c60(Obj_FUN_002d1c60 *o)
{
    UskMemoryRefInit_42d030(o);
    return o;
}
