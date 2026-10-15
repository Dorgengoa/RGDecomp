#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0031a4f0 Obj_FUN_0031a4f0;

extern void MemStackCtor_14e030(Obj_FUN_0031a4f0 *);

Obj_FUN_0031a4f0 *InsectAbilityTableCtor_31a4f0(Obj_FUN_0031a4f0 *o)
{
    MemStackCtor_14e030(o);
    return o;
}
