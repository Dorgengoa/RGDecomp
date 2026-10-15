#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_003f4010 Obj_FUN_003f4010;

extern void WorldDataMgrClear_3f3f60(Obj_FUN_003f4010 *);

Obj_FUN_003f4010 *WorldDataMgrCtor_3f4010(Obj_FUN_003f4010 *o)
{
    WorldDataMgrClear_3f3f60(o);
    return o;
}
