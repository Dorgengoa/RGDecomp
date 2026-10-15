#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0028aa00 Obj_FUN_0028aa00;

extern void MsgFormatParamsClear_28a9f0(Obj_FUN_0028aa00 *);

Obj_FUN_0028aa00 *MsgFormatParamsCtor_28aa00(Obj_FUN_0028aa00 *o)
{
    MsgFormatParamsClear_28a9f0(o);
    return o;
}
