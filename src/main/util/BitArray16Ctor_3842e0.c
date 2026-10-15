#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_003842e0 Obj_FUN_003842e0;

extern void BitArray16Clear_384310(Obj_FUN_003842e0 *);

Obj_FUN_003842e0 *BitArray16Ctor_3842e0(Obj_FUN_003842e0 *o)
{
    BitArray16Clear_384310(o);
    return o;
}
