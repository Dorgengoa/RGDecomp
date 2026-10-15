#include "types.h"

extern s32 NavMgrFindGraphById_30cae0(s32, s32);
extern void NavGraphRelease_311170(s32);
extern s32 NavMgrIndexOf_30cd50(s32, s32);
extern void NavMgrFreeGraph_30cbc0(s32, s32);
extern void UskMemoryRefCompact_42cfc0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 NavMgrRemoveGraph_30cdd0(s32 p0, s32 p1)
{
    s32 r0;
    s32 r2;

    r0 = NavMgrFindGraphById_30cae0(p0, p1);
    if (r0 != 0) {
        NavGraphRelease_311170(r0);
        r2 = NavMgrIndexOf_30cd50((p0 + 4), r0);
        NavMgrFreeGraph_30cbc0((p0 + 4), r2);
        UskMemoryRefCompact_42cfc0(p0);
    }
}
