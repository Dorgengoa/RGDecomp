#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0015ae50 Obj_FUN_0015ae50;

extern void NameTableNodeReset_15ada0(Obj_FUN_0015ae50 *);

Obj_FUN_0015ae50 *NameTableNodeCtor_15ae50(Obj_FUN_0015ae50 *o)
{
    NameTableNodeReset_15ada0(o);
    return o;
}
