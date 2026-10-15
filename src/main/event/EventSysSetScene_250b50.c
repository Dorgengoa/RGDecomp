#include "types.h"

extern void EventSysInit_26b460(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F78;

void EventSysSetScene_250b50(s32 p0)
{
    D_00481F78 = p0;
    EventSysInit_26b460();
}
