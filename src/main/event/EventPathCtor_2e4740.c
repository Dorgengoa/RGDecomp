#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_002e4740 Obj_FUN_002e4740;

extern void EventPathClear_2e4720(Obj_FUN_002e4740 *);

Obj_FUN_002e4740 *EventPathCtor_2e4740(Obj_FUN_002e4740 *o)
{
    EventPathClear_2e4720(o);
    return o;
}
