#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00201b70 Obj_FUN_00201b70;

extern void MapDataInit_1e7c50(Obj_FUN_00201b70 *);

Obj_FUN_00201b70 *MapDataCtor_201b70(Obj_FUN_00201b70 *o)
{
    MapDataInit_1e7c50(o);
    return o;
}
