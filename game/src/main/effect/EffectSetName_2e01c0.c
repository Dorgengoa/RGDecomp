/* rgp:protos */
#define RGP_SELF_EffectSetName_2e01c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EffectGetParamIntVec_2e0200 (byte-identical, in cunits);
   this member's callee takes FOUR arguments, so the tag lands in $7. */

/*rgp*/

struct Obj0;

struct Obj0 {
    s16 m00;
};

void EffectSetName_2e01c0(s32 p0, struct Obj0 *p1, s32 p2)
{
    s16 t0;

    t0 = p1->m00;
    if (t0 != 2) {
        if (t0 != 3) {
            return;
        }
    }
    EffectEntriesSetNodeName_2dd8d0((p0 + 0x1674), p1, p2);
}
