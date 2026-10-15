#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_002e79c0 Obj_FUN_002e79c0;

extern void XformInitIdentity_2e7970(Obj_FUN_002e79c0 *);

Obj_FUN_002e79c0 *XformCtor_2e79c0(Obj_FUN_002e79c0 *o)
{
    XformInitIdentity_2e7970(o);
    return o;
}
