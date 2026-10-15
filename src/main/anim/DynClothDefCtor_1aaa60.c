#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_001aaa60 Obj_FUN_001aaa60;

extern void DynClothDefInit_169420(Obj_FUN_001aaa60 *);

Obj_FUN_001aaa60 *DynClothDefCtor_1aaa60(Obj_FUN_001aaa60 *o)
{
    DynClothDefInit_169420(o);
    return o;
}
