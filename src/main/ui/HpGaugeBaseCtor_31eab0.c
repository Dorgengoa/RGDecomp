#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0031eab0 Obj_FUN_0031eab0;

extern void HpGaugeClearSlots_31e9c0(Obj_FUN_0031eab0 *);

Obj_FUN_0031eab0 *HpGaugeBaseCtor_31eab0(Obj_FUN_0031eab0 *o)
{
    HpGaugeClearSlots_31e9c0(o);
    return o;
}
