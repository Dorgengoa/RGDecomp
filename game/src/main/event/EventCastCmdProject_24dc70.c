/* rgp:protos */
#define RGP_SELF_EventCastCmdProject_24dc70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* One of the event-project blob sub-parsers: does its work through a helper
   and always reports success. */

/*rgp*/

s32 EventCastCmdProject_24dc70(void *rgp_a0)
{
    SlotGetInt_15f720((void *)rgp_a0);
    return 1;
}
