/* rgp:protos */
#define RGP_SELF_EntryListSelectNext_323500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int EntryListSelectNext_323500(s32 p0)
{
    s32 r0;

    r0 = ((short)EntryListGetCurIndex_3238b0(p0));
    return EntryListSelectByIndex_323540(p0, (r0 + 1));
}
