/* rgp:protos */
#define RGP_SELF_UiEntryListResetRectByTag_28eb10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void UiEntryListResetRectByTag_28eb10(s32 p0, s32 p1)
{
    s32 r0;

    r0 = ((s32)UiEntryListFindByTag_28ea40(p0, p1));
    UiEntryListResetEntryRect_28eb40(p0, r0);
}
