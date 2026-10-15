#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_002d9060 Obj_FUN_002d9060;

extern void MovingLineInit_2d5f40(Obj_FUN_002d9060 *);

Obj_FUN_002d9060 *MovingLineCtor_2d9060(Obj_FUN_002d9060 *o)
{
    MovingLineInit_2d5f40(o);
    return o;
}
