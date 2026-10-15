#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_003fc420 Obj_FUN_003fc420;

extern void WorldSubsysClear_3fc410(Obj_FUN_003fc420 *);

Obj_FUN_003fc420 *WorldSubsysCtor_3fc420(Obj_FUN_003fc420 *o)
{
    WorldSubsysClear_3fc410(o);
    return o;
}
