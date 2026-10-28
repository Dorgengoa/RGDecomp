/* rgp:protos */
#define RGP_SELF_ScriptGetCodeAddr_249050 1
#include "port/game_protos.h"
#line 1
#include "vm_slot.h"

/* Read a code address out of a slot; anything else reads as null. */

s32 ScriptGetCodeAddr_249050(Slot *v)
{
    if (v->type == 2) {
        return v->u.i;
    }
    return 0;
}
