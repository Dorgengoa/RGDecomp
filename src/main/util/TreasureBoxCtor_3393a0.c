#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_003393a0 Obj_FUN_003393a0;

extern void TreasureBoxReset_33b4c0(Obj_FUN_003393a0 *);

Obj_FUN_003393a0 *TreasureBoxCtor_3393a0(Obj_FUN_003393a0 *o)
{
    TreasureBoxReset_33b4c0(o);
    return o;
}
