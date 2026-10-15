#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_002578c0 Obj_FUN_002578c0;

extern void SplineInit_257860(Obj_FUN_002578c0 *);

Obj_FUN_002578c0 *SplineCtor_2578c0(Obj_FUN_002578c0 *o)
{
    SplineInit_257860(o);
    return o;
}
