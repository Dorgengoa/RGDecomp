#include "vm_slot.h"

/* Read a slot as an integer, COERCING a float operand. The truncation is the
   R5900 cvt.w.s, which is the arithmetic SplinePathStep_256970's fmod depends on
   as well -- see the note there before assuming it rounds. */

s32 ScriptGetInt_2490f0(Slot *v)
{
    if (v->type == 1) {
        return (s32)v->u.f;
    }
    return v->u.i;
}
