#include "types.h"

extern s32 ListNodeFindLast_18e17c(void);
extern void ListNodeLinkNext_18e140(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ListLinkAtTail_18e110(s32 p0, s32 p1)
{
    s32 r0;

    r0 = ListNodeFindLast_18e17c();
    ListNodeLinkNext_18e140(r0, p1);
}
