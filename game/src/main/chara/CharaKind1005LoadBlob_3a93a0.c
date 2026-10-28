/* rgp:protos */
#define RGP_SELF_CharaKind1005LoadBlob_3a93a0 1
#include "port/game_protos.h"
#line 1
/* CharaKind1005LoadBlob_3a93a0 -- shape-identical to merged InvObjLoadStateChecked_3ced20 (12 instructions); the donor's
   source with the symbol renamed and 1 call target(s) substituted:
     InvObjLoadState_3d3940 -> CharaKind1002LoadBlob_3a9870
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Head of a 5-member byte-identical group (48 B each):
   CharaKind1005LoadBlob_3a93a0 / InvObjLoadStateChecked_3d0600 / InvObjLoadStateChecked_3d10e0 / InvObjLoadStateChecked_3d30d0 / InvObjLoadStateChecked_3d3800.
   Both guards are ONE `||`: retail branches the first test INTO the shared
   return-0 body and the second one PAST it. */

/*rgp*/

s32 CharaKind1005LoadBlob_3a93a0(void *a, void *b, s32 n)
{
    if (b == 0 || n <= 0) {
        return 0;
    }
    return CharaKind1002LoadBlob_3a9870(a, b, n);
}
