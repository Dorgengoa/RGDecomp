#include "types.h"

/* One of the event-project blob sub-parsers: does its work through a helper
   and always reports success. */

extern void SlotGetInt_15f720(void);

s32 EventCastCmdProject_24dc70(void)
{
    SlotGetInt_15f720();
    return 1;
}
