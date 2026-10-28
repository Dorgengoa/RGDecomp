/* rgp:protos */
#define RGP_SELF_EvDoorObjSetClosed_303bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Reset the object and re-arm its 0x19E counter.

   The second parameter is a PASS-THROUGH: nothing in this function touches
   $a1, and EvDoorObjPlayClose_303be0 reads it as a flag (`beqz $5` at 0x00303BEC).  Caller
   EventObjMgrSetAllDoorsClosed_2e8be0 passes 1 there, so the argument is real and the prototype has
   to name it or the value would be clobbered on the way in. */

/*rgp*/

typedef struct Obj19E {
    u8 pad000[0x19E];
    s16 timer;         /* +0x19E */
} Obj19E;

void EvDoorObjSetClosed_303bb0(Obj19E *obj, s32 force)
{
    EvDoorObjPlayClose_303be0(obj, force);
    obj->timer = 0x7FFF;
}
