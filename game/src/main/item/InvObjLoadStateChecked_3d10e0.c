/* rgp:protos */
#define RGP_SELF_InvObjLoadStateChecked_3d10e0 1
#include "port/game_protos.h"
#line 1
/* InvObjLoadStateChecked_3d10e0 -- byte-identical clone of InvObjLoadStateChecked_3ced20 (48 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of a 5-member byte-identical group (48 B each):
   InvObjLoadStateChecked_3d10e0 / InvObjLoadStateChecked_3d0600 / InvObjLoadStateChecked_3d10e0 / InvObjLoadStateChecked_3d30d0 / InvObjLoadStateChecked_3d3800.
   Both guards are ONE `||`: retail branches the first test INTO the shared
   return-0 body and the second one PAST it. */

/*rgp*/

s32 InvObjLoadStateChecked_3d10e0(void *a, void *b, s32 n, int rgp_a3)
{
    if (b == 0 || n <= 0) {
        return 0;
    }
    return InvObjLoadState_3d3940(a, b, n, (int)rgp_a3);
}
