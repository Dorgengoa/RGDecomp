#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0031d1c0 Obj_FUN_0031d1c0;

extern void HpGaugeCtor_31e2a0(Obj_FUN_0031d1c0 *);

Obj_FUN_0031d1c0 *HpGaugeObjCtor_31d1c0(Obj_FUN_0031d1c0 *o)
{
    HpGaugeCtor_31e2a0(o);
    return o;
}
