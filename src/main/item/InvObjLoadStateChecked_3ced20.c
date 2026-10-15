#include "types.h"

/* Head of a 5-member byte-identical group (48 B each):
   InvObjLoadStateChecked_3ced20 / InvObjLoadStateChecked_3d0600 / InvObjLoadStateChecked_3d10e0 / InvObjLoadStateChecked_3d30d0 / InvObjLoadStateChecked_3d3800.
   Both guards are ONE `||`: retail branches the first test INTO the shared
   return-0 body and the second one PAST it. */

extern s32 InvObjLoadState_3d3940(void *a, void *b, s32 n);

s32 InvObjLoadStateChecked_3ced20(void *a, void *b, s32 n)
{
    if (b == 0 || n <= 0) {
        return 0;
    }
    return InvObjLoadState_3d3940(a, b, n);
}
