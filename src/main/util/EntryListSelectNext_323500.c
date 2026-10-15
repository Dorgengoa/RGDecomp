#include "types.h"

extern s32 EntryListGetCurIndex_3238b0(s32);
extern void EntryListSelectByIndex_323540(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EntryListSelectNext_323500(s32 p0)
{
    s32 r0;

    r0 = EntryListGetCurIndex_3238b0(p0);
    EntryListSelectByIndex_323540(p0, (r0 + 1));
}
