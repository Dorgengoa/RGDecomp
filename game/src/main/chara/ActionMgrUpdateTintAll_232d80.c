/* rgp:protos */
#define RGP_SELF_ActionMgrUpdateTintAll_232d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A list walk: the `b` into the test with the head in its delay slot is the
   standard while-loop rotation. */

/*rgp*/
/*rgp*/
/*rgp*/

void ActionMgrUpdateTintAll_232d80(s32 p0, f32 f)
{
    s32 it;

    it = DListGetHead_42ea60((u8 *)p0 + 0x20);
    while (it != 0) {
        CharaUpdateTint_213fc0(it + 0x10, f);
        it = DListGetNext_42eb30(it);
    }
}
