/* rgp:protos */
#define RGP_SELF_EventSoundTableCtor_2614c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Runs EventSoundTableReset_249e60 over the object and hands the same object back -- the
   argument is held in $16 across the call purely so it can be returned, which
   is why a function this small needs a frame at all. */

/*rgp*/

void *EventSoundTableCtor_2614c0(void *self)
{
    EventSoundTableReset_249e60(self);
    return self;
}
