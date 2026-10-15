/* CharaKind1002LoadBlob_3a9870 -- shape-identical to merged InvObjLoadStateChecked_3ced20 (12 instructions); the donor's
   source with the symbol renamed and 1 call target(s) substituted:
     InvObjLoadState_3d3940 -> CharaLoadBlob_3a9b70
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Head of a 5-member byte-identical group (48 B each):
   CharaKind1002LoadBlob_3a9870 / InvObjLoadStateChecked_3d0600 / InvObjLoadStateChecked_3d10e0 / InvObjLoadStateChecked_3d30d0 / InvObjLoadStateChecked_3d3800.
   Both guards are ONE `||`: retail branches the first test INTO the shared
   return-0 body and the second one PAST it. */

extern s32 CharaLoadBlob_3a9b70(void *a, void *b, s32 n);

s32 CharaKind1002LoadBlob_3a9870(void *a, void *b, s32 n)
{
    if (b == 0 || n <= 0) {
        return 0;
    }
    return CharaLoadBlob_3a9b70(a, b, n);
}
