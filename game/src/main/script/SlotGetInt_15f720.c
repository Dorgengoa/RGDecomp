/* rgp:protos */
#define RGP_SELF_SlotGetInt_15f720 1
#include "port/game_protos.h"
#line 1
#include "vm_slot.h"

/* Read a slot only if it really is an integer; anything else reads as 0.

   ⚠ The guard is spelled != , not ==, and it is not a style choice: retail's
   `beql type == 0` makes the VALUE the branch TARGET and the 0 the
   fall-through, so the source's `if` body is the 0. Written the other way
   round mwcc emits the mirror -- bnel with the 0 duplicated into the delay
   slot -- which is three of six words wrong and every one of them looks like
   register naming. Same lever as the branch-layout note for
   EventPlayerRunQueued_250c00. */

s32 SlotGetInt_15f720(Slot *v)
{
    if (v->type != 0) {
        return 0;
    }
    return v->u.i;
}
