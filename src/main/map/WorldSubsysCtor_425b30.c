#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00425b30 Obj_FUN_00425b30;

extern void WorldSubsysClear_425b20(Obj_FUN_00425b30 *);

Obj_FUN_00425b30 *WorldSubsysCtor_425b30(Obj_FUN_00425b30 *o)
{
    WorldSubsysClear_425b20(o);
    return o;
}
