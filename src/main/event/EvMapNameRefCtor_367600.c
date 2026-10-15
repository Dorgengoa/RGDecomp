#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00367600 Obj_FUN_00367600;

extern void EvMapNameRefReset_3675f0(Obj_FUN_00367600 *);

Obj_FUN_00367600 *EvMapNameRefCtor_367600(Obj_FUN_00367600 *o)
{
    EvMapNameRefReset_3675f0(o);
    return o;
}
