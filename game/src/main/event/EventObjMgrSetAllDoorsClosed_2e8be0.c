/* rgp:protos */
#define RGP_SELF_EventObjMgrSetAllDoorsClosed_2e8be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Drain a list, then two teardowns. The iterator ADVANCES BEFORE it uses the
   node: DListGetNext_42eb30 is called on the current entry and its result becomes
   the next one, while the payload pointer (entry + 0x10) is computed in that
   call's delay slot and only handed to EvDoorObjSetClosed_303bb0 afterwards. That order is
   what lets the loop body destroy the entry it is standing on. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EventObjMgrSetAllDoorsClosed_2e8be0(void *self)
{
    void *entry;
    void *payload;

    entry = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(self, 9));
    while (entry != 0) {
        payload = (u8 *)entry + 0x10;
        entry = DListGetNext_42eb30(entry);
        EvDoorObjSetClosed_303bb0(payload, 1);
    }
    EventObjMgrPreUpdateAllMaybe_2e8440(self);
    EventObjMgrUpdateAll_2e8290(self);
}
