#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00323cc0 Obj_FUN_00323cc0;

extern void EntryReset_323c20(Obj_FUN_00323cc0 *);

Obj_FUN_00323cc0 *EntryCtor_323cc0(Obj_FUN_00323cc0 *o)
{
    EntryReset_323c20(o);
    return o;
}
