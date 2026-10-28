/* rgp:protos */
#define RGP_SELF_ScriptSlotGetInt_2cc9c0 1
#include "port/game_protos.h"
#line 1
#include "vm_slot.h"

/* Known-positive sibling shape of ScriptGetInt_2490f0 (byte-identical, in cunits):
   read a slot as an integer, COERCING a float operand. */

s32 ScriptSlotGetInt_2cc9c0(Slot *v)
{
    if (v->type == 1) {
        return (s32)v->u.f;
    }
    return v->u.i;
}
