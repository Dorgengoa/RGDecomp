#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_001ef430 Obj_FUN_001ef430;

extern void MotionEventListClear_1b4aa0(Obj_FUN_001ef430 *);

Obj_FUN_001ef430 *MotionEventListCtor_1ef430(Obj_FUN_001ef430 *o)
{
    MotionEventListClear_1b4aa0(o);
    return o;
}
