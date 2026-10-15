#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00428660 Obj_FUN_00428660;

extern void WorldSubsysClear_428650(Obj_FUN_00428660 *);

Obj_FUN_00428660 *WorldSubsysCtor_428660(Obj_FUN_00428660 *o)
{
    WorldSubsysClear_428650(o);
    return o;
}
