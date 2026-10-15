/* CharaKind1004LoadBlob_3a9520 -- shape-identical to merged InvObjLoadStateChecked_3ced20 (12 instructions); the donor's
   source with the symbol renamed and 1 call target(s) substituted:
     InvObjLoadState_3d3940 -> CharaKind1003LoadBlob_3a96d0
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Head of a 5-member byte-identical group (48 B each):
   CharaKind1004LoadBlob_3a9520 / InvObjLoadStateChecked_3d0600 / InvObjLoadStateChecked_3d10e0 / InvObjLoadStateChecked_3d30d0 / InvObjLoadStateChecked_3d3800.
   Both guards are ONE `||`: retail branches the first test INTO the shared
   return-0 body and the second one PAST it. */

extern s32 CharaKind1003LoadBlob_3a96d0(void *a, void *b, s32 n);

s32 CharaKind1004LoadBlob_3a9520(void *a, void *b, s32 n)
{
    if (b == 0 || n <= 0) {
        return 0;
    }
    return CharaKind1003LoadBlob_3a96d0(a, b, n);
}
