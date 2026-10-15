#include "types.h"

extern void EventObjMgrResetThunk_2ea280(void *);
extern void NavMgrRelease_30da20(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DCB10[];
extern u8 D_004DCCC0[];

void EventObjDataReset_2d1170(void)
{
    EventObjMgrResetThunk_2ea280(D_004DCB10);
    NavMgrRelease_30da20(D_004DCCC0);
}
