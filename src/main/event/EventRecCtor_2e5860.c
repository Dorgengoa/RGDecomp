#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_002e5860 Obj_FUN_002e5860;

extern void EventRecReset_2e5840(Obj_FUN_002e5860 *);

Obj_FUN_002e5860 *EventRecCtor_2e5860(Obj_FUN_002e5860 *o)
{
    EventRecReset_2e5840(o);
    return o;
}
