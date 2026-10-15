#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_002e47f0 Obj_FUN_002e47f0;

extern void EventPathSegReset_2e47d0(Obj_FUN_002e47f0 *);

Obj_FUN_002e47f0 *EventPathSegCtor_2e47f0(Obj_FUN_002e47f0 *o)
{
    EventPathSegReset_2e47d0(o);
    return o;
}
