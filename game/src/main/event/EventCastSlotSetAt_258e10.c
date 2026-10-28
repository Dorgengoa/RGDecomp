/* rgp:protos */
#define RGP_SELF_EventCastSlotSetAt_258e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Ent {
    u8 pad000[0x10];
};

/*rgp*/

/* Two tests branching in OPPOSITE directions around the shared `return 0`
   block: that is an ||. */
s32 EventCastSlotSetAt_258e10(struct Ent *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    if (p1 < 0 || p1 >= 0x20) {
        return 0;
    }
    return EventCastSlotSet_258ee0(&p0[p1], p2, p3, p4);
}
