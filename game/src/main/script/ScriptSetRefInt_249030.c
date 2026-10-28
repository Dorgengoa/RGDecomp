/* rgp:protos */
#define RGP_SELF_ScriptSetRefInt_249030 1
#include "port/game_protos.h"
#line 1
#include "vm_slot.h"

/* Write an integer back through a slot the script passed BY REFERENCE.
   Every event command that returns a value to the script goes through this --
   EvCmdEventGetTick_248fe0 is the matched example. A slot that is not a reference is
   dropped silently. */

void ScriptSetRefInt_249030(Slot *v, s32 x)
{
    if (v->type == 3) {
        ((Slot *)v->u.p)->u.i = x;
    }
}
