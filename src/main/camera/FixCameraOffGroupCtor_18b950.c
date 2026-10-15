#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0018b950 Obj_FUN_0018b950;

extern void FixCameraOffGroupReset_18b980(Obj_FUN_0018b950 *);

Obj_FUN_0018b950 *FixCameraOffGroupCtor_18b950(Obj_FUN_0018b950 *o)
{
    FixCameraOffGroupReset_18b980(o);
    return o;
}
